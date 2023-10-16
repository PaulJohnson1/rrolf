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