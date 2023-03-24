#include <Server/Component/Flower.hh>

#include <cstdint>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app::component
{
    Flower::Flower(Entity parent)
        : m_Parent(parent)
    {
    }

    void Flower::Reset()
    {
        m_State = 0;
    }

    void Flower::Write(bc::BinaryCoder &coder, Flower flower, bool isCreation)
    {
        uint32_t state = isCreation ? 0b11 : flower.m_State;
        coder.Write<bc::VarUint>(state);

        if (state & 1)
            coder.Write<bc::Uint8>(flower.m_FaceFlags);
        if (state & 2)
            coder.Write<bc::Float32>(flower.m_EyeAngle);
    }

    uint8_t Flower::FaceFlags() const
    {
        return m_FaceFlags;
    }

    float Flower::EyeAngle() const
    {
        return m_EyeAngle;
    }

    void Flower::FaceFlags(uint8_t v)
    {
        if (v == m_FaceFlags)
            return;
        m_FaceFlags = v;
        m_State |= 1 << 0;
    }

    void Flower::EyeAngle(float v)
    {
        if (v == m_EyeAngle)
            return;
        m_EyeAngle = v;
        m_State |= 1 << 1;
    }
}
