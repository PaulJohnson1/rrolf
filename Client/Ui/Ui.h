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

struct rr_game;
struct rr_squad_member;
struct rr_ui_element;
struct rr_game_squad_client;
struct rr_game_squad;

enum rr_ui_resizeable_type
{
    rr_ui_not_resizeable = 0,
    rr_ui_h_container = 1,
    rr_ui_v_container = 2,
    rr_ui_choose_container = 3,
    rr_ui_grid_container = 4,
    rr_ui_scroll_container = 5
};

struct rr_ui_labeled_button_metadata
{
    uint8_t *toggle;
    char *text;
};

struct rr_ui_text_metadata
{
    char const *text;
    float size;
};

struct rr_ui_dynamic_text_metadata
{
    char *text;
    float size;
    void (*get_text)(struct rr_ui_element *, struct rr_game *);
    void *data;
};

struct rr_ui_choose_element_metadata
{
    uint8_t (*choose)(struct rr_ui_element *, struct rr_game *);
    void *data;
    uint8_t previously_shown;
    uint8_t not_first_frame;
};

struct rr_ui_container_metadata
{
    uint8_t width; // for 2D containers
    uint8_t height;
    float outer_spacing;
    float inner_spacing;
    void *data;
};

struct rr_ui_element_vector
{
    struct rr_ui_element **start;
    uint16_t size;
    uint16_t capacity;
};

struct rr_ui_element
{
    struct rr_ui_element_vector elements;
    struct rr_ui_element *container;
    void *data;
    uint8_t (*should_show)(struct rr_ui_element *, struct rr_game *);
    void (*animate)(struct rr_ui_element *, struct rr_game *);
    void (*on_render)(struct rr_ui_element *, struct rr_game *);
    void (*on_hide)(struct rr_ui_element *, struct rr_game *);
    void (*on_event)(struct rr_ui_element *, struct rr_game *);
    void (*poll_events)(struct rr_ui_element *, struct rr_game *);
    float x;
    float y;
    float width;
    float abs_width;
    float height;
    float abs_height;
    float abs_x;
    float abs_y;
    float animation;
    uint32_t fill;
    uint32_t stroke;
    float stroke_width;
    int8_t h_justify;
    int8_t v_justify;
    uint8_t resizeable;
    uint8_t completely_hidden : 1;
    uint8_t first_frame : 1;
    uint8_t stop_event_propagation : 1;
    uint8_t prevent_on_event : 1;
    uint8_t allow_overlap : 1;
    uint8_t no_reposition : 1;
    uint8_t h_flex;
    uint8_t v_flex;
};

// render funcs
void rr_ui_render_element(struct rr_ui_element *, struct rr_game *);
void rr_ui_render_tooltip_above(struct rr_ui_element *, struct rr_ui_element *,
                                struct rr_game *);
void rr_ui_render_tooltip_below(struct rr_ui_element *, struct rr_ui_element *,
                                struct rr_game *);
void rr_ui_render_tooltip_right(struct rr_ui_element *, struct rr_ui_element *,
                                struct rr_game *);
uint8_t rr_ui_mouse_over(struct rr_ui_element *, struct rr_game *);
void rr_ui_element_check_if_focused(struct rr_ui_element *, struct rr_game *);
uint8_t rr_ui_always_show(struct rr_ui_element *, struct rr_game *);
uint8_t rr_ui_never_show(struct rr_ui_element *, struct rr_game *);
void rr_ui_no_focus(struct rr_ui_element *, struct rr_game *);
void rr_ui_default_animate(struct rr_ui_element *, struct rr_game *);
void rr_ui_scale_animate(struct rr_ui_element *, struct rr_game *);
void rr_ui_instant_hide_animate(struct rr_ui_element *, struct rr_game *);
struct rr_ui_element *rr_ui_link_toggle(struct rr_ui_element *,
                                        uint8_t (*)(struct rr_ui_element *,
                                                    struct rr_game *));
void rr_ui_container_poll_events(struct rr_ui_element *, struct rr_game *);

extern struct rr_ui_element *rr_ui_element_init();
extern struct rr_ui_element *rr_ui_static_space_init(float);

extern struct rr_ui_element *rr_ui_container_init();
extern struct rr_ui_element *rr_ui_popup_container_init();
extern struct rr_ui_element *rr_ui_flex_container_init(struct rr_ui_element *,
                                                       struct rr_ui_element *,
                                                       float);
extern struct rr_ui_element *rr_ui_2d_container_init(uint8_t, uint8_t, float,
                                                     float);
extern struct rr_ui_element *rr_ui_tooltip_container_init();
extern struct rr_ui_element *
rr_ui_container_add_element(struct rr_ui_element *, struct rr_ui_element *);

extern struct rr_ui_element *rr_ui_text_init(char const *, float, uint32_t);
extern struct rr_ui_element *
rr_ui_dynamic_text_init(float, uint32_t,
                        void (*)(struct rr_ui_element *, struct rr_game *));

extern struct rr_ui_element *rr_ui_labeled_button_init(char *, float,
                                                       uint8_t *);

extern struct rr_ui_element *rr_ui_choose_element_init(
    struct rr_ui_element *, struct rr_ui_element *,
    uint8_t (*)(struct rr_ui_element *, struct rr_game *));
extern struct rr_ui_element *rr_ui_multi_choose_element_init(
    uint8_t (*)(struct rr_ui_element *, struct rr_game *), ...);

extern struct rr_ui_element *rr_ui_toggle_box_init(uint8_t *);

extern struct rr_ui_element *rr_ui_h_slider_init(float, float, float *,
                                                 uint8_t);

extern struct rr_ui_element *
rr_ui_close_button_init(float,
                        void (*)(struct rr_ui_element *, struct rr_game *));

extern struct rr_ui_element *rr_ui_scroll_container_init(struct rr_ui_element *,
                                                         float);

extern struct rr_ui_element *rr_ui_text_input_init(float, float, char *,
                                                   uint32_t, char *);
// custom
extern struct rr_ui_element *rr_ui_squad_container_init(struct rr_game_squad *);
extern struct rr_ui_element *
rr_ui_squad_player_tooltip_init(struct rr_squad_member *);

extern struct rr_ui_element *rr_ui_inventory_container_init();

extern struct rr_ui_element *rr_ui_title_screen_loadout_button_init(uint8_t);
extern struct rr_ui_element *rr_ui_loadout_button_init(uint8_t);
extern struct rr_ui_element *rr_ui_secondary_loadout_button_init(uint8_t);

extern struct rr_ui_element *rr_ui_rivet_container_init(struct rr_game *);
extern struct rr_ui_element *rr_ui_account_container_init(struct rr_game *);

extern struct rr_ui_element *rr_ui_inventory_toggle_button_init();
extern struct rr_ui_element *rr_ui_settings_toggle_button_init();
extern struct rr_ui_element *rr_ui_account_toggle_button_init();

extern struct rr_ui_element *rr_ui_discord_toggle_button_init();

extern struct rr_ui_element *rr_ui_settings_container_init(struct rr_game *);
extern struct rr_ui_element *rr_ui_squad_button_init();
extern struct rr_ui_element *rr_ui_create_squad_button_init();
extern struct rr_ui_element *rr_ui_join_button_init();
extern struct rr_ui_element *rr_ui_copy_squad_code_button_init();
extern struct rr_ui_element *rr_ui_join_squad_code_button_init();
extern struct rr_ui_element *rr_ui_toggle_private_button_init(struct rr_game *);

extern struct rr_ui_element *rr_ui_petal_tooltip_init(uint8_t, uint8_t);
extern struct rr_ui_element *rr_ui_mob_tooltip_init(uint8_t, uint8_t);

extern struct rr_ui_element *rr_ui_mob_gallery_toggle_button_init();
extern struct rr_ui_element *rr_ui_mob_container_init();

extern struct rr_ui_element *rr_ui_crafting_container_init();
extern struct rr_ui_element *rr_ui_crafting_toggle_button_init();

extern struct rr_ui_element *rr_ui_finished_game_screen_init();

extern struct rr_ui_element *rr_ui_in_game_player_hud_init(uint8_t);

extern struct rr_ui_element *rr_ui_dev_panel_toggle_button_init();
extern struct rr_ui_element *rr_ui_dev_panel_container_init(struct rr_game *);

extern struct rr_ui_element *rr_ui_biome_button_init(char *, uint32_t, uint8_t);

extern struct rr_ui_element *rr_ui_level_bar_init(float);

extern struct rr_ui_element *rr_ui_loot_container_init();

extern struct rr_ui_element *rr_ui_minimap_init(struct rr_game *);

extern struct rr_ui_element *rr_ui_chat_bar_init(struct rr_game *);
extern struct rr_ui_element *rr_ui_message_box_init(struct rr_game *);

extern struct rr_ui_element *rr_ui_anti_afk_container_init();
