#pragma once

#include <stdint.h>

#include <Shared/Bitset.h>

struct rr_input_data
{
    uint8_t mouse_buttons;
    uint8_t mouse_state;
    // c version of addeventlistener("mouse")
    uint8_t mouse_state_this_tick;
    uint8_t mouse_buttons_up_this_tick;
    uint8_t mouse_buttons_down_this_tick;
    float mouse_x;
    float mouse_y;
    float prev_mouse_x;
    float prev_mouse_y;
    float scroll_delta;
    uint8_t keys_pressed[RR_BITSET_ROUND(256)];
    // c version of addeventlistener("keydown")
    uint8_t keys_pressed_this_tick[RR_BITSET_ROUND(256)];
    uint8_t keys_released_this_tick[RR_BITSET_ROUND(256)];
};

void rr_input_data_init(struct rr_input_data *);
