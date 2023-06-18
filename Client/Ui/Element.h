#pragma once

#include <stdint.h>
#include <Client/Renderer/Renderer.h>

struct rr_game;

enum rr_ui_type
{
    rr_ui_default_element,
    rr_ui_button,
    rr_ui_container
};

struct rr_ui_element_vector
{
    uint32_t size;
    struct rr_ui_element *elements[128];//some max size
};

struct rr_ui_container_metadata
{
    uint8_t is_horizontal;
    uint32_t fill_color;
    float inner_spacing;
    float outer_spacing;
    struct rr_ui_element_vector elements;
};

struct rr_ui_choose_element_metadata
{
    struct rr_ui_element *a;
    struct rr_ui_element *b;
    uint8_t info;
};

struct rr_ui_element
{
    //enum rr_ui_type type;
    uint8_t h_justify;
    uint8_t v_justify;
    uint8_t hidden;
    uint8_t is_resizable_container;
    float x;
    float y;
    float lerp_x;
    float lerp_y;
    float width;
    float height;
    float animation_timer;
    void (*on_render)(struct rr_ui_element *, void *);
    struct rr_ui_element *container;
    void *misc_data;
};

/* "primitives" */
void ui_translate(struct rr_ui_element *, struct rr_renderer *);
uint8_t rr_button_is_touching_mouse(struct rr_ui_element *, struct rr_game *);
void rr_ui_choose_element_on_render(struct rr_ui_element *, void *);

/* inits */
struct rr_ui_element *rr_ui_element_init();
struct rr_ui_element *rr_ui_choose_element_init(struct rr_ui_element *, struct rr_ui_element *);

struct rr_ui_element *rr_ui_button_init();
struct rr_ui_element *rr_ui_find_server_button_init();
struct rr_ui_element *rr_ui_paired_button_init(struct rr_ui_element *);

struct rr_ui_element *rr_ui_container_init();
struct rr_ui_element *rr_ui_container_add_element(struct rr_ui_element *, struct rr_ui_element *);

struct rr_ui_element *rr_ui_text_init(char const *, float);

struct rr_ui_element *rr_ui_text_input_init(float, float, uint8_t);

struct rr_ui_element *rr_ui_inventory_container_init();
struct rr_ui_element *rr_ui_loadout_container_init();
struct rr_ui_element *rr_ui_title_screen_loadout_container_init();
struct rr_ui_element *rr_ui_squad_container_init();
struct rr_ui_element *rr_ui_wave_container_init();

struct rr_ui_element *rr_ui_abandon_game_button_init();