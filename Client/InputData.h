#pragma once

#include <stdint.h>

struct rr_input_data
{
    uint8_t mouse_buttons;
    uint8_t mouse_state;
    float mouse_x;
    float mouse_y;
    uint8_t keys_pressed[256 >> 3];
    // c verson of addeventlstener("keydown")
    uint8_t keys_pressed_this_tick[256 >> 3];
    uint8_t keys_released_this_tick[256 >> 3];
};

void rr_input_data_init(struct rr_input_data *);
