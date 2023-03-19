#pragma once

#include <cstddef>
#include <cstdint>

namespace bc
{
    class BinaryCoder
    {
        uint8_t *m_Data;
        size_t m_At;

    public:
        BinaryCoder(uint8_t *);

        uint8_t *Data();
        uint8_t const *Data() const;
        size_t At() const;
        void At(size_t);

        template <typename T>
        typename T::Type Read()
        {
            return T::Read(*this);
        }
        template <typename T, typename... Arguments>
        void Write(typename T::Type const &x, Arguments const &... args)
        {
            T::Write(*this, x, args...);
        }
    };
}