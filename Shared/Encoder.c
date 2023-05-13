#include <Shared/Encoder.h>

#include <string.h>

uint8_t rr_encoder_read_uint8(struct rr_encoder *self)
{
    return self->data[self->at++];
}

uint32_t rr_encoder_read_varuint(struct rr_encoder *self)
{
    uint32_t num = 0;
    uint32_t count = 0;
    uint8_t* ptr = self->data + self->at;
    
    do
    {
        num |= (*ptr & 127) << count;
        count += 7;
    } 
    while(*(ptr++) & 128);
    
    self->at += ptr - self->data;
    return num;
}

float rr_encoder_read_float(struct rr_encoder *self)
{
    float f;
    memcpy(&f, self->data, 4);
    self->at += 4;
    return f;
}


void rr_encoder_write_uint8(struct rr_encoder *self, uint8_t v)
{
    self->data[self->at++] = v;
}

void rr_encoder_write_varuint(struct rr_encoder *self, uint32_t v)
{
    uint8_t* ptr = self->data + self->at;
    while (v > 127)
    {
        *(ptr++) = (v & 127) | 128;
        v >>= 7;
    }
    *(ptr++) = v;
    self->at += ptr - self->data;
}

void rr_encoder_write_float(struct rr_encoder *self, float v)
{
    memcpy(self->data, &v, 4);
    self->at += 4;
}
