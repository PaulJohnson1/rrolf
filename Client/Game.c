#include <Client/Game.h>

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#ifndef EMSCRIPTEN
#include <libwebsockets.h>
#endif

#include <Client/Assets/Init.h>
#include <Client/InputData.h>
#include <Client/Renderer/ComponentRender.h>
#include <Client/Renderer/RenderFunctions.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Client/Socket.h>
#include <Client/Storage.h>
#include <Client/Ui/Engine.h>
#include <Shared/Api.h>
#include <Shared/Bitset.h>
#include <Shared/Component/Arena.h>
#include <Shared/Component/Flower.h>
#include <Shared/Component/Petal.h>
#include <Shared/Component/Physical.h>
#include <Shared/Component/PlayerInfo.h>
#include <Shared/Crypto.h>
#include <Shared/Rivet.h>
#include <Shared/Utilities.h>
#include <Shared/cJSON.h>
#include <Shared/pb.h>

void validate_loadout(struct rr_game *this)
{
    uint32_t temp_inv[rr_petal_id_max][rr_rarity_id_max];
    memcpy(&temp_inv, &this->inventory,
           (sizeof(uint32_t)) * rr_petal_id_max * rr_rarity_id_max);
    for (uint8_t i = 0; i < 20; ++i)
    {
        uint8_t id = this->cache.loadout[i].id;
        uint8_t rarity = this->cache.loadout[i].rarity;
        if (temp_inv[id][rarity] == 0)
            this->cache.loadout[i].id = this->cache.loadout[i].rarity = 0;
        else
            --temp_inv[id][rarity];
    }
}

void rr_api_on_get_petals(char *json, void *a)
{
    struct rr_game *game = a;

    for (uint32_t id = 0; id < rr_petal_id_max; ++id)
        for (uint32_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
            game->inventory[id][rarity] = 0;

    cJSON *parsed = cJSON_Parse(json);
    if (parsed == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON *petals = cJSON_GetObjectItemCaseSensitive(parsed, "petals");
    if (petals == NULL || !cJSON_IsObject(petals))
    {
        fprintf(stderr, "petals is missing or is not an object\n");
        cJSON_Delete(parsed);
        return;
    }
    for (cJSON *petal_key = petals->child; petal_key != NULL;
         petal_key = petal_key->next)
    {
        char *key = petal_key->string;
        char *sub_key1 = strtok(key, ":");
        char *sub_key2 = strtok(NULL, ":");

        if (sub_key1 && sub_key2)
        {
            int index1 = atoi(sub_key1);
            int index2 = atoi(sub_key2);

            game->inventory[index1][index2] =
                petal_key->valueint; // Assuming the value is a double.
        }
    }

    cJSON_Delete(parsed);
}

void rr_rivet_on_log_in(char *token, char *avatar_url, char *name,
                        char *account_number, char *uuid, void *captures)
{
    struct rr_game *this = captures;
    strcpy(this->rivet_account.token, token);
    strcpy(this->rivet_account.name, name);
    strcpy(this->rivet_account.avatar_url, avatar_url);
    strcpy(this->rivet_account.account_number, account_number);
    strcpy(this->rivet_account.uuid, uuid);

    rr_api_get_petals(this->rivet_account.uuid, this->rivet_account.token,
                      this);
}

static uint8_t simulation_not_ready(struct rr_ui_element *this,
                                    struct rr_game *game)
{
    return 1 - game->simulation_ready;
}

static uint8_t simulation_ready(struct rr_ui_element *this,
                                struct rr_game *game)
{
    return game->simulation_ready;
}

static uint8_t socket_ready(struct rr_ui_element *this, struct rr_game *game)
{
    return game->socket_ready;
}

static uint8_t socket_pending_or_ready(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    return game->socket_pending || game->socket_ready;
}

static void window_on_event(struct rr_ui_element *this, struct rr_game *game)
{
    if (game->input_data->mouse_buttons_up_this_tick & 1)
        game->bottom_ui_open = game->top_ui_open = 0;
}

void rr_game_init(struct rr_game *this)
{
    memset(this, 0, sizeof *this);
    rr_static_data_init();
    this->window = rr_ui_container_init();
    this->window->container = this->window;
    this->window->h_justify = this->window->v_justify = 1;
    this->window->resizeable = 0;
    this->window->on_event = window_on_event;
    this->cache.slots_unlocked = 10;
    for (uint8_t i = 0; i < this->cache.slots_unlocked; ++i)
        this->protocol_state |= ((1 | (1 << 10)) << i);

    this->inventory[rr_petal_id_basic][rr_rarity_id_common] = 1;

    strcpy(this->rivet_account.name, "loading");
    strcpy(this->rivet_account.avatar_url, "");
    strcpy(this->rivet_account.token, "");
    strcpy(this->rivet_account.account_number, "#0000");
    strcpy(this->rivet_account.uuid, "no-uuid");
    rr_rivet_identities_create_guest(this);

    // clang-format off
    rr_ui_container_add_element(
        this->window,
        rr_ui_pad(rr_ui_set_justify(rr_ui_rivet_container_init(this), -1, -1),
                  10));
    rr_ui_container_add_element(
        this->window,
        rr_ui_link_toggle(rr_ui_wave_container_init(), simulation_ready));

    rr_ui_container_add_element(
        this->window,
        rr_ui_link_toggle(
            rr_ui_set_background(
                rr_ui_v_container_init(rr_ui_container_init(), 10, 20,
                    rr_ui_v_container_init(rr_ui_container_init(), 0, 20,
                        rr_ui_text_init("rrolf.io", 96, 0xffffffff),
                        rr_ui_h_container_init(
                            rr_ui_container_init(), 10, 20,
                            rr_ui_text_input_init(400, 36, &this->cache.nickname[0], 16),
                            rr_ui_set_background(rr_ui_join_button_init(), 0xff1dd129),
                            NULL
                        ),
                        rr_ui_set_justify(rr_ui_set_background(rr_ui_squad_button_init(), 0xff1dd129), 1, 0),
                        rr_ui_set_background(
                            rr_ui_link_toggle(
                                rr_ui_v_container_init(
                                    rr_ui_container_init(), 10, 20,
                                    rr_ui_text_init("Squad", 18, 0xffffffff),
                                    rr_ui_h_container_init(
                                        rr_ui_container_init(), 5, 10,
                                        rr_ui_text_init("initial wave:", 14, -1),
                                        rr_ui_h_slider_init(300, 20, &this->cache.wave_start_percent, 1),
                                        NULL
                                    ),
                                    rr_ui_choose_element_init(
                                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10, 
                                        rr_ui_h_container_init(
                                            rr_ui_container_init(), 10, 20,
                                            rr_ui_squad_player_container_init(&this->squad_members[0]),
                                            rr_ui_squad_player_container_init(&this->squad_members[1]),
                                            rr_ui_squad_player_container_init(&this->squad_members[2]),
                                            rr_ui_squad_player_container_init(&this->squad_members[3]),
                                            NULL
                                        ),
                                        rr_ui_set_justify(rr_ui_countdown_init(this), 1, 0),
                                        NULL
                                    ),
                                    rr_ui_text_init("Joining Squad...", 24, 0xffffffff),
                                    socket_ready),
                                    NULL
                                ),
                            socket_pending_or_ready),
                        0x40ffffff),
                        NULL
                    ),
                    rr_ui_h_container_init(rr_ui_container_init(), 0, 15,
                        rr_ui_title_screen_loadout_button_init(0),
                        rr_ui_title_screen_loadout_button_init(1),
                        rr_ui_title_screen_loadout_button_init(2),
                        rr_ui_title_screen_loadout_button_init(3),
                        rr_ui_title_screen_loadout_button_init(4),
                        rr_ui_title_screen_loadout_button_init(5),
                        rr_ui_title_screen_loadout_button_init(6),
                        rr_ui_title_screen_loadout_button_init(7),
                        rr_ui_title_screen_loadout_button_init(8),
                        rr_ui_title_screen_loadout_button_init(9),
                        NULL
                    ),
                    rr_ui_h_container_init(rr_ui_container_init(), 0, 15,
                        rr_ui_title_screen_loadout_button_init(10),
                        rr_ui_title_screen_loadout_button_init(11),
                        rr_ui_title_screen_loadout_button_init(12),
                        rr_ui_title_screen_loadout_button_init(13),
                        rr_ui_title_screen_loadout_button_init(14),
                        rr_ui_title_screen_loadout_button_init(15),
                        rr_ui_title_screen_loadout_button_init(16),
                        rr_ui_title_screen_loadout_button_init(17),
                        rr_ui_title_screen_loadout_button_init(18),
                        rr_ui_title_screen_loadout_button_init(19),
                        NULL
                    ),
                    rr_ui_text_init("powered by Rivet", 15, 0xffffffff),
                    NULL
                ),
            0x00000000),
        simulation_not_ready)
    );
    rr_ui_container_add_element(this->window, rr_ui_inventory_container_init());
    rr_ui_container_add_element(this->window, rr_ui_mob_container_init());
    rr_ui_container_add_element(this->window, rr_ui_crafting_container_init());
    rr_ui_container_add_element(this->window, rr_ui_waiting_respawn_screen_init());
    rr_ui_container_add_element(this->window, rr_ui_finished_game_screen());
    rr_ui_container_add_element(this->window, rr_ui_pad(
        rr_ui_v_pad(
            rr_ui_set_justify(
                rr_ui_v_container_init(rr_ui_container_init(), 10, 20,
                    rr_ui_in_game_player_hud_init(0),
                    rr_ui_in_game_player_hud_init(1),
                    rr_ui_in_game_player_hud_init(2),
                    rr_ui_in_game_player_hud_init(3),
                    NULL
                )
            , -1, -1)
        , 100)
    , 50));
    rr_ui_container_add_element(
        this->window,
        rr_ui_set_justify(
            rr_ui_link_toggle(
                rr_ui_v_container_init(rr_ui_container_init(), 10, 10,
                    rr_ui_inventory_toggle_button_init(),
                    rr_ui_mob_gallery_toggle_button_init(),
                    rr_ui_crafting_toggle_button_init(),
                    NULL
                ),
            simulation_not_ready),
        -1, 1)
    );
    rr_ui_container_add_element(
        this->window,
        rr_ui_link_toggle(
            rr_ui_set_justify(
                rr_ui_v_container_init(rr_ui_container_init(), 15, 15,
                    rr_ui_h_container_init(
                        rr_ui_container_init(), 0, 15,
                        rr_ui_text_init("[x]", 18, 0xffffffff),
                        rr_ui_loadout_button_init(0),
                        rr_ui_loadout_button_init(1),
                        rr_ui_loadout_button_init(2),
                        rr_ui_loadout_button_init(3),
                        rr_ui_loadout_button_init(4),
                        rr_ui_loadout_button_init(5),
                        rr_ui_loadout_button_init(6),
                        rr_ui_loadout_button_init(7),
                        rr_ui_loadout_button_init(8),
                        rr_ui_loadout_button_init(9),
                        rr_ui_text_init("[x]", 18, 0x00000000),
                        NULL
                    ),
                    rr_ui_h_container_init(
                        rr_ui_container_init(), 0, 15,
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10, 
                            rr_ui_loadout_button_init(10),
                            rr_ui_text_init("[1]", 14, 0xffffffff),
                            NULL
                        ),
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10, 
                            rr_ui_loadout_button_init(11),
                            rr_ui_text_init("[2]", 14, 0xffffffff),
                            NULL
                        ),
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10,
                            rr_ui_loadout_button_init(12),
                            rr_ui_text_init("[3]", 14, 0xffffffff),
                            NULL
                        ),
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10,
                            rr_ui_loadout_button_init(13),
                            rr_ui_text_init("[4]", 14, 0xffffffff),
                            NULL
                        ),
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10,
                            rr_ui_loadout_button_init(14),
                            rr_ui_text_init("[5]", 14, 0xffffffff),
                            NULL
                        ),
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10,
                            rr_ui_loadout_button_init(15),
                            rr_ui_text_init("[6]", 14, 0xffffffff),
                            NULL
                        ),
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10,
                            rr_ui_loadout_button_init(16),
                            rr_ui_text_init("[7]", 14, 0xffffffff),
                            NULL
                        ),
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10,
                            rr_ui_loadout_button_init(17),
                            rr_ui_text_init("[8]", 14, 0xffffffff),
                            NULL
                        ),
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10,
                            rr_ui_loadout_button_init(18),
                            rr_ui_text_init("[9]", 14, 0xffffffff),
                            NULL
                        ),
                        rr_ui_v_container_init(rr_ui_container_init(), 0, 10,
                            rr_ui_loadout_button_init(19),
                            rr_ui_text_init("[0]", 14, 0xffffffff),
                            NULL
                        ),
                        NULL
                    ),
                    NULL
                ),
            0, 1),
        simulation_ready)
    );
    rr_ui_container_add_element(this->window,
                                rr_ui_settings_container_init(this));
    rr_ui_container_add_element(this->window,
                                rr_ui_changelog_container_init());

    this->rivet_info_tooltip = rr_ui_container_add_element(
        this->window,
        rr_ui_link_toggle(
            rr_ui_set_justify(
                rr_ui_set_background(
                    rr_ui_h_container_init(rr_ui_container_init(), 10, 0,
                        rr_ui_text_init(this->rivet_account.uuid, 16, 0xffffffff),
                        NULL
                    ),
                0x80000000),
            -1, -1),
        rr_ui_never_show)
    );
    this->rivet_info_tooltip->poll_events = rr_ui_no_focus;
    for (uint32_t id = 0; id < rr_mob_id_max; ++id)
    {
        for (uint32_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
        {
            this->mob_tooltips[id][rarity] = rr_ui_mob_tooltip_init(id, rarity);
            rr_ui_container_add_element(this->window,
                                        this->mob_tooltips[id][rarity]);
        }
    }
    for (uint32_t id = 0; id < rr_petal_id_max; ++id)
    {
        for (uint32_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
        {
            this->inventory[id][rarity] = 0;
            rr_renderer_init(&this->static_petals[id][rarity]);
            rr_renderer_set_dimensions(&this->static_petals[id][rarity], 50,
                                       50);
            rr_renderer_translate(&this->static_petals[id][rarity], 25, 25);
            rr_renderer_render_static_petal(&this->static_petals[id][rarity],
                                            id, rarity);
            this->petal_tooltips[id][rarity] =
                rr_ui_petal_tooltip_init(id, rarity);
            rr_ui_container_add_element(this->window,
                                        this->petal_tooltips[id][rarity]);
            // remember that these don't have a container
        }
    }

    rr_assets_init(this);

    rr_local_storage_get_bytes("debug",
                               &this->cache.displaying_debug_information);
    rr_local_storage_get_bytes("loadout", &this->cache.loadout);
    rr_local_storage_get_bytes("props", &this->cache.map_props);
    rr_local_storage_get_bytes("wave_start_percent", &this->cache.wave_start_percent);
    rr_local_storage_get_bytes("screen_shake", &this->cache.screen_shake);
    rr_local_storage_get_bytes("ui_hitboxes", &this->cache.show_ui_hitbox);
    rr_local_storage_get_bytes("slots_count", &this->cache.slots_unlocked);
    rr_local_storage_get_bytes("mouse", &this->cache.use_mouse);
    rr_local_storage_get_bytes("nickname", &this->cache.nickname);

    rr_local_storage_get_id_rarity("inventory", &this->inventory[0][0], rr_petal_id_max, rr_rarity_id_max);
    rr_local_storage_get_id_rarity("mob gallery", &this->cache.mob_kills[0][0], rr_mob_id_max, rr_rarity_id_max);
    // clang-format on
    this->tiles_size = 3;
}

void rr_game_websocket_on_event_function(enum rr_websocket_event_type type,
                                         void *data, void *captures,
                                         uint64_t size)
{
    struct rr_game *this = captures;
    switch (type)
    {
    case rr_websocket_event_type_open:
        this->socket_pending = 0;
        puts("websocket opened");
        break;
    case rr_websocket_event_type_close:
        // memset the clients
        this->socket_pending = 0;
        this->socket_ready = 0;
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
            uint64_t verification =
                proto_bug_read_uint64(&encoder, "verification");
            proto_bug_read_uint32(&encoder, "useless bytes");
            this->socket.clientbound_encryption_key =
                proto_bug_read_uint64(&encoder, "c encryption key");
            this->socket.serverbound_encryption_key =
                proto_bug_read_uint64(&encoder, "s encryption key");

            // respond
            struct proto_bug verify_encoder;
            proto_bug_init(&verify_encoder, &output_packet[0]);
            proto_bug_write_uint64(&verify_encoder, rr_get_rand(),
                                   "useless bytes");
            proto_bug_write_uint64(&verify_encoder, verification,
                                   "verification");
            uint64_t token_size = strlen(this->socket.rivet_player_token);
            uint64_t uuid_size = strlen(this->rivet_account.uuid);
            proto_bug_write_varuint(&verify_encoder, token_size,
                                    "rivet token size");
            proto_bug_write_varuint(&verify_encoder, uuid_size, "uuid size");
            proto_bug_write_string(&verify_encoder, this->socket.rivet_player_token,
                                   token_size, "rivet token");
            proto_bug_write_string(&verify_encoder, this->rivet_account.uuid,
                                   uuid_size, "rivet uuid");
            rr_websocket_send(&this->socket, verify_encoder.start,
                              verify_encoder.current);
            this->socket_ready = 1;
            return;
        }

        this->socket.clientbound_encryption_key =
            rr_get_hash(this->socket.clientbound_encryption_key);
        rr_decrypt(data, size, this->socket.clientbound_encryption_key);
        switch (proto_bug_read_uint8(&encoder, "header"))
        {
        case 0:
        {
            this->simulation_ready = 1;
            rr_simulation_read_binary(this, &encoder);
            struct proto_bug encoder2;
            proto_bug_init(&encoder2, output_packet);
            proto_bug_write_uint8(&encoder2, 0, "header");
            proto_bug_write_uint8(&encoder2, 0, "movement type");
            uint8_t movement_flags = 0;
            movement_flags |=
                (rr_bitset_get(this->input_data->keys_pressed, 'W') ||
                 rr_bitset_get(this->input_data->keys_pressed, 38))
                << 0;
            movement_flags |=
                (rr_bitset_get(this->input_data->keys_pressed, 'A') ||
                 rr_bitset_get(this->input_data->keys_pressed, 37))
                << 1;
            movement_flags |=
                (rr_bitset_get(this->input_data->keys_pressed, 'S') ||
                 rr_bitset_get(this->input_data->keys_pressed, 40))
                << 2;
            movement_flags |=
                (rr_bitset_get(this->input_data->keys_pressed, 'D') ||
                 rr_bitset_get(this->input_data->keys_pressed, 39))
                << 3;
            movement_flags |= this->input_data->mouse_buttons << 4;
            movement_flags |= rr_bitset_get(this->input_data->keys_pressed, 32)
                              << 4;
            movement_flags |= rr_bitset_get(this->input_data->keys_pressed, 16)
                              << 5;
            movement_flags |= this->cache.use_mouse << 6;
            proto_bug_write_uint8(&encoder2, movement_flags,
                                  "movement kb flags");
            proto_bug_write_float32(&encoder2,
                                    this->input_data->mouse_x -
                                        this->renderer->width / 2,
                                    "mouse x");
            proto_bug_write_float32(&encoder2,
                                    this->input_data->mouse_y -
                                        this->renderer->height / 2,
                                    "mouse y");
            rr_websocket_send(&this->socket, encoder2.start, encoder2.current);
            break;
        }
        case 69:
        {
            this->ticks_until_game_start =
                proto_bug_read_uint8(&encoder, "countdown");
            for (uint32_t i = 0; i < 4; ++i)
            {
                this->squad_members[i].in_use =
                    proto_bug_read_uint8(&encoder, "bitbit");
                this->squad_members[i].ready =
                    proto_bug_read_uint8(&encoder, "ready");
                this->squad_members[i].requested_start_wave_percent =
                    proto_bug_read_float32(&encoder,
                                           "requested start wave percent");
                uint32_t length = proto_bug_read_varuint(&encoder, "nick size");
                proto_bug_read_string(&encoder, &this->squad_members[i].name[0],
                                      length, "nick");
                this->squad_members[i].name[length] = 0;
                for (uint32_t j = 0; j < 20; ++j)
                {
                    this->squad_members[i].loadout[j].id =
                        proto_bug_read_uint8(&encoder, "id");
                    this->squad_members[i].loadout[j].rarity =
                        proto_bug_read_uint8(&encoder, "rar");
                }
            }
            struct proto_bug encoder2;
            proto_bug_init(&encoder2, output_packet);
            proto_bug_write_uint8(&encoder2, 70, "header");
            proto_bug_write_float32(&encoder2, this->cache.wave_start_percent,
                                    "requested wave");
            proto_bug_write_uint8(&encoder2, this->cache.slots_unlocked * 2,
                                  "loadout count");
            for (uint32_t i = 0; i < this->cache.slots_unlocked * 2; ++i)
            {
                proto_bug_write_uint8(&encoder2, this->cache.loadout[i].id,
                                      "id");
                proto_bug_write_uint8(&encoder2, this->cache.loadout[i].rarity,
                                      "rarity");
            }
            // write nickname
            rr_websocket_send(&this->socket, encoder2.start, encoder2.current);
            encoder2.current = encoder2.start;
            proto_bug_init(&encoder2, output_packet);
            proto_bug_write_uint8(&encoder2, 71, "header");
            uint32_t len = strlen(&this->cache.nickname[0]);
            proto_bug_write_varuint(&encoder2, len, "nick length");
            proto_bug_write_string(&encoder2, &this->cache.nickname[0], len,
                                   "nick");
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
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(this->renderer, &state);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x, physical->lerp_y);
    rr_component_drop_render(entity, this);
    rr_renderer_context_state_free(this->renderer, &state);
}

void render_health_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(this->renderer, &state);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x,
                          physical->lerp_y + physical->radius + 30);
    rr_component_health_render(entity, this);
    rr_renderer_context_state_free(this->renderer, &state);
}

void render_mob_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(this->renderer, &state);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x, physical->lerp_y);
    rr_component_mob_render(entity, this);
    rr_renderer_context_state_free(this->renderer, &state);
}

void render_petal_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(this->renderer, &state);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x, physical->lerp_y);
    rr_component_petal_render(entity, this);
    rr_renderer_context_state_free(this->renderer, &state);
}

void render_flower_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(this->renderer, &state);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x, physical->lerp_y);
    rr_component_flower_render(entity, this);
    rr_renderer_context_state_free(this->renderer, &state);
}

void render_web_component(EntityIdx entity, void *_captures)
{
    struct rr_game *this = _captures;
    struct rr_renderer_context_state state;
    rr_renderer_context_state_init(this->renderer, &state);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this->simulation, entity);
    rr_renderer_translate(this->renderer, physical->lerp_x, physical->lerp_y);
    rr_component_web_render(entity, this);
    rr_renderer_context_state_free(this->renderer, &state);
}

void player_info_finder(struct rr_game *this)
{
    struct rr_simulation *simulation = this->simulation;
    uint8_t counter = 1;
    memset(&this->player_infos, 0, sizeof this->player_infos);
    this->player_infos[0] = this->player_info->parent_id;
    for (EntityIdx i = 1; i < RR_MAX_ENTITY_COUNT; ++i)
        if (rr_bitset_get(simulation->player_info_tracker, i) &&
            i != this->player_info->parent_id)
            this->player_infos[counter++] = i;
}

static void render_background(struct rr_component_player_info *player_info,
                              struct rr_game *this, uint32_t prop_amount)
{
    if (this->cache.ourpetsnake_mode)
        return;
    double scale = player_info->lerp_camera_fov * this->renderer->scale;
    double leftX =
        player_info->lerp_camera_x - this->renderer->width / (2 * scale);
    double rightX =
        player_info->lerp_camera_x + this->renderer->width / (2 * scale);
    double topY =
        player_info->lerp_camera_y - this->renderer->height / (2 * scale);
    double bottomY =
        player_info->lerp_camera_y + this->renderer->height / (2 * scale);

#define GRID_SIZE (256)
    double newLeftX = floorf(leftX / GRID_SIZE) * GRID_SIZE;
    double newTopY = floorf(topY / GRID_SIZE) * GRID_SIZE;
    for (; newLeftX < rightX; newLeftX += GRID_SIZE)
    {
        for (double currY = newTopY; currY < bottomY; currY += GRID_SIZE)
        {
            uint32_t tile_index = (uint32_t)((newLeftX / GRID_SIZE + 1) *
                                             (currY / GRID_SIZE + 2)) %
                                  this->tiles_size;
            struct rr_renderer_context_state state;
            rr_renderer_context_state_init(this->renderer, &state);
            rr_renderer_translate(this->renderer, newLeftX + GRID_SIZE / 2,
                                  currY + GRID_SIZE / 2);
            rr_renderer_draw_image(this->renderer, this->tiles + tile_index);
            rr_renderer_context_state_free(this->renderer, &state);
        }
    }

#define render_map_feature                                                     \
    struct rr_renderer_context_state state;                                    \
    float theta = ((double)(uint32_t)(rr_get_hash(i + 200000))) /              \
                  ((double)UINT32_MAX) * (M_PI * 2);                           \
    float distance = sqrtf(((double)(uint32_t)(rr_get_hash(i + 300000))) /     \
                           ((double)UINT32_MAX)) *                             \
                     1600.0;                                                   \
    float rotation = ((double)(uint32_t)(rr_get_hash(i + 400000))) /           \
                     ((double)UINT32_MAX) * (M_PI * 2);                        \
    float x = distance * sinf(theta);                                          \
    float y = distance * cosf(theta);                                          \
    if (x < leftX - (selected_feature == 8 ? 400 : 100))                       \
        continue;                                                              \
    if (x > rightX + (selected_feature == 8 ? 400 : 100))                      \
        continue;                                                              \
    if (y < topY - (selected_feature == 8 ? 400 : 100))                        \
        continue;                                                              \
    if (y > bottomY + (selected_feature == 8 ? 400 : 100))                     \
        continue;                                                              \
    rr_renderer_context_state_init(this->renderer, &state);                    \
    rr_renderer_translate(this->renderer, x, y);                               \
    rr_renderer_rotate(this->renderer, rotation);                              \
    rr_renderer_draw_image(this->renderer,                                     \
                           &this->background_features[selected_feature]);      \
    rr_renderer_context_state_free(this->renderer, &state);

    rr_renderer_set_global_alpha(this->renderer, 0.75f);

    // draw background features
    for (uint64_t i = 0; i < prop_amount;)
    {
        uint64_t selected_feature;
        // any number between 0-8 and is not 1. 1 is water lettuce
        // which is disabled for now
        do
        {
            selected_feature = rr_get_hash(i) % 8;
            i++;
        } while (selected_feature == 1);

        render_map_feature
    }
    // trees over everything
    for (uint64_t i = 1000000; i < (1000000 + prop_amount / 50); i++)
    {
        uint64_t selected_feature = 8;
        render_map_feature
    }

#undef GRID_SIZE
#undef render_map_feature
}

void rr_game_tick(struct rr_game *this, float delta)
{
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    validate_loadout(this);

    rr_local_storage_store_bytes(
        "debug", &this->cache.displaying_debug_information,
        sizeof this->cache.displaying_debug_information);
    rr_local_storage_store_bytes("loadout", &this->cache.loadout,
                                 sizeof this->cache.loadout);
    rr_local_storage_store_bytes("props", &this->cache.map_props,
                                 sizeof this->cache.map_props);
    rr_local_storage_store_bytes("wave_start_percent",
                                 &this->cache.wave_start_percent,
                                 sizeof this->cache.wave_start_percent);
    rr_local_storage_store_bytes("screen_shake", &this->cache.screen_shake,
                                 sizeof this->cache.screen_shake);
    rr_local_storage_store_bytes("ui_hitboxes", &this->cache.show_ui_hitbox,
                                 sizeof this->cache.show_ui_hitbox);
    rr_local_storage_store_bytes("slots_count", &this->cache.slots_unlocked,
                                 sizeof this->cache.slots_unlocked);
    rr_local_storage_store_bytes("mouse", &this->cache.use_mouse,
                                 sizeof this->cache.use_mouse);
    rr_local_storage_store_bytes("nickname", &this->cache.nickname,
                                 strlen(&this->cache.nickname[0]));

    rr_local_storage_store_id_rarity("inventory", &this->inventory[0][0],
                                     rr_petal_id_max, rr_rarity_id_max);
    rr_local_storage_store_id_rarity("mob gallery",
                                     &this->cache.mob_kills[0][0],
                                     rr_mob_id_max, rr_rarity_id_max);

    double time = start.tv_sec * 1000000 + start.tv_usec;
    rr_renderer_set_transform(this->renderer, 1, 0, 0, 0, 1, 0);
    struct rr_renderer_context_state grand_state;
    rr_renderer_context_state_init(this->renderer, &grand_state);

    if (this->simulation_ready)
    {
        rr_simulation_tick(this->simulation, delta);

        this->renderer->state.filter.amount = 0;
        struct rr_renderer_context_state state1;
        struct rr_renderer_context_state state2;
        player_info_finder(this);
        if (this->player_info != NULL)
        {
            // screen shake
            rr_renderer_context_state_init(this->renderer, &state1);
            struct rr_component_player_info *player_info = this->player_info;
            rr_renderer_translate(this->renderer, this->renderer->width / 2,
                                  this->renderer->height / 2);
            rr_renderer_scale(this->renderer, player_info->lerp_camera_fov *
                                                  this->renderer->scale);
            rr_renderer_translate(this->renderer, -player_info->lerp_camera_x,
                                  -player_info->lerp_camera_y);

            if (this->cache.screen_shake &&
                player_info->flower_id != RR_NULL_ENTITY)
            {
                if (rr_simulation_get_physical(this->simulation,
                                               player_info->flower_id)
                        ->server_animation_tick != 0)
                {
                    float r = rr_frand() * 5;
                    float a = rr_frand() * 2 * M_PI;
                    rr_renderer_translate(this->renderer, r * cosf(a),
                                          r * sinf(a));
                }
            }

            uint32_t alpha = (uint32_t)(player_info->lerp_camera_fov * 51)
                             << 24;
            rr_renderer_context_state_init(this->renderer, &state2);
            rr_renderer_set_transform(this->renderer, 1, 0, 0, 0, 1, 0);
            rr_renderer_set_fill(this->renderer, 0xff45230a);
            rr_renderer_fill_rect(this->renderer, 0, 0, this->renderer->width,
                                  this->renderer->height);
            rr_renderer_set_fill(this->renderer, alpha);
            rr_renderer_fill_rect(this->renderer, 0, 0, this->renderer->width,
                                  this->renderer->height);
            rr_renderer_context_state_free(this->renderer, &state2);
            rr_renderer_context_state_init(this->renderer, &state2);

            struct rr_component_arena *arena =
                rr_simulation_get_arena(this->simulation, 1);
            rr_renderer_begin_path(this->renderer);
            rr_renderer_arc(this->renderer, 0, 0, arena->radius);
            rr_renderer_set_fill(this->renderer, 0xff45230a);
            rr_renderer_fill(this->renderer);
            rr_renderer_clip(this->renderer);

            rr_renderer_set_line_width(this->renderer, 1.0f);
            rr_renderer_set_stroke(this->renderer, alpha);
            rr_renderer_set_global_alpha(this->renderer, 1);

            render_background(player_info, this, this->cache.map_props * 750);

            rr_renderer_context_state_free(this->renderer, &state2);

            rr_simulation_for_each_health(this->simulation, this,
                                          render_health_component);
            rr_simulation_for_each_drop(this->simulation, this,
                                        render_drop_component);
            rr_simulation_for_each_web(this->simulation, this,
                                       render_web_component);
            rr_simulation_for_each_mob(this->simulation, this,
                                       render_mob_component);
            rr_simulation_for_each_petal(this->simulation, this,
                                         render_petal_component);
            rr_simulation_for_each_flower(this->simulation, this,
                                          render_flower_component);
            rr_renderer_context_state_free(this->renderer, &state1);
        }
    }
    else
    {
        // render background but different
        struct rr_component_player_info custom_player_info;
        rr_component_player_info_init(&custom_player_info, 0);
        custom_player_info.lerp_camera_fov = 0.9;
        uint32_t alpha = (uint32_t)(0.9 * 51) << 24;
        struct rr_renderer_context_state state;
        rr_renderer_context_state_init(this->renderer, &state);
        rr_renderer_set_transform(this->renderer, 1, 0, 0, 0, 1, 0);
        rr_renderer_set_fill(this->renderer, 0xff45230a);
        rr_renderer_fill_rect(this->renderer, 0, 0, this->renderer->width,
                              this->renderer->height);
        rr_renderer_set_fill(this->renderer, alpha);
        rr_renderer_fill_rect(this->renderer, 0, 0, this->renderer->width,
                              this->renderer->height);
        rr_renderer_context_state_free(this->renderer, &state);
        rr_renderer_context_state_init(this->renderer, &state);
        rr_renderer_translate(this->renderer, this->renderer->width * 0.5f,
                              this->renderer->height * 0.5f);
        render_background(&custom_player_info, this,
                          this->cache.map_props * 750);
        rr_renderer_context_state_free(this->renderer, &state);
    }
    // ui
    this->crafting_data.animation -= delta;
    if (this->crafting_data.animation < 0)
        this->crafting_data.animation = 0;
    this->prev_focused = this->focused;
    rr_ui_container_refactor(this->window);
    rr_ui_render_element(this->window, this);
    if (!this->block_ui_input)
    {
        this->window->poll_events(this->window, this);
        if (this->pressed != NULL && !rr_ui_mouse_over(this->pressed, this))
            this->pressed = NULL;
        if (this->focused != NULL)
            this->focused->on_event(this->focused, this);
        else
            this->window->on_event(this->window, this);
        if (this->prev_focused != this->focused && this->prev_focused != NULL)
            this->prev_focused->on_event(this->prev_focused, this);
    }
    this->block_ui_input = 0;
#ifndef EMSCRIPTEN
    lws_service(this->socket.socket_context, -1);
#endif
    if (this->socket_ready)
    {
#ifndef RIVET_BUILD
        if (rr_bitset_get_bit(this->input_data->keys_pressed_this_tick,
                              75 /* k */))
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, output_packet);
            proto_bug_write_uint8(&encoder, 3, "header");
            proto_bug_write_uint8(&encoder, 2, "cheat type");
            rr_websocket_send(&this->socket, encoder.start, encoder.current);
        }
        if (rr_bitset_get_bit(this->input_data->keys_pressed_this_tick,
                              76 /* l */))
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, output_packet);
            proto_bug_write_uint8(&encoder, 3, "header");
            proto_bug_write_uint8(&encoder, 1, "cheat type");
            rr_websocket_send(&this->socket, encoder.start, encoder.current);
        }
        if (rr_bitset_get_bit(this->input_data->keys_pressed_this_tick,
                              86 /* v */))
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, output_packet);
            proto_bug_write_uint8(&encoder, 3, "header");
            proto_bug_write_uint8(&encoder, 3, "cheat type");
            rr_websocket_send(&this->socket, encoder.start, encoder.current);
        }
#endif
        if (this->simulation_ready)
        {
            struct proto_bug encoder;
            proto_bug_init(&encoder, output_packet);
            proto_bug_write_uint8(&encoder, 2, "header");
            uint8_t should_write = 0;
            uint8_t switch_all = rr_bitset_get_bit(
                this->input_data->keys_pressed_this_tick, 'X');
            for (uint8_t n = 0; n < this->cache.slots_unlocked; ++n)
                if (rr_bitset_get_bit(this->input_data->keys_pressed_this_tick,
                                      48 + n) ||
                    switch_all)
                {
                    proto_bug_write_uint8(&encoder, n == 0 ? 10 : n,
                                          "petal switch");
                    should_write = 1;
                }
            if (should_write)
            {
                proto_bug_write_uint8(&encoder, 0, "petal switch");
                rr_websocket_send(&this->socket, encoder.start,
                                  encoder.current);
            }
        }
    }
    if (rr_bitset_get_bit(this->input_data->keys_pressed_this_tick,
                          186 /* ; */))
        this->cache.displaying_debug_information ^= 1;

    if (this->cache.displaying_debug_information)
    {
        struct rr_renderer_context_state state;
        rr_renderer_context_state_init(this->renderer, &state);
        rr_renderer_set_text_size(this->renderer, 12);
        rr_renderer_set_line_width(this->renderer, 12 * 0.12);
        rr_renderer_set_text_baseline(this->renderer, 2);
        rr_renderer_set_fill(this->renderer, 0xffffffff);
        rr_renderer_set_text_align(this->renderer, 2);
        rr_renderer_translate(this->renderer, this->renderer->width - 5,
                              this->renderer->height - 5);
        static char debug_mspt[100];
        long tick_sum = 0;
        long tick_max = 0;
        long frame_sum = 0;
        long frame_max = 0;
        for (uint32_t i = 0; i < RR_DEBUG_POLL_SIZE; ++i)
        {
            long t_t = this->debug_info.tick_times[i];
            long f_t = this->debug_info.frame_times[i];
            tick_sum += t_t;
            frame_sum += f_t;
            if (t_t > tick_max)
                tick_max = t_t;
            if (f_t > frame_max)
                frame_max = f_t;
        }

        debug_mspt[sprintf(
            debug_mspt,
            "tick time (avg/max): %.1f/%.1f | frame time (avg/max): %.1f/%.1f",
            tick_sum * 0.001f / RR_DEBUG_POLL_SIZE, tick_max * 0.001f,
            frame_sum * 0.001f / RR_DEBUG_POLL_SIZE, frame_max * 0.001f)] = 0;
        rr_renderer_stroke_text(this->renderer, debug_mspt, 0, 0);
        rr_renderer_fill_text(this->renderer, debug_mspt, 0, 0);
        debug_mspt[sprintf(debug_mspt, "ctx calls: %d",
                           rr_renderer_get_op_size())] = 0;
        rr_renderer_stroke_text(this->renderer, debug_mspt, 0, -15);
        rr_renderer_fill_text(this->renderer, debug_mspt, 0, -15);
        rr_renderer_context_state_free(this->renderer, &state);
        // rr_renderer_stroke_text
    }
    rr_renderer_context_state_free(this->renderer, &grand_state);

    rr_renderer_execute_instructions();
    rr_renderer_reset_instruction_queue();
    gettimeofday(&end, NULL);
    long time_elapsed =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    long frame_time = delta * 1000000.0f;

    this->debug_info.tick_times[this->debug_info.frame_pos] = time_elapsed;
    this->debug_info.frame_times[this->debug_info.frame_pos] = frame_time;
    this->debug_info.frame_pos =
        (this->debug_info.frame_pos + 1) % RR_DEBUG_POLL_SIZE;

    memset(this->input_data->keys_pressed_this_tick, 0, RR_BITSET_ROUND(256));
    memset(this->input_data->keys_released_this_tick, 0, RR_BITSET_ROUND(256));
    memset(this->input_data->keycodes_pressed_this_tick, 0,
           RR_BITSET_ROUND(256));
    this->input_data->mouse_buttons_up_this_tick = 0;
    this->input_data->mouse_buttons_down_this_tick = 0;
    this->input_data->mouse_state_this_tick = 0;
    this->input_data->prev_mouse_x = this->input_data->mouse_x;
    this->input_data->prev_mouse_y = this->input_data->mouse_y;
}

void rr_game_connect_socket(struct rr_game *this)
{
    memset(this->simulation, 0, sizeof *this->simulation);
    for (uint8_t i = 0; i < this->cache.slots_unlocked; ++i)
        this->protocol_state |= ((1 | (1 << 10)) << i);
    this->socket_ready = 0;
    this->simulation_ready = 0;
    rr_websocket_init(&this->socket);
    this->socket.user_data = this;
    this->socket.on_event = rr_game_websocket_on_event_function;

#ifdef RIVET_BUILD
    this->rivet_lobby_pending = 1;
    rr_rivet_lobbies_find(this);
#else
#ifdef RR_WINDOWS
    rr_websocket_connect_to(&this->socket, "127.0.0.1", 1234, 0);
#else
    // for testing
    // if (!this->socket.rivet_player_token)
    // {
    //     this->socket.rivet_player_token = calloc(10, 1);
    //     this->socket.uuid = calloc(10, 1);
    // }
    rr_websocket_connect_to(&this->socket, "127.0.0.1", 1234, 0);
    // rr_websocket_connect_to(&this->socket, "45.79.197.197", 1234, 0);
#endif
#endif
}

struct on_find_captures
{
    struct rr_game *game;
    struct rr_websocket *socket;
};

void rr_rivet_lobby_on_find(char *s, char *token, uint16_t port, void *_game)
{
    struct rr_game *game = _game;
    game->rivet_lobby_pending = 0;
    if (port == 0 || s == NULL || token == NULL)
    {
        // error;
        game->socket_pending = 0;
        game->socket_ready = 0;
        return;
    }
    game->socket_pending = 1;
    // rr_websocket_connect_to(&game->socket, "127.0.0.1", 1234, 0);

    if (port == 443)
        rr_websocket_connect_to(&game->socket, s, port, 1);
    else
        rr_websocket_connect_to(&game->socket, s, port, 0);
    free(s);
    captures->socket->rivet_player_token = strdup(token);
    // free(token);
    game->socket.rivet_player_token = token;
    // game->socket.uuid = game->rivet_account.uuid;
}
