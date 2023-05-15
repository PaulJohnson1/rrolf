#include <Shared/Component/PlayerInfo.h>

#include <string.h>

#include <Shared/Encoder.h>

enum : uint64_t
{
    state_flags_camera_x =   0b000001,
    state_flags_camera_y =   0b000010,
    state_flags_camera_fov = 0b000100,
    state_flags_all =        0b000111
};

void rr_component_player_info_init(struct rr_component_player_info *this)
{
    memset(this, 0, sizeof *this);
}

void rr_component_player_info_free(struct rr_component_player_info *this)
{
}

void rr_component_player_info_write(struct rr_component_player_info *this, struct rr_encoder *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    rr_encoder_write_varuint(encoder, state);
    RR_ENCODE_PUBLIC_FIELD(camera_x, float);
    RR_ENCODE_PUBLIC_FIELD(camera_y, float);
    RR_ENCODE_PUBLIC_FIELD(camera_fov, float);
}

void rr_component_player_info_read(struct rr_component_player_info *this, struct rr_encoder *encoder)
{
    uint64_t state = rr_encoder_read_varuint(encoder);
    RR_DECODE_PUBLIC_FIELD(camera_x, float);
    RR_DECODE_PUBLIC_FIELD(camera_y, float);
    RR_DECODE_PUBLIC_FIELD(camera_fov, float);
}

RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_x)
RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_y)
RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_fov)
