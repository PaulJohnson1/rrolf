#pragma once

#include <Shared/Bitset.h>
#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Rivet.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>

#ifdef RIVET_BUILD
#define RR_BASE_FOV (0.9f)
#else
#define RR_BASE_FOV (0.9f)
#endif


struct rr_simulation;
struct proto_bug;
RR_SERVER_ONLY(struct rr_squad_member;)
RR_CLIENT_ONLY(struct rr_renderer;)

struct rr_component_player_info_petal
{
    EntityHash entity_hash;
    int32_t cooldown_ticks;
};

struct rr_component_player_info_petal_slot
{
    uint8_t id;
    uint8_t rarity;
    uint8_t client_cooldown;
    RR_SERVER_ONLY(uint8_t count;)
    RR_SERVER_ONLY(struct rr_component_player_info_petal petals[5];)
};

struct rr_player_info_modifiers
{
    float drop_pickup_radius;
    //float rotation_direction;
};

struct rr_component_player_info
{
    struct rr_component_player_info_petal_slot slots[10];
    struct rr_component_player_info_petal_slot secondary_slots[10];
    RR_SERVER_ONLY(struct rr_squad_member *squad_member;)
    RR_SERVER_ONLY(struct rr_player_info_modifiers modifiers;)
    uint32_t *collected_this_run;
    RR_SERVER_ONLY(struct rr_server_client *client;)
    RR_SERVER_ONLY(uint32_t level;)
    RR_SERVER_ONLY(float global_rotation;)
    float camera_x;
    RR_CLIENT_ONLY(float lerp_camera_x;)
    float camera_y;
    RR_CLIENT_ONLY(float lerp_camera_y;)
    float camera_fov;
    RR_CLIENT_ONLY(float lerp_camera_fov;)
    RR_SERVER_ONLY(uint16_t protocol_state;)
    EntityIdx parent_id;
    EntityHash flower_id; // will be RR_NULL_ENTITY if nonexistant
    EntityIdx arena;
    RR_SERVER_ONLY(uint8_t rotation_count;)
    RR_SERVER_ONLY(uint8_t input;)
    uint8_t squad_pos;
    uint8_t squad;
    uint8_t slot_count;
    RR_SERVER_ONLY(
        uint8_t *entities_in_view;)
    RR_SERVER_ONLY(struct rr_id_rarity_pair drops_this_tick[8];) //yes, it's limited to 8. if the player poicks up more than that then it waits until the next tick
    RR_SERVER_ONLY(uint8_t drops_this_tick_size;)
};

void rr_component_player_info_init(struct rr_component_player_info *,
                                   struct rr_simulation *);
void rr_component_player_info_free(struct rr_component_player_info *,
                                   struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_player_info_set_slot_cd(
                   struct rr_component_player_info *, uint8_t, uint8_t);)
RR_SERVER_ONLY(void rr_component_player_info_set_update_loot(
                   struct rr_component_player_info *);)
RR_SERVER_ONLY(
    void rr_component_player_info_petal_swap(struct rr_component_player_info *,
                                             struct rr_simulation *, uint8_t);)

RR_SERVER_ONLY(void rr_component_player_info_write(
                   struct rr_component_player_info *, struct proto_bug *, int,
                   struct rr_component_player_info *);)
RR_CLIENT_ONLY(void rr_component_player_info_read(
                   struct rr_component_player_info *, struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(player_info, float, camera_x);
RR_DECLARE_PUBLIC_FIELD(player_info, float, camera_y);
RR_DECLARE_PUBLIC_FIELD(player_info, float, camera_fov);
RR_DECLARE_PUBLIC_FIELD(player_info, uint32_t, slot_count);
RR_DECLARE_PUBLIC_FIELD(player_info, EntityHash, flower_id);
RR_DECLARE_PUBLIC_FIELD(player_info, EntityIdx, arena);
RR_DECLARE_PUBLIC_FIELD(player_info, uint8_t, squad_pos);