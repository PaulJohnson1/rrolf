#include <fenv.h>
#include <stdlib.h>
#include <stdio.h>

#include <Server/Server.h>
#include <Shared/Encoder.h>
#include <Shared/Utilities.h>

int main()
{
#ifndef NDEBUG
    feenableexcept(FE_DIVBYZERO | FE_INVALID);
#endif

    struct rr_server s;
    rr_server_init(&s);
    struct rr_encoder encoder;
    static uint8_t data[10000];
    rr_encoder_init(&encoder, data);

    EntityIdx c = rr_simulation_alloc_entity(&s.simulation);
    EntityIdx e = rr_simulation_alloc_entity(&s.simulation);
    struct rr_component_physical *physical = rr_simulation_add_physical(&s.simulation, e);
    struct rr_component_player_info *player_info = rr_simulation_add_player_info(&s.simulation, c);

    rr_component_physical_set_radius(physical, 100000.0f);
    rr_component_player_info_set_camera_fov(player_info, 0.01f);
    rr_simulation_write_binary(&s.simulation, &encoder, player_info);
    rr_log_hex(encoder.start, encoder.current);
    // rr_server_run(&s);

    rr_server_free(&s);
}
