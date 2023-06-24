#pragma once

#include <Client/Ui/Element.h>
#include <stdarg.h>
#include <stdint.h>

struct rr_ui_element *rr_ui_h_container_init(struct rr_ui_element *, float, float, uint32_t, ...);
struct rr_ui_element *rr_ui_v_container_init(struct rr_ui_element *, float, float, uint32_t, ...);
struct rr_ui_element *rr_ui_grid_container_init(struct rr_ui_element *, uint8_t, uint8_t, float, float, struct rr_ui_element *(*)(uint8_t, uint8_t));
struct rr_ui_element *rr_ui_set_justify(struct rr_ui_element *, uint8_t, uint8_t);
struct rr_ui_element *rr_ui_pad(struct rr_ui_element *, float);
struct rr_ui_element *rr_ui_set_background(struct rr_ui_element *, uint32_t);

void rr_ui_container_refactor(struct rr_ui_element *);