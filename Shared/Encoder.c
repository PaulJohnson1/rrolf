#include <Shared/Encoder.h>

#include <string.h>

void rr_encoder_init(struct rr_encoder *this, uint8_t *data)
{
    this->start = data;
    this->current = data;
}

uint8_t rr_encoder_read_uint8(struct rr_encoder *this)
{
    return *this->current++;
}

uint64_t rr_encoder_read_uint64(struct rr_encoder *this)
{
    uint64_t x;
    memcpy(&x, this->current, 8);
    this->current += 8;
    return x;
}

uint64_t rr_encoder_read_varuint(struct rr_encoder *this)
{
    uint8_t byte;
    uint64_t num = 0;
    uint64_t count = 0;

    do
    {
        byte = *(this->current++);
        num |= (byte & 127) << count;
        count += 7;
    } while (byte & 128);

    return num;
}

float rr_encoder_read_float(struct rr_encoder *this)
{
    float f;
    memcpy(&f, this->current, 4);
    this->current += 4;
    return f;
}

void rr_encoder_write_uint8(struct rr_encoder *this, uint8_t v)
{
    *this->current++ = v;
}

void rr_encoder_write_uint64(struct rr_encoder *this, uint64_t v)
{
    memcpy(this->current, &v, 8);
    this->current += 8;
}

void rr_encoder_write_varuint(struct rr_encoder *this, uint64_t v)
{
    while (v > 127)
    {
        *this->current++ = v | 128;
        v >>= 7;
    }
    *this->current++ = v;
}

void rr_encoder_write_float(struct rr_encoder *this, float v)
{
    memcpy(this->current, &v, 4);
    this->current += 4;
}
