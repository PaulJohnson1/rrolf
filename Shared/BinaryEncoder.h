#pragma once

#include <stdint.h>

struct rr_binary_encoder // word binary is kinda excess here lool
{
    uint8_t *data;
    uint32_t at;
};

uint8_t rr_binary_encoder_read_uint8(struct rr_binary_encoder *);
uint32_t rr_binary_encoder_read_varuint(struct rr_binary_encoder *);
float rr_binary_encoder_read_float(struct rr_binary_encoder *);

void rr_binary_encoder_write_uint8(struct rr_binary_encoder *, uint8_t);
void rr_binary_encoder_write_varuint(struct rr_binary_encoder *, uint32_t);
void rr_binary_encoder_write_float(struct rr_binary_encoder *, float);
