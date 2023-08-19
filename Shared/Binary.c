#include <Shared/Binary.h>

#include <stdio.h>
#include <string.h>

void rr_binary_encoder_init(struct rr_binary_encoder *this, uint8_t *ptr)
{
    this->at = this->start = ptr;
}

uint8_t rr_binary_encoder_read_uint8(struct rr_binary_encoder *this)
{
    return *this->at++;
}

uint64_t rr_binary_encoder_read_varuint(struct rr_binary_encoder *this)
{
    uint8_t byte;
    uint64_t data = 0ull;
    uint64_t shift = 0ull;

    do
    {
        byte = rr_binary_encoder_read_uint8(this);
        data |= ((byte & 254ull) << shift) >> 1;
        shift += 7ull;
    } while (byte & 1ull);

    return data;
}

float rr_binary_encoder_read_float32(struct rr_binary_encoder *this)
{
    float data;
    memcpy(&data, this->at, sizeof data);
    this->at += sizeof data;
    return data;
}

double rr_binary_encoder_read_float64(struct rr_binary_encoder *this)
{
    double data;
    memcpy(&data, this->at, sizeof data);
    this->at += sizeof data;
    return data;
}

void rr_binary_encoder_read_nt_string(struct rr_binary_encoder *this, char *buf)
{
    while(*this->at)
    {
        *buf++ = *this->at++;
    }
    *buf = 0;
    this->at++;
}