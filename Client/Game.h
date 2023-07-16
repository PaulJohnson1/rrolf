#pragma once

#include <Client/Renderer/Renderer.h>
#include <Client/Socket.h>
#include <Client/Ui/Ui.h>
#include <Shared/Entity.h>

#include <Shared/StaticData.h>
#include <Shared/pb.h>

struct rr_game_loadout_petal
{
    uint8_t id;
    uint8_t rarity;
};

struct rr_game_squad_client
{
    uint8_t in_use;
    uint8_t ready;
    struct rr_game_loadout_petal loadout[20];
};

struct rr_game_crafting_data
{
    float animation;
    uint32_t count;
    uint32_t success_count;
    uint8_t crafting_id;
    uint8_t crafting_rarity;
};

struct rr_rivet_account
{
    char account_number[6];
    char token[300];
    char uuid[100];
    char name[100];
    char avatar_url[200];
};

struct rr_game_debug_info
{
    uint8_t count;
    long last_tick_time;
    long max_frame_time;
    long cumulative_frame_time;
    long max_tick_time;
    long cumulative_tick_time;
};

struct rr_game
{
    struct rr_game_crafting_data crafting_data;
    struct rr_game_debug_info debug_info;
    // petal rendering cache
    struct rr_renderer static_petals[rr_petal_id_max][rr_rarity_id_max];

    // mob assets cache
    struct rr_renderer mob_pteranodon_body;
    struct rr_renderer mob_pteranodon_wings[2];

    struct rr_renderer mob_trex_head;
    struct rr_renderer mob_trex_body;
    struct rr_renderer mob_trex_tail;
    struct rr_renderer mob_trex_legs[2]; // contains: [{leg, arm}, {arm, leg}]

    struct rr_renderer mob_triceratops_head;
    struct rr_renderer mob_triceratops_body;
    struct rr_renderer mob_triceratops_tail;
    struct rr_renderer mob_triceratops_legs[2];

    struct rr_renderer mob_dakotaraptor_body;
    struct rr_renderer mob_dakotaraptor_head;
    struct rr_renderer mob_dakotaraptor_tail;
    struct rr_renderer mob_dakotaraptor_wings[2];

    struct rr_renderer mob_stump;

    // background
    struct rr_renderer tiles[3];
    struct rr_renderer background_features[9];

    struct rr_rivet_account rivet_account;
    struct rr_game_squad_client squad_members[4];
    struct rr_websocket socket;
    struct rr_ui_element *petal_tooltips[rr_petal_id_max][rr_rarity_id_max];
    struct rr_ui_element *mob_tooltips[rr_mob_id_max][rr_rarity_id_max];
    struct rr_ui_element *squad_info_tooltip;
    struct rr_ui_element *rivet_info_tooltip;
    uint32_t inventory[rr_petal_id_max][rr_rarity_id_max];
    struct rr_renderer *renderer;
    struct rr_input_data *input_data;
    struct rr_simulation *simulation;
    struct rr_component_player_info *player_info;

    uint32_t protocol_state;
    float expanding_circle_radius;
    float map_prop_count;
    struct rr_game_loadout_petal loadout[20];
    EntityIdx player_infos[4];

    uint8_t socket_ready;
    uint8_t socket_pending;
    uint8_t simulation_ready;
    int8_t ticks_until_game_start;
    uint8_t bottom_ui_open; // 0 = none, 1 = inv, 2 = crafting
    uint8_t top_ui_open;    // 0 = none, 1 = settings, 2 = changelog
    uint8_t tiles_size;

    uint8_t block_ui_input;
    uint8_t use_mouse;
    uint8_t displaying_debug_information;
    uint8_t show_ui_hitbox;
    uint8_t screen_shake;

    struct rr_ui_element *window;
    struct rr_ui_element *prev_focused;
    struct rr_ui_element *focused;
};

void rr_game_init(struct rr_game *);
void rr_game_tick(struct rr_game *, float);
void rr_game_connect_socket(struct rr_game *);
void rr_simulation_read_binary(struct rr_game *, struct proto_bug *);
