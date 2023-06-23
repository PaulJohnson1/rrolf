#include <Client/Game.h>

#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

#ifndef EMSCRIPTEN
#include <libwebsockets.h>
#endif

#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>
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
    this->protocol_state = (1 << 20) - 1;

    this->ui_elements.title_screen = rr_ui_container_add_element(this->global_container, 
        rr_ui_v_container_init(rr_ui_container_init(), 15, 25, 4,
            rr_ui_text_init("rrolf", 72, 0xffffffff),
            rr_ui_h_container_init(rr_ui_container_init(), 0, 15, 2,
                rr_ui_text_input_init(360, 40, 15),
                rr_ui_find_server_button_init()
            ),
            rr_ui_squad_container_init(),
            rr_ui_title_screen_loadout_container_init()
        )
    );

    this->ui_elements.respawn_label = rr_ui_container_add_element(this->global_container, 
        rr_ui_set_justify(
            rr_ui_v_container_init(rr_ui_container_init(), 0, 15, 2,
                rr_ui_text_init("You died", 72, 0xffffffff),
                rr_ui_text_init("You will spawn back in next wave", 36, 0xffffffff)
            )
        , 1, 1)
    );

    this->ui_elements.game_over = rr_ui_container_add_element(this->global_container, 
        rr_ui_set_justify(
            rr_ui_v_container_init(rr_ui_container_init(), 0, 15, 2,
                rr_ui_text_init("Game Over", 72, 0xffffffff),
                rr_ui_text_init("You many now exit the squad", 36, 0xffffffff)
            )
        , 1, 1)
    );
     
    this->ui_elements.loadout = rr_ui_container_add_element(this->global_container, 
        rr_ui_set_justify(
            rr_ui_loadout_container_init()
        , 1, 2)
    );

    this->ui_elements.inventory = rr_ui_container_add_element(this->global_container, 
        rr_ui_pad(
            rr_ui_set_justify(
                rr_ui_scroll_container_init(rr_ui_inventory_container_init(), 400, 0xffff0000)
            , 0, 2)
        , 15)
    );
    /*
    this->ui_elements.inventory = rr_ui_container_add_element(this->global_container, 
        rr_ui_pad(
            rr_ui_set_justify(
                rr_ui_paired_button_init(rr_ui_inventory_container_init()),
            0, 2),
        15)
    );
    */

    this->ui_elements.wave_info = rr_ui_container_add_element(this->global_container,
        rr_ui_set_justify(
            rr_ui_wave_container_init()
        , 1, 0)
    );

    this->ui_elements.in_game_squad_info = rr_ui_container_add_element(this->global_container,
        rr_ui_set_justify(
            rr_ui_v_container_init(rr_ui_container_init(), 15, 15, 3,
                rr_ui_set_justify(
                    rr_ui_abandon_game_button_init()
                , 0, 0),
                rr_ui_static_space_init(50),
                rr_ui_h_container_init(rr_ui_container_init(), 0, 0, 2,
                    rr_ui_static_space_init(50),
                    rr_ui_v_container_init(rr_ui_container_init(), 0, 15, 4,
                        in_game_player_ui_init(0),
                        in_game_player_ui_init(1),
                        in_game_player_ui_init(2),
                        in_game_player_ui_init(3)
                    )
                )
            )
        , 0, 0)
    );

    for (uint32_t id = 0; id < rr_petal_id_max; ++id)
    {
        for (uint32_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
        {
            rr_renderer_init(&this->static_petals[id][rarity]);
            rr_renderer_set_dimensions(&this->static_petals[id][rarity], 50, 50);
            rr_renderer_translate(&this->static_petals[id][rarity], 25, 25);
            rr_renderer_render_static_petal(&this->static_petals[id][rarity], id, rarity);
            this->inventory[id][rarity] = 10;
            char *cd = malloc((sizeof *cd) * 8);
            cd[sprintf(cd, "↻ %.1fs", (RR_PETAL_DATA[id].cooldown * 2 / 5) * 0.1)] = 0;
            char *hp = malloc((sizeof *hp) * 8);
            hp[sprintf(hp, "%.1f", RR_PETAL_DATA[id].health * RR_PETAL_RARITY_SCALE[rarity])] = 0;
            char *dmg = malloc((sizeof *dmg) * 8);
            dmg[sprintf(dmg, "%.1f", RR_PETAL_DATA[id].damage * RR_PETAL_RARITY_SCALE[rarity] / RR_PETAL_DATA[id].count[rarity])] = 0;
            rr_ui_container_refactor(this->petal_tooltips[id][rarity] = rr_ui_set_background(rr_ui_v_container_init(rr_ui_container_init(), 10, 5, 6,
                    rr_ui_h_container_init(rr_ui_flex_container_init(), 0, 20, 2,
                        rr_ui_set_justify(rr_ui_text_init(RR_PETAL_NAMES[id], 24, 0xffffffff), 0, 0),
                        rr_ui_set_justify(rr_ui_text_init(cd, 16, 0xffffffff), 2, 0)
                    ),
                    rr_ui_set_justify(rr_ui_text_init(RR_RARITY_NAMES[rarity], 16, RR_RARITY_COLORS[rarity]), 0, 0),
                    rr_ui_static_space_init(10),
                    rr_ui_set_justify(rr_ui_text_init(RR_PETAL_DESCRIPTIONS[id], 16, 0xffffffff), 0, 0),
                    rr_ui_set_justify(
                        rr_ui_h_container_init(rr_ui_container_init(), 0, 0, 2,
                            rr_ui_text_init("Health: ", 12, 0xff44ff44),
                            rr_ui_text_init(hp, 12, 0xff44ff44)
                        )
                    , 0, 0),
                    rr_ui_set_justify(
                        rr_ui_h_container_init(rr_ui_container_init(), 0, 0, 2,
                            rr_ui_text_init("Damage: ", 12, 0xffff4444),
                            rr_ui_text_init(dmg, 12, 0xffff4444)
                        )
                    , 0, 0)
                )
            , 0x80000000));
        }
    }
}

void rr_game_websocket_on_event_function(enum rr_websocket_event_type type, void *data, void *captures, uint64_t size)
{
    struct rr_game *this = captures;
    switch (type)
    {
    case rr_websocket_event_type_open:
        this->socket_pending = 0;
        puts("websocket opened");
        break;
    case rr_websocket_event_type_close:
        //memset the clients
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
        {
            this->simulation_ready = 1;
            rr_simulation_read_binary(this->simulation, &encoder);
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
        case 69:
        {
            this->ticks_until_game_start = proto_bug_read_uint8(&encoder, "countdown");
            for (uint32_t i = 0; i < 4; ++i)
            {
                this->squad_members[i].in_use = proto_bug_read_uint8(&encoder, "bitbit");
                this->squad_members[i].ready = proto_bug_read_uint8(&encoder, "ready");
                for (uint32_t j = 0; j < 20; ++j)
                {
                    this->squad_members[i].loadout[j].id = proto_bug_read_uint8(&encoder, "id");
                    this->squad_members[i].loadout[j].rarity = proto_bug_read_uint8(&encoder, "rar");
                }
            }
            struct proto_bug encoder2;
            proto_bug_init(&encoder2, output_packet);
            proto_bug_write_uint8(&encoder2, 70, "header");
            for (uint32_t i = 0; i < 20; ++i)
            {
                if (this->protocol_state | (1 << i))
                {
                    proto_bug_write_uint8(&encoder2, i + 1, "pos");
                    proto_bug_write_uint8(&encoder2, this->loadout[i].id, "id");
                    proto_bug_write_uint8(&encoder2, this->loadout[i].rarity, "rar");
                }
            }
            proto_bug_write_uint8(&encoder2, 0, "pos");
            rr_websocket_send(&this->socket, encoder2.start, encoder2.current);
            this->protocol_state = 0;
            break;
        }
        default:
            RR_UNREACHABLE("how'd this happen");
        }
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
    struct rr_component_physical *physical = rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x, physical->lerp_y);
    rr_component_drop_render(entity, this);
    rr_renderer_free_context_state(this->renderer, &state);
}

void render_health_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    if (!rr_simulation_has_health(this->simulation, entity))
        return;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(this->renderer, &state);
    struct rr_component_physical *physical = rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x, physical->lerp_y + physical->radius + 30);
    rr_component_health_render(entity, this);
    rr_renderer_free_context_state(this->renderer, &state);
}

void render_mob_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    if (!rr_simulation_has_mob(this->simulation, entity))
        return;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(this->renderer, &state);
    struct rr_component_physical *physical = rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x, physical->lerp_y);
    rr_component_mob_render(entity, this);
    rr_renderer_free_context_state(this->renderer, &state);
}

void render_petal_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    if (!rr_simulation_has_petal(this->simulation, entity))
        return;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(this->renderer, &state);
    struct rr_component_physical *physical = rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x, physical->lerp_y);
    rr_component_petal_render(entity, this);
    rr_renderer_free_context_state(this->renderer, &state);
}

void render_flower_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    if (!rr_simulation_has_flower(this->simulation, entity))
        return;
    struct rr_renderer_context_state state;
    rr_renderer_init_context_state(this->renderer, &state);
    struct rr_component_physical *physical = rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x, physical->lerp_y);
    rr_component_flower_render(entity, this);
    rr_renderer_free_context_state(this->renderer, &state);
}

void player_info_finder(struct rr_game *this)
{
    struct rr_simulation *simulation = this->simulation;
    uint8_t counter = 1;
    memset(&this->player_infos, 0, sizeof this->player_infos);
    this->player_infos[0] = this->simulation->player_info;
    for (EntityIdx i = 1; i < RR_MAX_ENTITY_COUNT; ++i)
        if (rr_bitset_get(simulation->player_info_tracker, i) && i != this->simulation->player_info)
            this->player_infos[counter++] = i;
}

void rr_game_tick(struct rr_game *this, float delta)
{
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    double time = start.tv_sec * 1000000 + start.tv_usec;
    rr_renderer_set_transform(this->renderer, 1, 0, 0, 0, 1, 0);
    struct rr_renderer_context_state grand_state;
    rr_renderer_init_context_state(this->renderer, &grand_state);
    //render off-game elements
    struct rr_ui_container_metadata *data = this->global_container->misc_data;

    for (uint32_t i = 0; i < data->elements.size; ++i)
        if (data->elements.elements[i]->container_flags & 1)
            rr_ui_container_refactor(data->elements.elements[i]);
    {
        struct rr_renderer_context_state pre_state;
        rr_renderer_init_context_state(this->renderer, &pre_state);
        rr_renderer_translate(this->renderer, this->renderer->width * 0.5, this->renderer->height * 0.5);
        this->ui_elements.title_screen->on_render(this->ui_elements.title_screen, this);
        this->ui_elements.inventory->on_render(this->ui_elements.inventory, this);
        rr_renderer_free_context_state(this->renderer, &pre_state);
    }
    this->ui_elements.respawn_label->hidden = 1;
    this->ui_elements.loadout->hidden = 1;
    this->ui_elements.title_screen->hidden = 0;
    this->ui_elements.in_game_squad_info->hidden = 1;
    this->ui_elements.game_over->hidden = 1;
    this->ui_elements.inventory->hidden = this->simulation_ready;
    if (this->simulation_ready)
    {
        this->expanding_circle_radius += 1500 * delta;
        if (this->expanding_circle_radius > 1500)
        {
            this->expanding_circle_radius = 1500;
            this->ui_elements.title_screen->hidden = 1;
        }
        if (this->simulation->player_info != RR_NULL_ENTITY)
        {
            player_info_finder(this); //list player infos in order
            this->ui_elements.in_game_squad_info->hidden = 0;
            this->ui_elements.loadout->hidden = 0;
            if (rr_simulation_get_player_info(this->simulation, this->simulation->player_info)->flower_id == RR_NULL_ENTITY)
            {
                this->ui_elements.respawn_label->hidden = this->simulation->game_over;
                this->ui_elements.game_over->hidden = 1 - this->simulation->game_over;
            }
        }
    }
    else
    {
        this->expanding_circle_radius -= 1500 * delta;
        if (this->expanding_circle_radius < 0)
            this->expanding_circle_radius = 0;
    }

    if (this->expanding_circle_radius > 0 && this->expanding_circle_radius < 1500)
    {
        rr_renderer_begin_path(this->renderer);
        rr_renderer_set_fill(this->renderer, 0xff20a464);
        rr_renderer_arc(this->renderer, this->renderer->width * 0.5, this->renderer->height * 0.5, this->expanding_circle_radius * this->renderer->scale);
        rr_renderer_fill(this->renderer);
        rr_renderer_clip(this->renderer);
    }
    
    if (this->expanding_circle_radius > 0)
    {
        rr_simulation_tick(this->simulation, delta);

        this->renderer->state.filter.amount = 0;
        struct rr_renderer_context_state state1;
        struct rr_renderer_context_state state2;
        //rr_simulation_for_each_entity(this->simulation, this->simulation, player_info_finder);
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
                /*
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
                */
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
        {
            struct rr_renderer_context_state pre_state;
            rr_renderer_init_context_state(this->renderer, &pre_state);
            rr_renderer_translate(this->renderer, this->renderer->width * 0.5, this->renderer->height * 0.5);
            this->ui_elements.loadout->on_render(this->ui_elements.loadout, this);
            this->ui_elements.respawn_label->on_render(this->ui_elements.respawn_label, this);
            this->ui_elements.in_game_squad_info->on_render(this->ui_elements.in_game_squad_info, this);
            this->ui_elements.wave_info->on_render(this->ui_elements.wave_info, this);
            this->ui_elements.game_over->on_render(this->ui_elements.game_over, this);
            rr_renderer_free_context_state(this->renderer, &pre_state);
        }
    }

    if (this->socket_ready)
    {
#ifndef EMSCRIPTEN
        lws_service(this->socket.socket_context, -1);
#endif

        if (rr_bitset_get_bit(this->input_data->keys_pressed_this_tick, 186 /* ; */))
            this->displaying_debug_information ^= 1;

        if (this->simulation_ready && rr_bitset_get_bit(this->input_data->keys_pressed_this_tick, 13 /* enter */))
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, output_packet);
            proto_bug_write_uint8(&encoder, 1, "header");
            rr_websocket_send(&this->socket, encoder.start, encoder.current);
        }
    }

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
    rr_renderer_free_context_state(this->renderer, &grand_state);

    memset(this->input_data->keys_pressed_this_tick, 0, RR_BITSET_ROUND(256));
    memset(this->input_data->keys_released_this_tick, 0, RR_BITSET_ROUND(256));
    this->input_data->mouse_buttons_this_tick = 0;
    this->input_data->mouse_state_this_tick = 0;
}

void rr_game_connect_socket(struct rr_game *this)
{
    memset(this->simulation, 0, sizeof *this->simulation);
    this->socket_ready = 0;
    this->simulation_ready = 0;
    this->socket_pending = 1;
    rr_websocket_init(&this->socket);
    this->socket.user_data = this;
    this->socket.on_event = rr_game_websocket_on_event_function;
    rr_websocket_connect_to(&this->socket, "127.0.0.1", 8000);
}
