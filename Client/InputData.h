#pragma once

#include <stdint.h>

#include <Shared/Bitset.h>

struct rr_input_data
{
    uint8_t mouse_buttons;
    uint8_t mouse_state;
    uint8_t mouse_state_this_tick;
    uint8_t mouse_buttons_this_tick;
    float mouse_x;
    float mouse_y;
    uint8_t keys_pressed[RR_BITSET_ROUND(256)];
    // c verson of addeventlstener("keydown")
    uint8_t keys_pressed_this_tick[RR_BITSET_ROUND(256)];
    uint8_t keys_released_this_tick[RR_BITSET_ROUND(256)];
};

void rr_input_data_init(struct rr_input_data *);
