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

#include <stdarg.h>
#include <stdint.h>

struct rr_ui_element;
struct rr_game;

struct rr_ui_element *rr_ui_h_container_init(struct rr_ui_element *, int32_t,
                                             int32_t, ...);
struct rr_ui_element *rr_ui_v_container_init(struct rr_ui_element *, int32_t,
                                             int32_t, ...);

struct rr_ui_element *rr_ui_set_background(struct rr_ui_element *, uint32_t);
struct rr_ui_element *rr_ui_set_fill_stroke(struct rr_ui_element *, uint32_t,
                                            uint32_t);
struct rr_ui_element *rr_ui_set_justify(struct rr_ui_element *, int8_t, int8_t);
struct rr_ui_element *rr_ui_h_pah(struct rr_ui_element *, float);
struct rr_ui_element *rr_ui_v_pad(struct rr_ui_element *, float);
struct rr_ui_element *rr_ui_pad(struct rr_ui_element *, float);
struct rr_ui_element *rr_ui_justify_all(struct rr_ui_element *, int8_t);

void rr_ui_h_container_set(struct rr_ui_element *);
void rr_ui_v_container_set(struct rr_ui_element *);
void rr_ui_choose_container_set(struct rr_ui_element *);
void rr_ui_grid_container_set(struct rr_ui_element *);

void rr_ui_container_refactor(struct rr_ui_element *, struct rr_game *);