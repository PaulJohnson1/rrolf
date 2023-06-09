#include <Client/Game.h>

#include <assert.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#ifndef EMSCRIPTEN
#include <libwebsockets.h>
#endif

#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/ComponentRender.h>
#include <Client/Ui/Engine.h>
#include <Client/InputData.h>
#include <Client/Socket.h>
#include <Client/Simulation.h>
#include <Shared/Utilities.h>
#include <Shared/Bitset.h>
#include <Shared/Crypto.h>
#include <Shared/pb.h>
#include <Shared/Component/Arena.h>
#include <Shared/Component/Flower.h>
#include <Shared/Component/Petal.h>
#include <Shared/Component/PlayerInfo.h>
#include <Shared/Component/Physical.h>

void rr_game_init(struct rr_game *this)
{
    memset(this, 0, sizeof *this);
    this->global_container = rr_ui_container_init();
    this->global_container->container = this->global_container;
    this->ui_elements.respawn_label = rr_ui_container_add_element(this->global_container, 
        rr_ui_set_justify(
            rr_ui_v_container_init(rr_ui_container_init(), 0, 15, 2,
                rr_ui_text_init("rrolf", 72),
                rr_ui_h_container_init(rr_ui_container_init(), 0, 50, 2,
                    rr_ui_text_init("Spawn In", 48),
                    rr_ui_respawn_button_init()
                )
            )
        , 1, 1)
    );
    this->ui_elements.title_screen = rr_ui_container_add_element(this->global_container, 
        rr_ui_set_justify(
            rr_ui_v_container_init(rr_ui_container_init(), 0, 15, 2,
                rr_ui_text_init("rrolf", 72),
                rr_ui_h_container_init(rr_ui_container_init(), 0, 15, 2,
                    rr_ui_text_input_init(360, 40, 15),
                    rr_ui_find_server_button_init()
                )
            )
        , 1, 1)
    ); 
    this->ui_elements.loadout = rr_ui_container_add_element(this->global_container, 
        rr_ui_set_justify(
            rr_ui_v_container_init(rr_ui_container_init(), 20, 20, 2,
                rr_ui_h_container_init(rr_ui_container_init(), 0, 20, 10,
                    rr_ui_loadout_button_init(0, 1),
                    rr_ui_loadout_button_init(1, 1),
                    rr_ui_loadout_button_init(2, 1),
                    rr_ui_loadout_button_init(3, 1),
                    rr_ui_loadout_button_init(4, 1),
                    rr_ui_loadout_button_init(5, 1),
                    rr_ui_loadout_button_init(6, 1),
                    rr_ui_loadout_button_init(7, 1),
                    rr_ui_loadout_button_init(8, 1),
                    rr_ui_loadout_button_init(9, 1)
                ),
                rr_ui_h_container_init(rr_ui_container_init(), 0, 20, 10,
                    rr_ui_loadout_button_init(0, 0),
                    rr_ui_loadout_button_init(1, 0),
                    rr_ui_loadout_button_init(2, 0),
                    rr_ui_loadout_button_init(3, 0),
                    rr_ui_loadout_button_init(4, 0),
                    rr_ui_loadout_button_init(5, 0),
                    rr_ui_loadout_button_init(6, 0),
                    rr_ui_loadout_button_init(7, 0),
                    rr_ui_loadout_button_init(8, 0),
                    rr_ui_loadout_button_init(9, 0)
                )
            )
        , 1, 2)
    );

    this->ui_elements.inventory = rr_ui_container_add_element(this->global_container, 
        rr_ui_set_justify(
            rr_ui_inventory_container_init(),
        0, 2)
    );
    /*
    this->ui_elements.inventory = rr_ui_container_add_element(this->global_container, 
        rr_ui_set_justify(
            rr_ui_make_v_container(rr_ui_init_container(), 10, 20, 2,
                rr_ui_init_text("Inventory", 24),
                rr_ui_make_h_container(rr_ui_init_container(), 0, 10, 4,
                    rr_ui_make_v_container(rr_ui_init_container(), 0, 10, 4,
                        rr_ui_init_inventory_button(0, 0),
                        rr_ui_init_inventory_button(0, 1),
                        rr_ui_init_inventory_button(0, 2),
                        rr_ui_init_inventory_button(0, 3)
                    ),
                    rr_ui_make_v_container(rr_ui_init_container(), 0, 10, 4,
                        rr_ui_init_inventory_button(1, 0),
                        rr_ui_init_inventory_button(1, 1),
                        rr_ui_init_inventory_button(1, 2),
                        rr_ui_init_inventory_button(1, 3)
                    ),
                    rr_ui_make_v_container(rr_ui_init_container(), 0, 10, 4,
                        rr_ui_init_inventory_button(2, 0),
                        rr_ui_init_inventory_button(2, 1),
                        rr_ui_init_inventory_button(2, 2),
                        rr_ui_init_inventory_button(2, 3)
                    ),
                    rr_ui_make_v_container(rr_ui_init_container(), 0, 10, 4,
                        rr_ui_init_inventory_button(3, 0),
                        rr_ui_init_inventory_button(3, 1),
                        rr_ui_init_inventory_button(3, 2),
                        rr_ui_init_inventory_button(3, 3)
                    )
                )
            )
        , 0, 2)
    );
    */
    /*
    rr_ui_container_add_element(this->global_container, 
        rr_ui_set_justify(
            rr_ui_v_container_init(1, 20, 20, 2,
                rr_ui_text_init("Wave 69", 36),
                rr_ui_h_container_init(1, 0, 20, 4,
                    rr_ui_v_container_init(1, 0, -40, 4,
                        rr_ui_mob_button_init(0, 0),
                        rr_ui_mob_button_init(0, 1),
                        rr_ui_mob_button_init(0, 2),
                        rr_ui_mob_button_init(0, 3)
                    ),
                    rr_ui_v_container_init(1, 0, -40, 4,
                        rr_ui_mob_button_init(1, 0),
                        rr_ui_mob_button_init(1, 1),
                        rr_ui_mob_button_init(1, 2),
                        rr_ui_mob_button_init(1, 3)
                    ),
                    rr_ui_v_container_init(1, 0, -40, 4,
                        rr_ui_mob_button_init(2, 0),
                        rr_ui_mob_button_init(2, 1),
                        rr_ui_mob_button_init(2, 2),
                        rr_ui_mob_button_init(2, 3)
                    ),
                    rr_ui_v_container_init(1, 0, -40, 4,
                        rr_ui_mob_button_init(3, 0),
                        rr_ui_mob_button_init(3, 1),
                        rr_ui_mob_button_init(3, 2),
                        rr_ui_mob_button_init(3, 3)
                    )
                )
            )
        , 1, 0)
    );
    */
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
        puts("websocket closed");
        break;
    case rr_websocket_event_type_data:
    {
        struct proto_bug encoder;
        proto_bug_init(&encoder, data);

        if (!this->socket.recieved_first_packet)
        {
            this->socket.recieved_first_packet = 1;
            rr_decrypt(data, 1024, 21094093777837637ull);
            rr_decrypt(data, 8, 1);
            rr_decrypt(data, 1024, 59731158950470853ull);
            rr_decrypt(data, 1024, 64709235936361169ull);
            rr_decrypt(data, 1024, 59013169977270713ull);
            uint64_t verification = proto_bug_read_uint64(&encoder, "verification");
            proto_bug_read_uint32(&encoder, "useless bytes");
            this->socket.clientbound_encryption_key = proto_bug_read_uint64(&encoder, "c encryption key");
            this->socket.serverbound_encryption_key = proto_bug_read_uint64(&encoder, "s encryption key");
            struct proto_bug verify_encoder;
            proto_bug_init(&verify_encoder, output_packet);
            proto_bug_write_uint64(&verify_encoder, rr_get_rand(), "useless bytes");
            proto_bug_write_uint64(&verify_encoder, verification, "verification");
            rr_websocket_send(&this->socket, verify_encoder.start, verify_encoder.current);
            this->socket_ready = 1;
            return;
        }

        this->socket.clientbound_encryption_key = rr_get_hash(this->socket.clientbound_encryption_key);
        rr_decrypt(data, size, this->socket.clientbound_encryption_key);
        switch (proto_bug_read_uint8(&encoder, "header"))
        {
        case 0:
            rr_simulation_read_binary(this->simulation, &encoder);
            break;
        default:
            RR_UNREACHABLE("how'd this happen");
        }
        struct proto_bug encoder2;
        proto_bug_init(&encoder2, output_packet);
        proto_bug_write_uint8(&encoder2, 0, "header");
        proto_bug_write_uint8(&encoder2, 0, "movement type");
        uint8_t movement_flags = 0;
        movement_flags |= (rr_bitset_get(this->input_data->keys_pressed, 87) || rr_bitset_get(this->input_data->keys_pressed, 38)) << 0;
        movement_flags |= (rr_bitset_get(this->input_data->keys_pressed, 65) || rr_bitset_get(this->input_data->keys_pressed, 37)) << 1;
        movement_flags |= (rr_bitset_get(this->input_data->keys_pressed, 83) || rr_bitset_get(this->input_data->keys_pressed, 40)) << 2;
        movement_flags |= (rr_bitset_get(this->input_data->keys_pressed, 68) || rr_bitset_get(this->input_data->keys_pressed, 39)) << 3;
        movement_flags |= this->input_data->mouse_buttons << 4;
        movement_flags |= rr_bitset_get(this->input_data->keys_pressed, 32) << 4;
        movement_flags |= rr_bitset_get(this->input_data->keys_pressed, 16) << 5;
        proto_bug_write_uint8(&encoder2, movement_flags, "movement kb flags");
        rr_websocket_send(&this->socket, encoder2.start, encoder2.current);
        break;
    }
    default:
        RR_UNREACHABLE("non exhaustive switch expression");
    }
}

void render_drop_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    if (!rr_simulation_has_drop(this->simulation, entity))
        return;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(this->renderer, &state);
    rr_component_drop_render(entity, this->simulation, this->renderer);
    rr_renderer_free_context_state(this->renderer, &state);
}

void render_health_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    if (!rr_simulation_has_health(this->simulation, entity))
        return;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(this->renderer, &state);
    rr_component_health_render(entity, this->simulation, this->renderer);
    rr_renderer_free_context_state(this->renderer, &state);
}

void render_mob_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    if (!rr_simulation_has_mob(this->simulation, entity))
        return;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(this->renderer, &state);
    rr_component_mob_render(entity, this->simulation, this->renderer);
    rr_renderer_free_context_state(this->renderer, &state);
}

void render_petal_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    if (!rr_simulation_has_petal(this->simulation, entity))
        return;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(this->renderer, &state);
    rr_component_petal_render(entity, this->simulation, this->renderer);
    rr_renderer_free_context_state(this->renderer, &state);
}

void render_flower_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    if (!rr_simulation_has_flower(this->simulation, entity))
        return;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(this->renderer, &state);
    rr_component_flower_render(entity, this->simulation, this->renderer);
    rr_renderer_free_context_state(this->renderer, &state);
}

void player_info_finder(EntityIdx entity, void *captures)
{
    struct rr_simulation *this = captures;
    if (rr_simulation_has_player_info(this, entity))
        this->player_info = entity;
}

void rr_game_tick(struct rr_game *this, float delta)
{
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    double time = start.tv_sec * 1000000 + start.tv_usec;
    rr_renderer_set_transform(this->renderer, 1, 0, 0, 0, 1, 0);    
    if (this->socket_ready)
    {
        rr_simulation_tick(this->simulation, delta);

        this->renderer->state.filter.amount = 0;
        struct rr_renderer_context_state state1;
        struct rr_renderer_context_state state2;
        rr_simulation_for_each_entity(this->simulation, this->simulation, player_info_finder);
        if (this->simulation->player_info != RR_NULL_ENTITY)
        {
            rr_renderer_init_context_state(this->renderer, &state1);
            struct rr_component_player_info *player_info = rr_simulation_get_player_info(this->simulation, this->simulation->player_info);
            rr_renderer_translate(this->renderer, this->renderer->width / 2, this->renderer->height / 2);
            rr_renderer_scale(this->renderer, player_info->lerp_camera_fov * this->renderer->scale);
            rr_renderer_translate(this->renderer, -player_info->lerp_camera_x, -player_info->lerp_camera_y);
            if (player_info->flower_id != RR_NULL_ENTITY)
            {
                if (rr_simulation_get_physical(this->simulation, player_info->flower_id)->server_animation_tick != 0)
                    rr_renderer_translate(this->renderer, rr_frand() * 5.0f, rr_frand() * 5.0f);
            }
            for (EntityIdx p = 1; p < RR_MAX_ENTITY_COUNT; ++p)
            {
                if (rr_bitset_get_bit(this->simulation->arena_tracker, p) == 0)
                    continue;
                uint32_t alpha = (uint32_t)(player_info->lerp_camera_fov * 51) << 24;
                rr_renderer_init_context_state(this->renderer, &state2);
                rr_renderer_set_transform(this->renderer, 1, 0, 0, 0, 1, 0);
                rr_renderer_set_fill(this->renderer, 0xff20a464);
                rr_renderer_fill_rect(this->renderer, 0, 0, this->renderer->width, this->renderer->height);
                rr_renderer_set_fill(this->renderer, alpha);
                rr_renderer_fill_rect(this->renderer, 0, 0, this->renderer->width, this->renderer->height);
                rr_renderer_free_context_state(this->renderer, &state2);
                rr_renderer_init_context_state(this->renderer, &state2);
                // intrusive op
                struct rr_component_arena *arena = rr_simulation_get_arena(this->simulation, p);
                rr_renderer_begin_path(this->renderer);
                rr_renderer_arc(this->renderer, 0, 0, arena->radius);
                rr_renderer_set_fill(this->renderer, 0xff20a464);
                rr_renderer_fill(this->renderer);
                rr_renderer_clip(this->renderer);

                rr_renderer_set_line_width(this->renderer, 1);
                rr_renderer_set_stroke(this->renderer, alpha);

                float scale = player_info->lerp_camera_fov * this->renderer->scale;
                float leftX = player_info->lerp_camera_x - this->renderer->width / (2 * scale);
                float rightX = player_info->lerp_camera_x + this->renderer->width / (2 * scale);
                float topY = player_info->lerp_camera_y - this->renderer->height / (2 * scale);
                float bottomY = player_info->lerp_camera_y + this->renderer->height / (2 * scale);
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
                break; // only one arena
            }

            rr_simulation_for_each_entity(this->simulation, this, render_health_component);
            rr_simulation_for_each_entity(this->simulation, this, render_drop_component);
            rr_simulation_for_each_entity(this->simulation, this, render_mob_component);
            rr_simulation_for_each_entity(this->simulation, this, render_petal_component);
            rr_simulation_for_each_entity(this->simulation, this, render_flower_component);
            rr_renderer_free_context_state(this->renderer, &state1);
        }
    }
    if (this->socket_ready)
    {
#ifndef EMSCRIPTEN
        lws_service(this->socket.socket_context, -1);
#endif

        if (rr_bitset_get_bit(this->input_data->keys_pressed_this_tick, 186 /* ; */))
            this->displaying_debug_information ^= 1;

        if (rr_bitset_get_bit(this->input_data->keys_pressed_this_tick, 13 /* enter */))
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, output_packet);
            proto_bug_write_uint8(&encoder, 1, "header");
            rr_websocket_send(&this->socket, encoder.start, encoder.current);
        }
    }
    this->ui_elements.respawn_label->hidden = 1;
    this->ui_elements.title_screen->hidden = 0;
    if (this->socket_ready)
    {
        this->ui_elements.title_screen->hidden = 1;
        if (this->simulation->player_info != RR_NULL_ENTITY)
            if (rr_simulation_get_player_info(this->simulation, this->simulation->player_info)->flower_id == RR_NULL_ENTITY)
                this->ui_elements.respawn_label->hidden = 0;
    }

    this->global_container->on_render(this->global_container, this);

    gettimeofday(&end, NULL);
    long time_elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    if (this->displaying_debug_information)
    {
        struct rr_renderer_context_state state;
        rr_renderer_init_context_state(this->renderer, &state);
        rr_renderer_scale(this->renderer, 5);
        static char debug_mspt[100];
        debug_mspt[sprintf(debug_mspt, "%f mspt", (float)time_elapsed / 1000.0f)] = 0;
        rr_renderer_fill_text(this->renderer, debug_mspt, 0, 8);
        rr_renderer_free_context_state(this->renderer, &state);
        // rr_renderer_stroke_text
    }

    memset(this->input_data->keys_pressed_this_tick, 0, RR_BITSET_ROUND(256));
    memset(this->input_data->keys_released_this_tick, 0, RR_BITSET_ROUND(256));
    this->input_data->mouse_buttons_this_tick = 0;
    this->input_data->mouse_state_this_tick = 0;
}

void rr_game_connect_socket(struct rr_game *this)
{
    memset(this->simulation, 0, sizeof *this->simulation);
    this->socket_ready = 0;
    this->socket_pending = 1;
    rr_websocket_init(&this->socket);
    this->socket.user_data = this;
    this->socket.on_event = rr_game_websocket_on_event_function;
    rr_websocket_connect_to(&this->socket, "127.0.0.1", 8000);
}
