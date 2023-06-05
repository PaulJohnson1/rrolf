#pragma once

#include <Client/Ui/Element.h>
#include <stdarg.h>
#include <stdint.h>

struct rr_ui_element *rr_ui_make_v_container(uint8_t, float, float, uint32_t, ...);
struct rr_ui_element *rr_ui_make_h_container(uint8_t, float, float, uint32_t, ...);
struct rr_ui_element *rr_ui_set_justify(struct rr_ui_element *, uint8_t, uint8_t);