#include <Shared/BinaryEncoder.h>


uint8_t rr_binary_encoder_read_uint8(struct rr_binary_encoder *c)
{
    return c->data[c->at++];
}

/*
Processor.prototype.readVU = function() {
  let number = 0;
  let count = 0;
  do {
    number |= (this.buffer[this.at] & 0x7f) << (7 * count++);
  } while((this.buffer[this.at++] >> 7) == 1);
  return number;
};
*/

uint32_t rr_binary_encoder_read_varuint(struct rr_binary_encoder *c)
{

}

float rr_binary_encoder_read_float(struct rr_binary_encoder *c)
{
    union
    {
        float _;
        uint8_t arr[4];
    } convert;

    convert.arr[0] = rr_binary_encoder_read_uint8(c);
    convert.arr[1] = rr_binary_encoder_read_uint8(c);
    convert.arr[2] = rr_binary_encoder_read_uint8(c);
    convert.arr[3] = rr_binary_encoder_read_uint8(c);

    return co
}


void rr_binary_encoder_write_uint8(struct rr_binary_encoder *c, uint8_t v)
{
    c->data[c->at++] = v;
}

void rr_binary_encoder_write_varuint(struct rr_binary_encoder *c, uint32_t v)
{
    uint8_t* ptr = c->data + c->at;
    while (v > 127)
    {
        *(ptr++) = (v & 127) | 128;
        v >>= 7;
    }
    *(ptr++) = v;
    c->at += ptr - c->data;
}

void rr_binary_encoder_write_float(struct rr_binary_encoder *c, float v)
{
    union
    {
        float _;
        uint8_t arr[4];
    } convert;

    convert._ = v;

    rr_binary_encoder_write_uint8(c, convert.arr[0]);
    rr_binary_encoder_write_uint8(c, convert.arr[1]);
    rr_binary_encoder_write_uint8(c, convert.arr[2]);
    rr_binary_encoder_write_uint8(c, convert.arr[3]);
}
