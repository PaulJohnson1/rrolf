// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <Client/Simulation.h>

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <Client/Game.h>
#include <Client/System/DeletionAnimation.h>
#include <Client/System/Interpolation.h>
#include <Shared/Bitset.h>
#include <Shared/pb.h>

void rr_simulation_init(struct rr_simulation *this)
{
    memset(this, 0, sizeof *this);
}

void rr_simulation_entity_create_with_id(struct rr_simulation *this,
                                         EntityIdx entity)
{
    this->entity_tracker[entity] = 1;
}

void rr_simulation_read_binary(struct rr_game *game, struct proto_bug *encoder)
{
    struct rr_simulation *this = game->simulation;
    EntityIdx id = 0;
    while (1)
    {
        id = proto_bug_read_varuint(encoder, "entity deletion id");
        if (id == RR_NULL_ENTITY)
            break;
        assert(id < RR_MAX_ENTITY_COUNT);
        assert(this->entity_tracker[id]);
        uint8_t type = proto_bug_read_uint8(encoder, "deletion type");
        if (type)
        {
            struct rr_simulation *del_s = game->deletion_simulation;
            EntityIdx id_2 = rr_simulation_alloc_entity(del_s);
#define XX(COMPONENT, ID)                                                      \
    if (rr_simulation_has_##COMPONENT(this, id))                               \
    {                                                                          \
        struct rr_component_##COMPONENT *o =                                   \
            rr_simulation_get_##COMPONENT(this, id);                           \
        struct rr_component_##COMPONENT *c =                                   \
            rr_simulation_add_##COMPONENT(del_s, id_2);                        \
        memcpy(c, o, sizeof(struct rr_component_##COMPONENT));                 \
    }
            RR_FOR_EACH_COMPONENT
#undef XX
            if (rr_simulation_has_physical(del_s, id_2))
            {
                rr_simulation_get_physical(del_s, id_2)->deletion_type = type;
                if (rr_simulation_has_mob(this, id) &&
                    (rr_simulation_get_relations(this, id)->team ==
                         rr_simulation_team_id_mobs ||
                     rr_simulation_get_mob(this, id)->id == rr_mob_id_meteor))
                {
                    struct rr_component_mob *mob =
                        rr_simulation_get_mob(this, id);
                    ++game->cache.mob_kills[mob->id][mob->rarity];
                }
            }
        }
        __rr_simulation_pending_deletion_free_components(id, this);
        __rr_simulation_pending_deletion_unset_entity(id, this);
    }

    // assuming that player info is written first (is it though)
    while (1)
    {
        id = proto_bug_read_varuint(encoder, "entity update id");
        if (id == RR_NULL_ENTITY)
            break;
        uint8_t is_creation = proto_bug_read_uint8(encoder, "upcreate");
        uint32_t component_flags =
            proto_bug_read_varuint(encoder, "entity component flags");

        if (is_creation)
        {
#ifndef RIVET_BUILD
            printf("create entity with id %d, components %d\n", id,
                   component_flags);
#endif
            this->entity_tracker[id] = 1 | component_flags;
#define XX(COMPONENT, ID)                                                      \
    if (component_flags & (1 << ID))                                           \
        rr_simulation_add_##COMPONENT(this, id);
            RR_FOR_EACH_COMPONENT
#undef XX
        }
        else if ((component_flags >> 1) != (this->entity_tracker[id] >> 1))
            printf(
                "protocol error: entity %d misaligned: expected %d but got %d",
                id, this->entity_tracker[id] >> 1, component_flags >> 1);

#define XX(COMPONENT, ID)                                                      \
    if (component_flags & (1 << ID))                                           \
        rr_component_##COMPONENT##_read(                                       \
            rr_simulation_get_##COMPONENT(this, id), encoder);
        RR_FOR_EACH_COMPONENT
#undef XX
    }
    game->player_info = rr_simulation_get_player_info(
        this, proto_bug_read_varuint(encoder, "pinfo id"));
    this->game_over = proto_bug_read_uint8(encoder, "game over");
    this->updated_this_tick = 1;
}

void rr_simulation_tick(struct rr_simulation *this, float delta)
{
    rr_simulation_create_component_vectors(this);
    rr_system_interpolation_tick(this, delta);
}

void rr_deletion_simulation_tick(struct rr_simulation *this, float delta)
{
    rr_bitset_for_each_bit(
        this->pending_deletions,
        this->pending_deletions + RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT), this,
        __rr_simulation_pending_deletion_free_components);
    rr_bitset_for_each_bit(this->pending_deletions,
                           this->pending_deletions +
                               RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT),
                           this, __rr_simulation_pending_deletion_unset_entity);
    memset(this->pending_deletions, 0, RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT));
    rr_simulation_create_component_vectors(this);
    rr_system_deletion_animation_tick(this, delta);
}

EntityIdx rr_simulation_alloc_entity(struct rr_simulation *this)
{
    for (EntityIdx i = 1; i < RR_MAX_ENTITY_COUNT; i++)
    {
        if (!rr_simulation_has_entity(this, i))
        {
            this->entity_tracker[i] = 1;
            // no more manual
#ifndef NDEBUG
            printf("<rr_simulation::entity_create::%d>\n", i);
#endif
            return i;
        }
    }
    RR_UNREACHABLE("ran out of entity ids");
}
