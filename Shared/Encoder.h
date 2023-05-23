#pragma once

#include <stdint.h>

struct rr_encoder
{
    uint8_t *start;
    uint8_t *current;
};

void rr_encoder_init(struct rr_encoder *, uint8_t *);

uint8_t rr_encoder_read_uint8(struct rr_encoder *);
uint64_t rr_encoder_read_uint64(struct rr_encoder *);
uint64_t rr_encoder_read_varuint(struct rr_encoder *);
float rr_encoder_read_float(struct rr_encoder *);

void rr_encoder_write_uint8(struct rr_encoder *, uint8_t);
void rr_encoder_write_uint64(struct rr_encoder *, uint64_t);
void rr_encoder_write_varuint(struct rr_encoder *, uint64_t);
void rr_encoder_write_float(struct rr_encoder *, float);

