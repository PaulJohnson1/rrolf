#pragma once

#include <Shared/Entity.h>

struct rr_game
{
    uint8_t displaying_debug_information:1;
    uint8_t socket_ready:1;
    struct rr_websocket *socket;
    struct rr_renderer *renderer;
    struct rr_input_data *input_data;
    struct rr_simulation *simulation;
};

void rr_game_init(struct rr_game *);
void rr_game_tick(struct rr_game *, float delta);
