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

#include <Client/Ui/Engine.h>
#include <Client/Ui/Ui.h>

struct rr_ui_element *rr_ui_anti_afk_container_init()
{
    struct rr_ui_element *e = rr_ui_v_container_init(
        rr_ui_container_init(), 0, 15, rr_ui_text_init("AFK Check", 20, -1),
        rr_ui_text_init("Are you here?", 20, 0xffffffff),
        rr_ui_labeled_button_init("I'm here", 10, 0), 0);

    e->x = 100;
    e->y = 100;
    // e->

    return e;
}
