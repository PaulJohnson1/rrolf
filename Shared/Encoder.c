#include <Shared/Encoder.h>

#include <stdio.h>
#include <string.h>

void rr_encoder_init(struct rr_encoder *self, uint8_t *data)
{
    self->start = data;
    self->current = data;
}

uint8_t rr_encoder_read_uint8(struct rr_encoder *self)
{
    return *self->current++;
}

uint32_t rr_encoder_read_varuint(struct rr_encoder *self)
{
    uint8_t byte;
    uint32_t num = 0;
    uint32_t count = 0;

    do
    {
        byte = *(self->current++);
        num |= (byte & 127) << count;
        count += 7;
    } while (byte & 128);

    return num;
}

float rr_encoder_read_float(struct rr_encoder *self)
{
    float f;
    memcpy(&f, self->current, 4);
    self->current += 4;
    return f;
}

void rr_encoder_write_uint8(struct rr_encoder *self, uint8_t v)
{
    *self->current++ = v;
}

void rr_encoder_write_varuint(struct rr_encoder *self, uint32_t v)
{
    while (v > 127)
    {
        *self->current++ = v | 128;
        v >>= 7;
    }
    *self->current++ = v;
}

void rr_encoder_write_float(struct rr_encoder *self, float v)
{
    memcpy(self->current, &v, 4);
    self->current += 4;
}
