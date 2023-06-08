#include <Shared/Component/PlayerInfo.h>

#include <string.h>
#include <stdlib.h>

#include <Shared/pb.h>
#include <Shared/StaticData.h>

#define FOR_EACH_PUBLIC_FIELD \
    X(camera_x, float32) \
    X(camera_y, float32) \
    X(flower_id, varuint) \
    X(slot_count, varuint) \
    X(camera_fov, float32) 

enum
{
    state_flags_flower_id = 0b000001,
    state_flags_camera_fov = 0b000010,
    state_flags_camera_y = 0b000100,
    state_flags_slot_count = 0b001000,
    state_flags_camera_x = 0b010000,
    state_flags_all = 0b001111
};

void rr_component_player_info_init(struct rr_component_player_info *this, struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
    this->camera_fov = 1.0f;
    #ifdef RR_SERVER
    for (uint64_t i = 0; i < 10; ++i)
    {
        uint8_t id = rand() % (rr_petal_id_max - 1) + 1;
        uint8_t rarity = rr_rarity_id_ultra;
        this->slots[i].rarity = rarity;
        this->slots[i].id = id;
        // this->slots[i].data = &RR_PETAL_DATA[id];
        this->slots[i].count = RR_PETAL_DATA[id].count[rarity];
        id = rand() % (rr_petal_id_max - 1) + 1;
        rarity = rr_rarity_id_ultra;
        this->secondary_slots[i].rarity = rarity;
        this->secondary_slots[i].id = id;
        // this->slots[i].data = &RR_PETAL_DATA[id];
    }
    #endif
}

void rr_component_player_info_free(struct rr_component_player_info *this, struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_player_info_write(struct rr_component_player_info *this, struct proto_bug *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "player_info component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
    for (uint32_t i = 0; i < this->slot_count; ++i)
    {
        proto_bug_write_uint8(encoder, this->slots[i].id, "p_id");
        proto_bug_write_uint8(encoder, this->slots[i].rarity, "p_rar");
        proto_bug_write_uint8(encoder, this->slots[i].client_cooldown, "p_ccd");

        proto_bug_write_uint8(encoder, this->secondary_slots[i].id, "p_id");
        proto_bug_write_uint8(encoder, this->secondary_slots[i].rarity, "p_rar");
    }
}

RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_x)
RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_y)
RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_fov)
RR_DEFINE_PUBLIC_FIELD(player_info, uint32_t, slot_count)
RR_DEFINE_PUBLIC_FIELD(player_info, EntityIdx, flower_id);

#endif

#ifdef RR_CLIENT
void rr_component_player_info_read(struct rr_component_player_info *this, struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "player_info component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
    for (uint32_t i = 0; i < this->slot_count; ++i)
    {
        this->slots[i].id = proto_bug_read_uint8(encoder, "p_id");
        this->slots[i].rarity = proto_bug_read_uint8(encoder, "p_rar");
        this->slots[i].client_cooldown = proto_bug_read_uint8(encoder, "p_ccd");

        this->secondary_slots[i].id = proto_bug_read_uint8(encoder, "p_id");
        this->secondary_slots[i].rarity = proto_bug_read_uint8(encoder, "p_rar");
    }
}
#endif