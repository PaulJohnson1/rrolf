#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define PROTO_BUG_WINDOWS
#endif
#if defined(NDEBUG) && !defined(PROTO_BUG_NDEBUG)
#define PROTO_BUG_NDEBUG
#endif

#if defined(PROTO_BUG_FORCE_DEBUG) && defined(PROTO_BUG_NDEBUG)
#undef PROTO_BUG_NDEBUG
#endif

    struct proto_bug
    {
        uint8_t *start;
        uint8_t *current;
        uint8_t *end;
    };

    void proto_bug_init(struct proto_bug *, uint8_t *);
    void proto_bug_set_bound(struct proto_bug *, uint8_t *);
    void proto_bug_reset(struct proto_bug *); // go back to the beginning
    uint64_t proto_bug_get_size(struct proto_bug *);

    void proto_bug_write_uint8_internal(struct proto_bug *, uint8_t);
    void proto_bug_write_uint16_internal(struct proto_bug *, uint16_t);
    void proto_bug_write_uint32_internal(struct proto_bug *, uint32_t);
    void proto_bug_write_uint64_internal(struct proto_bug *, uint64_t);
    void proto_bug_write_varuint_internal(struct proto_bug *, uint64_t);
    void proto_bug_write_float32_internal(struct proto_bug *, float);
    void proto_bug_write_float64_internal(struct proto_bug *, double);
    void proto_bug_write_string_internal(struct proto_bug *, char const *,
                                         uint64_t);

    uint8_t proto_bug_read_uint8_internal(struct proto_bug *);
    uint16_t proto_bug_read_uint16_internal(struct proto_bug *);
    uint32_t proto_bug_read_uint32_internal(struct proto_bug *);
    uint64_t proto_bug_read_uint64_internal(struct proto_bug *);
    uint64_t proto_bug_read_varuint_internal(struct proto_bug *);
    float proto_bug_read_float32_internal(struct proto_bug *);
    double proto_bug_read_float64_internal(struct proto_bug *);
    void proto_bug_read_string_internal(struct proto_bug *, char *,
                                        uint64_t);

#ifndef PROTO_BUG_NDEBUG
    void proto_bug_write_uint8_debug(struct proto_bug *, uint8_t,
                                     char const *name, char const *file,
                                     uint32_t line);
    void proto_bug_write_uint16_debug(struct proto_bug *, uint16_t,
                                      char const *name, char const *file,
                                      uint32_t line);
    void proto_bug_write_uint32_debug(struct proto_bug *, uint32_t,
                                      char const *name, char const *file,
                                      uint32_t line);
    void proto_bug_write_uint64_debug(struct proto_bug *, uint64_t,
                                      char const *name, char const *file,
                                      uint32_t line);
    void proto_bug_write_varuint_debug(struct proto_bug *, uint64_t,
                                       char const *name, char const *file,
                                       uint32_t line);
    void proto_bug_write_float32_debug(struct proto_bug *, float,
                                       char const *name, char const *file,
                                       uint32_t line);
    void proto_bug_write_float64_debug(struct proto_bug *, double,
                                       char const *name, char const *file,
                                       uint32_t line);
    void proto_bug_write_string_debug(struct proto_bug *, char const *,
                                      uint64_t, char const *name,
                                      char const *file, uint32_t line);

    uint8_t proto_bug_read_uint8_debug(struct proto_bug *, char const *name,
                                       char const *file, uint32_t line);
    uint16_t proto_bug_read_uint16_debug(struct proto_bug *, char const *name,
                                         char const *file, uint32_t line);
    uint32_t proto_bug_read_uint32_debug(struct proto_bug *, char const *name,
                                         char const *file, uint32_t line);
    uint64_t proto_bug_read_uint64_debug(struct proto_bug *, char const *name,
                                         char const *file, uint32_t line);
    uint64_t proto_bug_read_varuint_debug(struct proto_bug *, char const *name,
                                          char const *file, uint32_t line);
    float proto_bug_read_float32_debug(struct proto_bug *, char const *name,
                                       char const *file, uint32_t line);
    double proto_bug_read_float64_debug(struct proto_bug *, char const *name,
                                        char const *file, uint32_t line);
    void proto_bug_read_string_debug(struct proto_bug *, char *, uint64_t size,
                                     char const *name, char const *file,
                                     uint32_t line);

#define proto_bug_write_uint8(this_pointer, value, name)                       \
    proto_bug_write_uint8_debug(this_pointer, value, name, __FILE__, __LINE__)
#define proto_bug_write_uint16(this_pointer, value, name)                      \
    proto_bug_write_uint16_debug(this_pointer, value, name, __FILE__, __LINE__)
#define proto_bug_write_uint32(this_pointer, value, name)                      \
    proto_bug_write_uint32_debug(this_pointer, value, name, __FILE__, __LINE__)
#define proto_bug_write_uint64(this_pointer, value, name)                      \
    proto_bug_write_uint64_debug(this_pointer, value, name, __FILE__, __LINE__)
#define proto_bug_write_varuint(this_pointer, value, name)                     \
    proto_bug_write_varuint_debug(this_pointer, value, name, __FILE__, __LINE__)
#define proto_bug_write_float32(this_pointer, value, name)                     \
    proto_bug_write_float32_debug(this_pointer, value, name, __FILE__, __LINE__)
#define proto_bug_write_float64(this_pointer, value, name)                     \
    proto_bug_write_float64_debug(this_pointer, value, name, __FILE__, __LINE__)
#define proto_bug_write_string(this_pointer, string_pointer, size, name)       \
    proto_bug_write_string_debug(this_pointer, string_pointer, size, name,     \
                                 __FILE__, __LINE__)

#define proto_bug_read_uint8(this_pointer, name)                               \
    proto_bug_read_uint8_debug(this_pointer, name, __FILE__, __LINE__)
#define proto_bug_read_uint16(this_pointer, name)                              \
    proto_bug_read_uint16_debug(this_pointer, name, __FILE__, __LINE__)
#define proto_bug_read_uint32(this_pointer, name)                              \
    proto_bug_read_uint32_debug(this_pointer, name, __FILE__, __LINE__)
#define proto_bug_read_uint64(this_pointer, name)                              \
    proto_bug_read_uint64_debug(this_pointer, name, __FILE__, __LINE__)
#define proto_bug_read_varuint(this_pointer, name)                             \
    proto_bug_read_varuint_debug(this_pointer, name, __FILE__, __LINE__)
#define proto_bug_read_float32(this_pointer, name)                             \
    proto_bug_read_float32_debug(this_pointer, name, __FILE__, __LINE__)
#define proto_bug_read_float64(this_pointer, name)                             \
    proto_bug_read_float64_debug(this_pointer, name, __FILE__, __LINE__)
#define proto_bug_read_string(this_pointer, string_pointer, size, name)        \
    proto_bug_read_string_debug(this_pointer, string_pointer, size, name,      \
                                __FILE__, __LINE__)
#else
#define proto_bug_write_uint8(this_pointer, value, name)                       \
    proto_bug_write_uint8_internal(this_pointer, value)
#define proto_bug_write_uint16(this_pointer, value, name)                      \
    proto_bug_write_uint16_internal(this_pointer, value)
#define proto_bug_write_uint32(this_pointer, value, name)                      \
    proto_bug_write_uint32_internal(this_pointer, value)
#define proto_bug_write_uint64(this_pointer, value, name)                      \
    proto_bug_write_uint64_internal(this_pointer, value)
#define proto_bug_write_varuint(this_pointer, value, name)                     \
    proto_bug_write_varuint_internal(this_pointer, value)
#define proto_bug_write_float32(this_pointer, value, name)                     \
    proto_bug_write_float32_internal(this_pointer, value)
#define proto_bug_write_float64(this_pointer, value, name)                     \
    proto_bug_write_float64_internal(this_pointer, value)
#define proto_bug_write_string(this_pointer, string_pointer, size, name)       \
    proto_bug_write_string_internal(this_pointer, string_pointer, size)

#define proto_bug_read_uint8(this_pointer, name)                               \
    proto_bug_read_uint8_internal(this_pointer)
#define proto_bug_read_uint16(this_pointer, name)                              \
    proto_bug_read_uint16_internal(this_pointer)
#define proto_bug_read_uint32(this_pointer, name)                              \
    proto_bug_read_uint32_internal(this_pointer)
#define proto_bug_read_uint64(this_pointer, name)                              \
    proto_bug_read_uint64_internal(this_pointer)
#define proto_bug_read_varuint(this_pointer, name)                             \
    proto_bug_read_varuint_internal(this_pointer)
#define proto_bug_read_float32(this_pointer, name)                             \
    proto_bug_read_float32_internal(this_pointer)
#define proto_bug_read_float64(this_pointer, name)                             \
    proto_bug_read_float64_internal(this_pointer)
#define proto_bug_read_string(this_pointer, string_pointer, size, name)        \
    proto_bug_read_string_internal(this_pointer, string_pointer, size)
#endif

#ifdef __cplusplus
}
#endif
