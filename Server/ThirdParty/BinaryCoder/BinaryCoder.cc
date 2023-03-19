#include <BinaryCoder/BinaryCoder.hh>

namespace bc
{
    BinaryCoder::BinaryCoder(uint8_t *buffer)
        : m_Data(buffer),
          m_At(0)
    {
    }

    size_t BinaryCoder::At() const
    {
        return m_At;
    }
    void BinaryCoder::At(size_t x)
    {
        m_At = x;
    }

    uint8_t *BinaryCoder::Data()
    {
        return m_Data;
    }

    uint8_t const *BinaryCoder::Data() const
    {
        return m_Data;
    }
}