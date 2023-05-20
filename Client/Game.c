#include <Client/Game.h>

#include <assert.h>
#include <string.h>
#include <math.h>

#ifndef EMSCRIPTEN
#include <libwebsockets.h>
#endif

#include <Client/Renderer/Renderer.h>
#include <Client/InputData.h>
#include <Client/Socket.h>
#include <Client/Simulation.h>
#include <Shared/Utilities.h>

#include <Shared/Encoder.h>
#include <Shared/Bitset.h>

#include <Shared/Component/Arena.h>
#include <Shared/Component/Flower.h>
#include <Shared/Component/PlayerInfo.h>
#include <Shared/Component/Physical.h>

void rr_game_init(struct rr_game *this)
{
    memset(this, 0, sizeof *this);
}

void rr_game_websocket_on_event_function(enum rr_websocket_event_type type, void *data, void *captures, uint64_t size)
{
    struct rr_game *this = captures;
    switch (type)
    {
    case rr_websocket_event_type_open:
        puts("websocket opened");
        break;
    case rr_websocket_event_type_close:
        puts("websocket closed :(");
        break;
    case rr_websocket_event_type_data:
    {
        //rr_log_hex(data, data + size);
        struct rr_encoder encoder;
        rr_encoder_init(&encoder, data);
        switch (rr_encoder_read_uint8(&encoder))
        {
        case 0:
            rr_simulation_read_binary(this->simulation, &encoder);
            break;
        default:
            RR_UNREACHABLE("how'd this happen");
        }
        struct rr_encoder encoder2;
        static uint8_t output_packet[16];
        rr_encoder_init(&encoder2, output_packet);
        rr_encoder_write_uint8(&encoder2, 0);
        rr_encoder_write_uint8(&encoder2, 0);
        uint8_t movement_flags = 0;
        movement_flags |= (rr_bitset_get(this->input_data->keys, 87) || rr_bitset_get(this->input_data->keys, 38)) << 0;
        movement_flags |= (rr_bitset_get(this->input_data->keys, 65) || rr_bitset_get(this->input_data->keys, 37)) << 1;
        movement_flags |= (rr_bitset_get(this->input_data->keys, 83) || rr_bitset_get(this->input_data->keys, 40)) << 2;
        movement_flags |= (rr_bitset_get(this->input_data->keys, 68) || rr_bitset_get(this->input_data->keys, 39)) << 3;
        rr_encoder_write_uint8(&encoder2, movement_flags);
        rr_websocket_send(this->socket, encoder2.start, encoder2.current);
        //send packet
        break;
    }
    default:
        RR_UNREACHABLE("non exhaustive switch expression");
    }
}

void rr_game_tick(struct rr_game *this)
{
    rr_renderer_set_transform(this->renderer,1,0,0,0,1,0);
    struct rr_renderer_context_state state1;
    struct rr_renderer_context_state state2;
    if (this->player_info == 0)
    {
        for (EntityIdx playerInfo = 1; playerInfo < RR_MAX_ENTITY_COUNT; ++playerInfo)
        {
            if (!rr_bitset_get_bit(this->simulation->player_info_tracker, playerInfo))
                continue;
            this->player_info = playerInfo;
            break;
        }
    }
    if (this->player_info != 0)
    {
        rr_renderer_init_context_state(this->renderer, &state1);
        struct rr_component_player_info *player_info = rr_simulation_get_player_info(this->simulation, this->player_info);
        rr_renderer_translate(this->renderer, this->renderer->width / 2, this->renderer->height / 2);
        rr_renderer_scale(this->renderer, player_info->camera_fov * this->renderer->scale);
        rr_renderer_translate(this->renderer, -player_info->camera_x, -player_info->camera_y);
        for (EntityIdx p = 1; p < RR_MAX_ENTITY_COUNT; ++p)
        {
            if (rr_bitset_get_bit(this->simulation->arena_tracker, p) == 0)
                continue;
            rr_renderer_init_context_state(this->renderer, &state2);
            //intrusive op
            struct rr_component_arena *arena = rr_simulation_get_arena(this->simulation, p);
            rr_renderer_begin_path(this->renderer);
            rr_renderer_arc(this->renderer, 0, 0, arena->radius);
            rr_renderer_set_fill(this->renderer, 0xffeeeeee);
            rr_renderer_fill(this->renderer);
            rr_renderer_clip(this->renderer);

            struct rr_component_player_info *playerInfo = rr_simulation_get_player_info(this->simulation, this->player_info);

            rr_renderer_set_line_width(this->renderer, 1);
            rr_renderer_set_stroke(this->renderer, (uint32_t)(playerInfo->camera_fov * 51) << 24);

            float scale = playerInfo->camera_fov * this->renderer->scale;
            float leftX = playerInfo->camera_x - this->renderer->width / (2 * scale); 
            float rightX = playerInfo->camera_x + this->renderer->width / (2 * scale); 
            float topY = playerInfo->camera_y - this->renderer->height / (2 * scale); 
            float bottomY = playerInfo->camera_y + this->renderer->height / (2 * scale); 
            float newLeftX = ceilf(leftX / 50) * 50;
            float newTopY = ceilf(topY / 50) * 50;
            for (; newLeftX < rightX; newLeftX += 50)
            {
                rr_renderer_begin_path(this->renderer);
                rr_renderer_move_to(this->renderer, newLeftX, topY);
                rr_renderer_line_to(this->renderer, newLeftX, bottomY);
                rr_renderer_stroke(this->renderer);
            }
            for (; newTopY < bottomY; newTopY += 50)
            {
                rr_renderer_begin_path(this->renderer);
                rr_renderer_move_to(this->renderer, leftX, newTopY);
                rr_renderer_line_to(this->renderer, rightX, newTopY);
                rr_renderer_stroke(this->renderer);
            }
            rr_renderer_free_context_state(this->renderer, &state2);
            break; //only one arena
        }
        for (EntityIdx p = 1; p < RR_MAX_ENTITY_COUNT; ++p)
        {
            if (rr_bitset_get_bit(this->simulation->flower_tracker, p) == 0)
                continue;
            rr_renderer_init_context_state(this->renderer, &state2);
            rr_component_flower_render(p, this->simulation, this->renderer);
        
            rr_renderer_free_context_state(this->renderer, &state2);
        }
        rr_renderer_free_context_state(this->renderer, &state1);
    }
    this->socket->user_data = this;
    this->socket->on_event = rr_game_websocket_on_event_function;
#ifndef EMSCRIPTEN
    lws_service(this->socket->socket_context, -1);
#endif
}