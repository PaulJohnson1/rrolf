#pragma once

#include <Client/Renderer/Renderer.h>
#include <Client/Socket.h>
#include <Client/Ui/Ui.h>
#include <Shared/Entity.h>

#include <Shared/StaticData.h>

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
    uint32_t count;
    uint32_t success_count;
    float animation;
    uint8_t crafting_id;
    uint8_t crafting_rarity;
};

struct rr_game
{
    // petal rendering cache
    struct rr_renderer static_petals[rr_petal_id_max][rr_rarity_id_max];

    // mob assets cache
    struct rr_renderer mob_pteranodon_wings[2];
    struct rr_renderer mob_pteranodon_body;

    struct rr_renderer mob_trex_legs[2]; // contains: [{leg, arm}, {arm, leg}]
    struct rr_renderer mob_trex_body;
    struct rr_renderer mob_trex_body_line;
    struct rr_renderer mob_trex_tail_bottom;
    struct rr_renderer mob_trex_tail_top;
    struct rr_renderer mob_trex_head;

    struct rr_renderer mob_triceratops[7];

    struct rr_renderer mob_dakotaraptor[6];

    struct rr_renderer mob_stump;

    // background
    struct rr_renderer tiles[3];
    struct rr_renderer background_features[9];

    struct rr_game_squad_client squad_members[4];
    struct rr_websocket socket;
    struct rr_game_crafting_data crafting_data;
    struct rr_ui_element *petal_tooltips[rr_petal_id_max][rr_rarity_id_max];
    uint32_t inventory[rr_petal_id_max][rr_rarity_id_max];
    struct rr_renderer *renderer;
    struct rr_input_data *input_data;
    struct rr_simulation *simulation;
    uint32_t protocol_state;
    float expanding_circle_radius;
    struct rr_game_loadout_petal loadout[20];
    EntityIdx player_infos[4];
    uint8_t displaying_debug_information;
    uint8_t socket_ready;
    uint8_t socket_pending;
    uint8_t simulation_ready;
    uint8_t simulation_not_ready;
    int8_t ticks_until_game_start;
    uint8_t ui_open; // 0 = none, 1 = inv, 2 = crafting
    uint8_t false_ptr;
    uint8_t true_ptr;
    uint8_t tiles_size;

    struct rr_ui_element *window;
    struct rr_ui_element *prev_focused;
    struct rr_ui_element *focused;
};

void rr_game_init(struct rr_game *);
void rr_game_tick(struct rr_game *, float);
void rr_game_connect_socket(struct rr_game *);
