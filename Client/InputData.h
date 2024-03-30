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

#include <stdint.h>

#include <Shared/Bitset.h>

struct rr_input_touch
{
    float touch_x;
    float touch_y;
    uint8_t identifier;
    uint8_t active;
};

struct rr_input_data
{
    char *clipboard;
    uint8_t keys_pressed[RR_BITSET_ROUND(256)];
    // c version of addeventlistener("keydown")
    uint8_t keys_pressed_this_tick[RR_BITSET_ROUND(256)];
    uint8_t keys_released_this_tick[RR_BITSET_ROUND(256)];

    uint32_t keycodes_pressed_this_tick[16];
    uint32_t keycodes_length;
    struct rr_input_touch touches[16];
    uint8_t touch_length;
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
};

void rr_input_data_init(struct rr_input_data *);
