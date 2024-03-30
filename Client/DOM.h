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

void rr_dom_create_text_element(char const *, uint32_t);
void rr_dom_element_show(char const *);
void rr_dom_element_hide(char const *);
void rr_dom_element_update_position(char const *, float, float, float, float);
void rr_dom_retrieve_text(char const *, char *, uint32_t);
void rr_dom_set_text(char const *, char *);
void rr_copy_string(char const *);
void rr_page_reload(uint8_t);
uint8_t rr_dom_test_mobile();
void rr_page_open(char const *);