#pragma once

#include <stdint.h>
// a normal binary encoder

#define RR_API_SUCCESS 45

struct rr_binary_encoder
{
    uint8_t *at;
    uint8_t *start;
};

void rr_binary_encoder_init(struct rr_binary_encoder *, uint8_t *);
uint8_t rr_binary_encoder_read_uint8(struct rr_binary_encoder *);
uint64_t rr_binary_encoder_read_varuint(struct rr_binary_encoder *);
uint32_t rr_binary_encoder_read_utf8(struct rr_binary_encoder *);
float rr_binary_encoder_read_float32(struct rr_binary_encoder *);
double rr_binary_encoder_read_float64(struct rr_binary_encoder *);
void rr_binary_encoder_read_nt_string(struct rr_binary_encoder *, char *);

void rr_binary_encoder_write_uint8(struct rr_binary_encoder *, uint8_t);
void rr_binary_encoder_write_varuint(struct rr_binary_encoder *, uint64_t);
void rr_binary_encoder_write_float32(struct rr_binary_encoder *, float);
void rr_binary_encoder_write_float64(struct rr_binary_encoder *, double);
void rr_binary_encoder_write_utf8(struct rr_binary_encoder *, uint32_t);
void rr_binary_encoder_write_nt_string(struct rr_binary_encoder *, char *);