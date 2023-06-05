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
    struct rr_ui_element *elements[10];//some max size
};

struct rr_ui_container_metadata
{
    uint8_t is_horizontal;
    float inner_spacing;
    float outer_spacing;
};

struct rr_ui_element
{
    //enum rr_ui_type type;
    uint8_t h_justify;
    uint8_t v_justify;
    uint8_t hidden;
    float x;
    float y;
    float width;
    float height;
    void (*on_render)(struct rr_ui_element *, void *);
    struct rr_ui_element *container;
    void *misc_data;
    struct rr_ui_element_vector elements;
};

void ui_translate(struct rr_ui_element *, struct rr_renderer *);

struct rr_ui_element *rr_ui_init_element();

struct rr_ui_element *rr_ui_init_button();
struct rr_ui_element *rr_ui_init_respawn_button();
uint8_t rr_button_is_touching_mouse(struct rr_ui_element *, struct rr_game *);

struct rr_ui_element *rr_ui_init_container();
void rr_ui_container_add_element(struct rr_ui_element *, struct rr_ui_element *);

struct rr_ui_element *rr_ui_init_text(char const *, float);