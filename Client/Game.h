// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <Client/Particle.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Socket.h>
#include <Client/Ui/Ui.h>
#include <Shared/Entity.h>
#include <Shared/Rivet.h>
#include <Shared/Squad.h>
#include <Shared/StaticData.h>
#include <Shared/pb.h>

#define RR_DEBUG_POLL_SIZE 10

enum rr_game_menu
{
    rr_game_menu_none,
    rr_game_menu_inventory,
    rr_game_menu_gallery,
    rr_game_menu_crafting,
    rr_game_menu_settings,
    rr_game_menu_account,
    rr_game_menu_dev_squad_panel
};

struct rr_game_debug_info
{
    uint8_t frame_pos;
    uint8_t websocket_pos;
    long tick_times[RR_DEBUG_POLL_SIZE];
    long frame_times[RR_DEBUG_POLL_SIZE];
    long message_sizes[RR_DEBUG_POLL_SIZE];
};

struct rr_game_crafting_data
{
    float animation;
    uint32_t count;
    uint32_t success_count;
    uint8_t crafting_id;
    uint8_t crafting_rarity;
};

struct rr_game_chat_message
{
    uint8_t type;
    char sender_name[16];
    char message[64];
};

struct rr_game_chat
{
    uint8_t chat_active; // 0 = inactive, 1 = local, 2 = squad
    uint8_t chat_type;
    uint32_t at;
    struct rr_game_chat_message messages[10];
    char sending[64];
};

// anything cross reload
struct rr_game_cache
{
    double experience;
    uint32_t mob_kills[rr_mob_id_max][rr_rarity_id_max];
    struct rr_id_rarity_pair loadout[20];
    uint8_t use_mouse;
    uint8_t displaying_debug_information;
    uint8_t tint_petals;
    uint8_t screen_shake;
    uint8_t low_performance_mode;
    char nickname[128];
};

struct rr_game_squad
{
    struct rr_squad_member squad_members[RR_SQUAD_MEMBER_COUNT];
    uint8_t squad_pos;
    uint8_t squad_private;
    char squad_code[16];
};

struct rr_developer_cheats
{
    float speed_percent;
};

struct rr_game
{
    struct rr_particle_manager particle_manager;
    struct rr_game_crafting_data crafting_data;
    struct rr_game_debug_info debug_info;
    struct rr_game_chat chat;
    struct rr_game_cache cache;
    struct rr_game_squad squad;
    struct rr_developer_cheats developer_cheats;
    struct rr_game_squad other_squads[RR_SQUAD_COUNT];

    struct rr_rivet_account rivet_account;
    struct rr_websocket socket;

    struct rr_ui_element *petal_tooltips[rr_petal_id_max][rr_rarity_id_max];
    struct rr_ui_element *mob_tooltips[rr_mob_id_max][rr_rarity_id_max];
    struct rr_ui_element *link_account_tooltip;
    struct rr_ui_element *inventory_tooltip;
    struct rr_ui_element *gallery_tooltip;
    struct rr_ui_element *craft_tooltip;
    struct rr_ui_element *settings_tooltip;
    struct rr_ui_element *account_tooltip;
    struct rr_ui_element *discord_tooltip;
    struct rr_ui_element *abandon_game_tooltip;
    struct rr_ui_element *experience_tooltip;
    struct rr_ui_element *link_reminder_tooltip;
    struct rr_ui_element *window;
    struct rr_ui_element *prev_focused;
    struct rr_ui_element *focused;
    struct rr_ui_element *pressed;
    struct rr_ui_element *anti_afk;

    struct rr_renderer *renderer;
    struct rr_input_data *input_data;
    struct rr_simulation *simulation;
    struct rr_simulation *deletion_simulation;
    struct rr_component_player_info *player_info;

    uint32_t inventory[rr_petal_id_max][rr_rarity_id_max];
    uint32_t failed_crafts[rr_petal_id_max][rr_rarity_id_max];
    uint8_t loadout_counts[rr_petal_id_max][rr_rarity_id_max];
    EntityIdx player_infos[RR_SQUAD_MEMBER_COUNT];
    uint64_t dev_flag;
    float lerp_delta;

    uint8_t socket_ready : 1;
    uint8_t socket_pending : 1;
    uint8_t joined_squad : 1;
    uint8_t simulation_ready : 1;
    uint8_t block_ui_input : 1;
    uint8_t is_mobile : 1;
    uint8_t logged_in : 1;
    uint8_t account_linked : 1;
    uint8_t is_dev;
    uint8_t socket_error;
    uint8_t menu_open;
    uint8_t ticks_until_text_cache;
    uint8_t selected_biome;
    uint8_t slots_unlocked;

    char rivet_player_token[400];
    char connect_code[16];
};

void rr_game_init(struct rr_game *);
void rr_game_tick(struct rr_game *, float);
void rr_game_connect_socket(struct rr_game *);
void rr_simulation_read_binary(struct rr_game *, struct proto_bug *);

void rr_game_websocket_on_event_function(enum rr_websocket_event_type, void *,
                                         void *, uint64_t);

uint32_t rr_game_get_adjusted_inventory_count(struct rr_game *, uint8_t,
                                              uint8_t);
