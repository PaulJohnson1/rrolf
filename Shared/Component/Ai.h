#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)
RR_SERVER_ONLY(struct rr_component_player_info;)

enum rr_ai_state
{
    rr_ai_state_idle,
    rr_ai_state_idle_moving,
    rr_ai_state_chasing,
    rr_ai_state_attacking,

    // triceratops
    rr_ai_state_waiting_to_attack,
    rr_ai_state_recovering_after_charge,

    // hornet
    rr_ai_state_missile_shoot_delay,
    // player mobs
    rr_ai_state_returning_to_owner
};

struct rr_component_ai
{
    RR_SERVER_ONLY(uint32_t ticks_until_next_action;)
    EntityIdx parent_id;
    RR_SERVER_ONLY(EntityIdx target_entity;)
    RR_SERVER_ONLY(enum rr_ai_state ai_state;)
    RR_SERVER_ONLY(uint8_t protocol_state;)
    RR_SERVER_ONLY(uint8_t has_prediction;)
};

void rr_component_ai_init(struct rr_component_ai *, struct rr_simulation *);
void rr_component_ai_free(struct rr_component_ai *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_ai_write(struct rr_component_ai *,
                                          struct proto_bug *, int,
                                          struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_ai_read(struct rr_component_ai *,
                                         struct proto_bug *);)
