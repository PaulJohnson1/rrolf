#pragma once

#include <Shared/Entity.h>
#include <Client/Ui/Element.h>
#include <Client/Socket.h>

#include <Shared/StaticData.h>

struct rr_game_squad_client
{
    uint8_t in_use;
};

struct rr_global_elements
{
    struct rr_ui_element *respawn_label;
    struct rr_ui_element *title_screen;
    struct rr_ui_element *loadout;
    struct rr_ui_element *wave_info;
    struct rr_ui_element *inventory;
};

struct rr_game
{
    struct rr_websocket socket;
    struct rr_renderer *renderer;
    struct rr_renderer static_petals[rr_petal_id_max][rr_rarity_id_max];
    struct rr_input_data *input_data;
    struct rr_simulation *simulation;
    struct rr_ui_element *global_container;
    struct rr_global_elements ui_elements;
    uint8_t displaying_debug_information:1;
    uint8_t socket_ready:1;
    uint8_t socket_pending:1;
    uint8_t simulation_ready:1;
    struct rr_game_squad_client squad_members[4];
};

void rr_game_init(struct rr_game *);
void rr_game_tick(struct rr_game *, float);
void rr_game_connect_socket(struct rr_game *);
