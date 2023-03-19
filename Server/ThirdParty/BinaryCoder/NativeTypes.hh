#pragma once

#include <string>

#include <BinaryCoder/BinaryCoder.hh>

namespace bc
{
#define BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(PUBLIC_NAME, RETURN_TYPE) \
    struct PUBLIC_NAME                                                     \
    {                                                                      \
        using Type = RETURN_TYPE;                                          \
        static Type Read(BinaryCoder &);                                   \
        static void Write(BinaryCoder &, Type x);                          \
    };

    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(VarUint, uint64_t);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(VarInt, int64_t);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(Uint8, uint8_t);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(Uint16, uint16_t);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(Uint32, uint32_t);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(Uint64, uint64_t);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(Int8, int8_t);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(Int16, int16_t);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(Int32, int32_t);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(Int64, int64_t);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(Float32, float);
    BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE(Float64, double);
#undef BINARY_CODER_DECLARE_NATIVE_LIBRARY_TYPE
    struct String
    {
        using Type = std::string;
        static Type Read(BinaryCoder &);
        static void Write(BinaryCoder &, Type const &x);
    };

}