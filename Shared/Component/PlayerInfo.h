#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct rr_encoder;

// check if there's rr_component_player_info_set function before setting a field
struct rr_component_player_info
{
                   EntityIdx parent_id;
                   EntityIdx player_id; // will be 0 if nonexistant
                   float camera_x;
    RR_CLIENT_ONLY(float lerp_camera_x;)
                   float camera_y;
    RR_CLIENT_ONLY(float lerp_camera_y;)
                   float camera_fov;
    RR_CLIENT_ONLY(float lerp_camera_fov;)
                   uint64_t protocol_state;
    RR_SERVER_ONLY(EntityIdx *entities_in_view_start;)
    RR_SERVER_ONLY(EntityIdx *entities_in_view_end;)
    RR_SERVER_ONLY(EntityIdx *entities_in_view_end_of_storage;)
};

void rr_component_player_info_init(struct rr_component_player_info *);
void rr_component_player_info_free(struct rr_component_player_info *);

RR_SERVER_ONLY(void rr_component_player_info_write(struct rr_component_player_info *, struct rr_encoder *, int is_creation);)
RR_CLIENT_ONLY(void rr_component_player_info_read(struct rr_component_player_info *, struct rr_encoder *);)

RR_DECLARE_PUBLIC_FIELD(player_info, float, camera_x);
RR_DECLARE_PUBLIC_FIELD(player_info, float, camera_y);
RR_DECLARE_PUBLIC_FIELD(player_info, float, camera_fov);
