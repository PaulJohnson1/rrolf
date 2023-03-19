#include <BinaryCoder/NativeTypes.hh>

namespace bc
{
    VarUint::Type VarUint::Read(BinaryCoder &coder)
    {
        Type x = 0;
        Type shift = 0;
        while (coder.Data()[coder.At()] & 0x80)
        {
            Type byte = coder.Read<Uint8>();
            x |= (byte & 127) << shift;
            shift += 7;
        }

        x |= (Type)(coder.Read<Uint8>() & 127) << shift;

        return x;
    }
    void VarUint::Write(BinaryCoder &coder, Type x)
    {
        do
        {
            uint8_t byte = x & 127;
            x >>= 7;
            if (x != 0)
                byte |= 128;
            coder.Write<Uint8>(byte);
        } while (x != 0);
    }
    VarInt::Type VarInt::Read(BinaryCoder &coder)
    {
        VarUint::Type unsignedValue = coder.Read<VarUint>();
        return int32_t(unsignedValue >> 1) ^ (0 - int32_t(unsignedValue & 1));
    }
    void VarInt::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<VarUint>((VarUint::Type(x) << 1) ^ (x >> 31));
    }
    Uint8::Type Uint8::Read(BinaryCoder &coder)
    {
        Type x = coder.Data()[coder.At()];
        coder.At(coder.At() + 1);
        return x;
    }
    void Uint8::Write(BinaryCoder &coder, Type x)
    {
        coder.Data()[coder.At()] = x;
        coder.At(coder.At() + 1);
    }
    Uint16::Type Uint16::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Uint8>() | ((Type)coder.Read<Uint8>() << 8);
        return x;
    }
    void Uint16::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Uint8>(x & 255);
        coder.Write<Uint8>(x >> 8);
    }
    Uint32::Type Uint32::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Uint16>() | ((Type)coder.Read<Uint16>() << 16);
        return x;
    }
    void Uint32::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Uint16>(x & 65535);
        coder.Write<Uint16>(x >> 16);
    }
    Uint64::Type Uint64::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Uint32>() | ((Type)coder.Read<Uint32>() << 32);
        return x;
    }
    void Uint64::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Uint32>(x & 4294967295);
        coder.Write<Uint32>(x >> 32);
    }
    Int8::Type Int8::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Data()[coder.At()];
        coder.At(coder.At() + 1);
        return x;
    }
    void Int8::Write(BinaryCoder &coder, Type x)
    {
        coder.Data()[coder.At()] = x;
    }
    Int16::Type Int16::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Int8>() | ((Type)coder.Read<Int8>() << 8);
        return x;
    }
    void Int16::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Int8>(x & 255);
        coder.Write<Int8>(x >> 8);
    }
    Int32::Type Int32::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Int16>() | ((Type)coder.Read<Int16>() << 16);
        return x;
    }
    void Int32::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Int16>(x & 65535);
        coder.Write<Int16>(x >> 16);
    }
    Int64::Type Int64::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Int32>() | ((Type)coder.Read<Int32>() << 32);
        return x;
    }
    void Int64::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Int32>(x & 4294967295);
        coder.Write<Int32>(x >> 32);
    }
    Float32::Type Float32::Read(BinaryCoder &coder)
    {
        union
        {
            float floatValue;
            uint32_t uint32Value;
        } conversion;

        conversion.uint32Value = coder.Read<Uint32>();
        return conversion.floatValue;
    }
    void Float32::Write(BinaryCoder &coder, Type x)
    {
        union
        {
            float floatValue;
            uint32_t uint32Value;
        } conversion;

        conversion.floatValue = x;
        coder.Write<Uint32>(conversion.uint32Value);
    }
    Float64::Type Float64::Read(BinaryCoder &coder)
    {
        union
        {
            double doubleValue;
            uint64_t uint64Value;
        } conversion;

        conversion.uint64Value = coder.Read<Uint64>();
        return conversion.doubleValue;
    }
    void Float64::Write(BinaryCoder &coder, Type x)
    {
        union
        {
            double doubleValue;
            uint64_t uint64Value;
        } conversion;

        conversion.doubleValue = x;
        coder.Write<Uint64>(conversion.uint64Value);
    }
    String::Type String::Read(BinaryCoder &coder)
    {
        std::string output;
        char byte;
        while ((byte = coder.Read<Int8>()))
            output += byte;
        return output;
    }
    void String::Write(BinaryCoder &coder, Type const &x)
    {
        for (size_t i = 0; i < x.size(); i++)
            coder.Write<Int8>(x[i]);
        coder.Write<Int8>(0);
    }
}