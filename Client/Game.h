#pragma once

struct rr_game
{
    struct rr_websocket *socket;
    struct rr_renderer *renderer;
    struct rr_input_data *input_data;
    struct rr_simulation *simulation;
};

void rr_game_tick(struct rr_game *);
