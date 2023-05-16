#pragma once

#include <stdint.h>

struct rr_input_data
{
    uint8_t mouse_buttons;
    uint8_t mouse_state;
    float mouse_x;
    float mouse_y;
    uint8_t keys[256 >> 3];
};

void rr_input_data_init(struct rr_input_data *);
