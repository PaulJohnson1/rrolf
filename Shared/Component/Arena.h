#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)
RR_SERVER_ONLY(struct rr_component_player_info;)

#ifdef RR_SERVER
struct rr_spawn_zone
{
    float x;
    float y;
    float w;
    float h;
};
#endif

struct rr_component_arena
{
    RR_SERVER_ONLY(struct rr_spawn_zone respawn_zone;)
    EntityIdx parent_id;
    RR_SERVER_ONLY(uint8_t protocol_state;)
    RR_SERVER_ONLY(uint8_t first_squad_to_enter;)
    RR_SERVER_ONLY(EntityIdx mob_count;)
    RR_SERVER_ONLY(uint16_t ticks_to_deletion;)
    RR_SERVER_ONLY(uint16_t maze_dim;)
    RR_SERVER_ONLY(struct rr_maze_grid *grid;)
    RR_SERVER_ONLY(float grid_size;)
};

void rr_component_arena_init(struct rr_component_arena *,
                             struct rr_simulation *);
void rr_component_arena_free(struct rr_component_arena *,
                             struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_arena_write(
                   struct rr_component_arena *, struct proto_bug *, int,
                   struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_arena_read(struct rr_component_arena *,
                                            struct proto_bug *);)
