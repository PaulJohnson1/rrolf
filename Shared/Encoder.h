#pragma once

#include <stdint.h>

struct rr_encoder
{
    uint8_t *data;
    uint32_t at;
};

uint8_t rr_encoder_read_uint8(struct rr_encoder *);
uint32_t rr_encoder_read_varuint(struct rr_encoder *);
float rr_encoder_read_float(struct rr_encoder *);

void rr_encoder_write_uint8(struct rr_encoder *, uint8_t);
void rr_encoder_write_varuint(struct rr_encoder *, uint32_t);
void rr_encoder_write_float(struct rr_encoder *, float);
