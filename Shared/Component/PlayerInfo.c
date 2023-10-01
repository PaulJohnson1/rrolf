#include <Shared/Component/PlayerInfo.h>

#include <stdlib.h>
#include <string.h>

#ifdef RR_SERVER
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include <Server/Client.h>
#endif
#include <Shared/Api.h>
#include <Shared/Component/Health.h>
#include <Shared/Rivet.h>
#include <Shared/SimulationCommon.h>
#include <Shared/StaticData.h>
#include <Shared/pb.h>

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(camera_y, float32)                                                       \
    X(camera_fov, float32)                                                     \
    X(flower_id, varuint)                                                      \
    X(camera_x, float32)                                                       \
    X(slot_count, varuint)                                                     \
    X(squad_pos, uint8)                                                        \
    X(arena, varuint)

enum
{
    state_flags_camera_y = 0b0000001,
    state_flags_camera_fov = 0b0000010,
    state_flags_slot_count = 0b0000100,
    state_flags_flower_id = 0b0001000,
    state_flags_camera_x = 0b0010000,
    state_flags_petals = 0b0100000,
    state_flags_squad_pos = 0b1000000,
    state_flags_petals_collected = 0b10000000,
    state_flags_arena = 0b100000000,
    state_flags_all = 0b111111111
};

void rr_component_player_info_init(struct rr_component_player_info *this,
                                   struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
    this->camera_fov = RR_BASE_FOV;
    RR_SERVER_ONLY(this->modifiers.drop_pickup_radius = 25;)
    this->collected_this_run = malloc(rr_petal_id_max * rr_rarity_id_max * sizeof (uint32_t));
    memset(this->collected_this_run, 0, rr_petal_id_max * rr_rarity_id_max * sizeof (uint32_t));
}

#ifdef RR_SERVER
#include <Server/Simulation.h>
#include <Server/Squad.h>
#endif 

void rr_component_player_info_free(struct rr_component_player_info *this,
                                   struct rr_simulation *simulation)
{
    free(this->collected_this_run);
#ifdef RR_SERVER
    if (rr_simulation_entity_alive(simulation, this->flower_id))
        rr_simulation_request_entity_deletion(simulation, this->flower_id);
#endif
}

#ifdef RR_SERVER
void rr_component_player_info_set_slot_cd(struct rr_component_player_info *this,
                                          uint8_t pos, uint8_t cd)
{
    this->protocol_state |=
        (this->slots[pos].client_cooldown != cd) * state_flags_petals;
    this->slots[pos].client_cooldown = cd;
}

void rr_component_player_info_set_update_loot(
                   struct rr_component_player_info *this)
{
    this->protocol_state |= state_flags_petals_collected;
}

void rr_component_player_info_petal_swap(struct rr_component_player_info *this,
                                         struct rr_simulation *simulation,
                                         uint8_t pos)
{
    struct rr_component_player_info_petal_slot *slot = &this->slots[pos];
    struct rr_component_player_info_petal_slot *s_slot =
        &this->secondary_slots[pos];
    for (uint32_t i = 0; i < slot->count; ++i)
    {
        EntityIdx id = slot->petals[i].entity_hash;
        if (id != RR_NULL_ENTITY && rr_simulation_has_entity(simulation, id))
        {
            rr_simulation_request_entity_deletion(simulation, id);
            slot->petals[i].entity_hash = RR_NULL_ENTITY;
        }
    }
    uint8_t temp = slot->id;
    slot->id = s_slot->id;
    s_slot->id = temp;
    temp = slot->rarity;
    slot->rarity = s_slot->rarity;
    s_slot->rarity = temp;

    slot->count = RR_PETAL_DATA[slot->id].count[slot->rarity];
    for (uint32_t i = 0; i < slot->count; ++i)
        slot->petals[i].cooldown_ticks = RR_PETAL_DATA[slot->id].cooldown + 25;
    this->protocol_state |= state_flags_petals;
}

void rr_component_player_info_write(struct rr_component_player_info *this,
                                    struct proto_bug *encoder, int is_creation,
                                    struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    if (this->parent_id != client->parent_id)
        state &= ~(state_flags_petals | state_flags_petals_collected);
    proto_bug_write_varuint(encoder, state, "player_info component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
    if (state & state_flags_petals)
    {
        for (uint32_t i = 0; i < this->slot_count; ++i)
        {
            proto_bug_write_uint8(encoder, this->slots[i].id, "p_id");
            proto_bug_write_uint8(encoder, this->slots[i].rarity, "p_rar");
            proto_bug_write_uint8(encoder, this->slots[i].client_cooldown,
                                  "p_ccd");

            proto_bug_write_uint8(encoder, this->secondary_slots[i].id, "p_id");
            proto_bug_write_uint8(encoder, this->secondary_slots[i].rarity,
                                  "p_rar");
        }
    }
    if (state & state_flags_petals_collected)
    {
        for (uint32_t id = 1; id < rr_petal_id_max; ++id)
        {
            for (uint32_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
            {
                if (this->collected_this_run[id * rr_rarity_id_max + rarity] == 0)
                    continue;
                proto_bug_write_uint8(encoder, id, "dr_id");
                proto_bug_write_uint8(encoder, rarity, "dr_rar");
                proto_bug_write_varuint(encoder, this->collected_this_run[id * rr_rarity_id_max + rarity], "dr_cnt");
            }
        }
        proto_bug_write_uint8(encoder, 0, "dr_id");
    }
}

RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_x)
RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_y)
RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_fov)
RR_DEFINE_PUBLIC_FIELD(player_info, uint32_t, slot_count)
RR_DEFINE_PUBLIC_FIELD(player_info, EntityHash, flower_id);
RR_DEFINE_PUBLIC_FIELD(player_info, EntityIdx, arena);
RR_DEFINE_PUBLIC_FIELD(player_info, uint8_t, squad_pos);
#endif

#ifdef RR_CLIENT
void rr_component_player_info_read(struct rr_component_player_info *this,
                                   struct proto_bug *encoder)
{
    uint64_t state =
        proto_bug_read_varuint(encoder, "player_info component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
    if (state & state_flags_petals)
    {
        for (uint32_t i = 0; i < this->slot_count; ++i)
        {
            this->slots[i].id = proto_bug_read_uint8(encoder, "p_id");
            this->slots[i].rarity = proto_bug_read_uint8(encoder, "p_rar");
            this->slots[i].client_cooldown =
                proto_bug_read_uint8(encoder, "p_ccd");

            this->secondary_slots[i].id = proto_bug_read_uint8(encoder, "p_id");
            this->secondary_slots[i].rarity =
                proto_bug_read_uint8(encoder, "p_rar");
        }
    }
    if (state & state_flags_petals_collected)
    {
        uint8_t id = proto_bug_read_uint8(encoder, "dr_id");
        while (id)
        {
            uint8_t rarity = proto_bug_read_uint8(encoder, "dr_rar");
            this->collected_this_run[id * rr_rarity_id_max + rarity] = proto_bug_read_varuint(encoder, "dr_cnt");
            id = proto_bug_read_uint8(encoder, "dr_id");
        }
    }
}
#endif