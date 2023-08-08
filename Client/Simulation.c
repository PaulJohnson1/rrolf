#include <Client/Simulation.h>

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <Client/Game.h>
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
        __rr_simulation_pending_deletion_free_components(id, this);
        __rr_simulation_pending_deletion_unset_entity(id, this);
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

    game->player_info = rr_simulation_get_player_info(
        this, proto_bug_read_varuint(encoder, "pinfo id"));
    this->game_over = proto_bug_read_uint8(encoder, "game over");
    this->updated_this_tick = 1;
}

void rr_simulation_tick(struct rr_simulation *this, float delta)
{
    rr_simulation_create_component_vectors(this);
    rr_system_interpolation_tick(this, 1 - powf(0.9f, delta * 10));
}
