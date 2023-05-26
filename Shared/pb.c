#include "pb.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <malloc.h>
#else
#include <alloca.h>
#endif

#define ENCODING_TYPES \
    XX(uint8)          \
    XX(uint16)         \
    XX(uint32)         \
    XX(uint64)         \
    XX(varuint)        \
    XX(float32)        \
    XX(float64)        \
    XX(string)

    enum encoding_type
    {
#define XX(n) n,
        ENCODING_TYPES
#undef XX
    };

    char const *get_encoding_type_string(enum encoding_type encoding_type)
    {
        switch (encoding_type)
        {
#define XX(n) \
    case n:   \
        return #n;
            ENCODING_TYPES
#undef XX
        default:
            assert(0);
            __builtin_unreachable();
        }
    }

void proto_bug_init(struct proto_bug *self, uint8_t *data)
{
    self->start = data;
    self->current = data;
}

void proto_bug_reset(struct proto_bug *self)
{
    self->current = self->start;
}

uint64_t proto_bug_get_size(struct proto_bug *self)
{
    return self->current - self->start;
}

void proto_bug_write_uint8_internal(struct proto_bug *self, uint8_t data)
{
    *self->current++ = data;
}
void proto_bug_write_uint16_internal(struct proto_bug *self, uint16_t data)
{
    proto_bug_write_uint8_internal(self, (data & 0xff00) >> 8);
    proto_bug_write_uint8_internal(self, data & 0xff);
}
void proto_bug_write_uint32_internal(struct proto_bug *self, uint32_t data)
{
    proto_bug_write_uint8_internal(self, (data & 0xff000000) >> 24);
    proto_bug_write_uint8_internal(self, (data & 0x00ff0000) >> 16);
    proto_bug_write_uint8_internal(self, (data & 0x0000ff00) >> 8);
    proto_bug_write_uint8_internal(self, data & 0xff);
}
void proto_bug_write_uint64_internal(struct proto_bug *self, uint64_t data)
{
    proto_bug_write_uint8_internal(self, (data & 0xff00000000000000ull) >> 56ull);
    proto_bug_write_uint8_internal(self, (data & 0xff000000000000ull) >> 48ull);
    proto_bug_write_uint8_internal(self, (data & 0xff0000000000ull) >> 40ull);
    proto_bug_write_uint8_internal(self, (data & 0xff00000000ull) >> 32ull);
    proto_bug_write_uint8_internal(self, (data & 0xff000000ull) >> 24ull);
    proto_bug_write_uint8_internal(self, (data & 0xff0000ull) >> 16ull);
    proto_bug_write_uint8_internal(self, (data & 0xff00ull) >> 8ull);
    proto_bug_write_uint8_internal(self, data & 0xffull);
}
void proto_bug_write_float32_internal(struct proto_bug *self, float data)
{
    memcpy(self->current, &data, sizeof data); // the compiler is a genius and optimizes self
    self->current += sizeof data;
}
void proto_bug_write_float64_internal(struct proto_bug *self, double data)
{
    memcpy(self->current, &data, sizeof data);
    self->current += sizeof data;
}
void proto_bug_write_varuint_internal(struct proto_bug *self, uint64_t data)
{
    while (data > 127ull)
    {
        proto_bug_write_uint8_internal(self, data | 128ull);
        data >>= 7ull;
    }
    proto_bug_write_uint8_internal(self, data);
}
void proto_bug_write_string_internal(struct proto_bug *self, char const *string, uint64_t size)
{
    for (uint64_t i = 0; i < size; i++)
        proto_bug_write_uint8_internal(self, string[i]);
}

uint8_t proto_bug_read_uint8_internal(struct proto_bug *self)
{
    return *self->current++;
}
uint16_t proto_bug_read_uint16_internal(struct proto_bug *self)
{
    uint16_t data = 0;
    data |= (uint16_t)proto_bug_read_uint8_internal(self) << 8;
    data |= (uint16_t)proto_bug_read_uint8_internal(self);

    return data;
}
uint32_t proto_bug_read_uint32_internal(struct proto_bug *self)
{
    uint32_t data = 0;
    data |= (uint32_t)proto_bug_read_uint8_internal(self) << 24;
    data |= (uint32_t)proto_bug_read_uint8_internal(self) << 16;
    data |= (uint32_t)proto_bug_read_uint8_internal(self) << 8;
    data |= (uint32_t)proto_bug_read_uint8_internal(self);

    return data;
}
uint64_t proto_bug_read_uint64_internal(struct proto_bug *self)
{
    uint64_t data = 0;
    data |= (uint64_t)proto_bug_read_uint8_internal(self) << 56ull;
    data |= (uint64_t)proto_bug_read_uint8_internal(self) << 48ull;
    data |= (uint64_t)proto_bug_read_uint8_internal(self) << 40ull;
    data |= (uint64_t)proto_bug_read_uint8_internal(self) << 32ull;
    data |= (uint64_t)proto_bug_read_uint8_internal(self) << 24ull;
    data |= (uint64_t)proto_bug_read_uint8_internal(self) << 16ull;
    data |= (uint64_t)proto_bug_read_uint8_internal(self) << 8ull;
    data |= (uint64_t)proto_bug_read_uint8_internal(self);

    return data;
}
float proto_bug_read_float32_internal(struct proto_bug *self)
{
    float data;
    memcpy(&data, self->current, sizeof data);
    self->current += sizeof data;
    return data;
}
double proto_bug_read_float64_internal(struct proto_bug *self)
{
    double data;
    memcpy(&data, self->current, sizeof data);
    self->current += sizeof data;
    return data;
}
uint64_t proto_bug_read_varuint_internal(struct proto_bug *self)
{
    uint8_t byte;
    uint64_t data = 0ull;
    uint64_t shift = 0ull;

    do
    {
        byte = proto_bug_read_uint8_internal(self);
        data |= (byte & 127ull) << shift;
        shift += 7ull;
    } while (byte & 128ull);

    return data;
}
void proto_bug_read_string_internal(struct proto_bug *self, char *string, uint64_t size)
{
    for (uint64_t i = 0; i < size; i++)
        string[i] = proto_bug_read_uint8_internal(self);
}

#ifndef PROTO_BUG_NDEBUG
    static char assertion_fail_message[1024];

void proto_bug_assert_valid_debug_header(struct proto_bug *self, enum encoding_type expected_encoding_type, char const *name, char const *file, uint32_t line)
{
    enum encoding_type received_encoding_type = (enum encoding_type)proto_bug_read_uint8_internal(self);
    uint64_t name_size = proto_bug_read_varuint_internal(self);
    uint64_t file_size = proto_bug_read_varuint_internal(self);
    // uint64_t _size = proto_bug_read_varuint_internal(self);
    char *received_name = (char *)PROTO_BUG_ALLOCA(name_size + 1);
    char *received_file = (char *)PROTO_BUG_ALLOCA(file_size + 1);
    memset(received_name, 0, name_size + 1);
    memset(received_file, 0, file_size + 1);
    proto_bug_read_string_internal(self, received_name, name_size);
    proto_bug_read_string_internal(self, received_file, file_size);
    uint32_t received_line = proto_bug_read_varuint_internal(self);
    if ((received_encoding_type != expected_encoding_type) || ((name_size != strlen(name) || (strcmp(received_name, name)))))
    {
        assertion_fail_message[sprintf(assertion_fail_message, "tried to read {encoding_type:%s name:%s written_at: %s:%u} as {encoding_type:%s name:%s read_at: %s:%u}\n",
                                       get_encoding_type_string(received_encoding_type), received_name, received_file, received_line,
                                       get_encoding_type_string(expected_encoding_type), name, file, line)] = 0;

            fputs(assertion_fail_message, stderr);
            abort();
        }
    }

void proto_bug_write_debug_header(struct proto_bug *self, enum encoding_type encoding_type, char const *name, char const *file, uint32_t line)
{
    proto_bug_write_uint8_internal(self, encoding_type);
    uint64_t name_size = strlen(name);
    uint64_t file_size = strlen(file);
    proto_bug_write_varuint_internal(self, name_size);
    proto_bug_write_varuint_internal(self, file_size);
    proto_bug_write_string_internal(self, name, name_size);
    proto_bug_write_string_internal(self, file, file_size);
    proto_bug_write_varuint_internal(self, line);
}

void proto_bug_write_uint8_debug(struct proto_bug *self, uint8_t data, char const *name, char const *file, uint32_t line)
{
    proto_bug_write_debug_header(self, uint8, name, file, line);
    proto_bug_write_uint8_internal(self, data);
}
void proto_bug_write_uint16_debug(struct proto_bug *self, uint16_t data, char const *name, char const *file, uint32_t line)
{
    proto_bug_write_debug_header(self, uint16, name, file, line);
    proto_bug_write_uint16_internal(self, data);
}
void proto_bug_write_uint32_debug(struct proto_bug *self, uint32_t data, char const *name, char const *file, uint32_t line)
{
    proto_bug_write_debug_header(self, uint32, name, file, line);
    proto_bug_write_uint32_internal(self, data);
}
void proto_bug_write_uint64_debug(struct proto_bug *self, uint64_t data, char const *name, char const *file, uint32_t line)
{
    proto_bug_write_debug_header(self, uint64, name, file, line);
    proto_bug_write_uint64_internal(self, data);
}
void proto_bug_write_float32_debug(struct proto_bug *self, float data, char const *name, char const *file, uint32_t line)
{
    proto_bug_write_debug_header(self, float32, name, file, line);
    proto_bug_write_float32_internal(self, data);
}
void proto_bug_write_float64_debug(struct proto_bug *self, double data, char const *name, char const *file, uint32_t line)
{
    proto_bug_write_debug_header(self, float64, name, file, line);
    proto_bug_write_float64_internal(self, data);
}
void proto_bug_write_varuint_debug(struct proto_bug *self, uint64_t data, char const *name, char const *file, uint32_t line)
{
    proto_bug_write_debug_header(self, varuint, name, file, line);
    proto_bug_write_varuint_internal(self, data);
}
void proto_bug_write_string_debug(struct proto_bug *self, char const *string_pointer, uint64_t size, char const *name, char const *file, uint32_t line)
{
    proto_bug_write_debug_header(self, string, name, file, line);
    proto_bug_write_string_internal(self, string_pointer, size);
}

uint8_t proto_bug_read_uint8_debug(struct proto_bug *self, char const *name, char const *file, uint32_t line)
{
    proto_bug_assert_valid_debug_header(self, uint8, name, file, line);
    return proto_bug_read_uint8_internal(self);
}
uint16_t proto_bug_read_uint16_debug(struct proto_bug *self, char const *name, char const *file, uint32_t line)
{
    proto_bug_assert_valid_debug_header(self, uint16, name, file, line);
    return proto_bug_read_uint16_internal(self);
}
uint32_t proto_bug_read_uint32_debug(struct proto_bug *self, char const *name, char const *file, uint32_t line)
{
    proto_bug_assert_valid_debug_header(self, uint32, name, file, line);
    return proto_bug_read_uint32_internal(self);
}
uint64_t proto_bug_read_uint64_debug(struct proto_bug *self, char const *name, char const *file, uint32_t line)
{
    proto_bug_assert_valid_debug_header(self, uint64, name, file, line);
    return proto_bug_read_uint64_internal(self);
}
float proto_bug_read_float32_debug(struct proto_bug *self, char const *name, char const *file, uint32_t line)
{
    proto_bug_assert_valid_debug_header(self, float32, name, file, line);
    return proto_bug_read_float32_internal(self);
}
double proto_bug_read_float64_debug(struct proto_bug *self, char const *name, char const *file, uint32_t line)
{
    proto_bug_assert_valid_debug_header(self, float64, name, file, line);
    return proto_bug_read_float64_internal(self);
}
uint64_t proto_bug_read_varuint_debug(struct proto_bug *self, char const *name, char const *file, uint32_t line)
{
    proto_bug_assert_valid_debug_header(self, varuint, name, file, line);
    return proto_bug_read_varuint_internal(self);
}
void proto_bug_read_string_debug(struct proto_bug *self, char *string_pointer, uint64_t size, char const *name, char const *file, uint32_t line)
{
    proto_bug_assert_valid_debug_header(self, string, name, file, line);
    proto_bug_read_string_internal(self, string_pointer, size);
}
#endif


#ifdef __cplusplus
}
#endif