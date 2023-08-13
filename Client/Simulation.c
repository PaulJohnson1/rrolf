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
    rr_bitset_set(this->entity_tracker, entity);
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
        assert(rr_bitset_get_bit(this->entity_tracker, id));
        uint8_t type = proto_bug_read_uint8(encoder, "deletion type");
        if (type)
        {
            struct rr_simulation *del_s = game->deletion_simulation;
            EntityIdx id_2 = rr_simulation_alloc_entity(del_s);
            #define XX(COMPONENT, ID) \
            if (rr_simulation_has_##COMPONENT(this, id)) \
            { \
                struct rr_component_##COMPONENT *o = rr_simulation_get_##COMPONENT(this, id); \
                struct rr_component_##COMPONENT *c = rr_simulation_add_##COMPONENT(del_s, id_2); \
                memcpy(c, o, sizeof (struct rr_component_##COMPONENT)); \
            } 
            RR_FOR_EACH_COMPONENT
            #undef XX
            rr_simulation_get_physical(del_s, id_2)->deletion_type = type;
            if (rr_simulation_has_mob(this, id))
            {
                struct rr_component_mob *mob = rr_simulation_get_mob(this, id);
                game->cache.mob_kills[mob->id][mob->rarity]++;
            }
        }
        __rr_simulation_pending_deletion_free_components(id, this);
        __rr_simulation_pending_deletion_unset_entity(id, this);
        //rr_bitset_set(this->pending_deletions, id);
    }

    // assuming that player info is written first (is it though)
    while (1)
    {
        id = proto_bug_read_varuint(encoder, "entity update id");
        if (id == RR_NULL_ENTITY)
            break;
        uint8_t is_creation = !rr_bitset_get_bit(this->entity_tracker, id);
        uint32_t component_flags =
            proto_bug_read_varuint(encoder, "entity component flags");

        if (is_creation)
        {
#ifndef RIVET_BUILD
            printf("create entity with id %d, components %d\n", id,
                   component_flags);
#endif
            rr_bitset_set(this->entity_tracker, id);
#define XX(COMPONENT, ID)                                                      \
    if (component_flags & (1 << ID))                                           \
        rr_simulation_add_##COMPONENT(this, id);
            RR_FOR_EACH_COMPONENT
#undef XX
        }

#define XX(COMPONENT, ID)                                                      \
    if (component_flags & (1 << ID))                                           \
        rr_component_##COMPONENT##_read(                                       \
            rr_simulation_get_##COMPONENT(this, id), encoder);
        RR_FOR_EACH_COMPONENT
#undef XX
    }
    uint32_t len = proto_bug_read_varuint(encoder, "ani count");
    for (uint32_t i = 0; i < len; ++i)
    {
        struct rr_particle *particle = rr_particle_alloc(&game->particle_manager, proto_bug_read_uint8(encoder, "ani type"));
        particle->length = proto_bug_read_uint8(encoder, "ani length");
        for (uint32_t i = 0; i < particle->length; ++i)
        {
            particle->position[i].x = proto_bug_read_float32(encoder, "ani x");
            particle->position[i].y = proto_bug_read_float32(encoder, "ani y");
        }
        particle->opacity = 0.8;
    }
    game->player_info = rr_simulation_get_player_info(
        this, proto_bug_read_varuint(encoder, "pinfo id"));
    this->game_over = proto_bug_read_uint8(encoder, "game over");
    this->updated_this_tick = 1;
}

void rr_simulation_tick(struct rr_simulation *this, float delta)
{
    //rr_bitset_for_each_bit(this->pending_deletions, this->pending_deletions + RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT), this, __rr_simulation_pending_deletion_free_components);
    //rr_bitset_for_each_bit(this->pending_deletions, this->pending_deletions + RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT), this, __rr_simulation_pending_deletion_unset_entity);
    //memset(this->pending_deletions, 0, RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT));
    rr_simulation_create_component_vectors(this);
    rr_system_interpolation_tick(this, 1 - powf(0.9f, delta * 10));
}

void rr_deletion_simulation_tick(struct rr_simulation *this, float delta)
{
    rr_bitset_for_each_bit(this->pending_deletions, this->pending_deletions + RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT), this, __rr_simulation_pending_deletion_free_components);
    rr_bitset_for_each_bit(this->pending_deletions, this->pending_deletions + RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT), this, __rr_simulation_pending_deletion_unset_entity);
    memset(this->pending_deletions, 0, RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT));
    rr_simulation_create_component_vectors(this);
    rr_system_deletion_animation_tick(this, 1 - powf(0.9f, delta * 10));
}

EntityIdx rr_simulation_alloc_entity(struct rr_simulation *this)
{
    for (EntityIdx i = 1; i < RR_MAX_ENTITY_COUNT; i++)
    {
        if (!rr_simulation_has_entity(this, i))
        {
            rr_bitset_set(this->entity_tracker, i);
#ifndef NDEBUG
            printf("created with id %d\n", i);
#endif
            return i;
        }
    }
    RR_UNREACHABLE("ran out of entity ids");
}
