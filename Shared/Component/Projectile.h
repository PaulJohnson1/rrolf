#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)
RR_SERVER_ONLY(struct rr_component_player_info;)

struct rr_component_projectile
{
    EntityIdx parent_id;
    RR_SERVER_ONLY(int16_t ticks_until_death;)

    RR_SERVER_ONLY(uint8_t protocol_state;)
};

void rr_component_projectile_init(struct rr_component_projectile *,
                                  struct rr_simulation *);
void rr_component_projectile_free(struct rr_component_projectile *,
                                  struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_projectile_write(
                   struct rr_component_projectile *, struct proto_bug *, int,
                   struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_projectile_read(
                   struct rr_component_projectile *, struct proto_bug *);)
