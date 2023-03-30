#pragma once

#include <type_traits>

namespace app
{
    template <typename T, bool AngleWrapAround = false>
    class Lerp
    {
        T m_Interpolated;
        T m_Destination;

    public:
        Lerp(T val)
        {
            m_Interpolated = m_Destination = val;
        }
        void operator=(T val) { m_Destination = val; }
        void Tick(float pct)
        {
            if (m_Interpolated == 0)
                m_Interpolated = m_Destination;
            m_Interpolated = (m_Destination - m_Interpolated) * pct + m_Interpolated;
        }
        operator T() const { return m_Interpolated; }
    };
}
