#pragma once

#include <type_traits>
#include <cmath>

namespace app
{
    template <typename T, bool AngleWrapAround = false>
    class Lerp
    {
        T m_Interpolated;
        T m_Destination;
        bool m_First = true;

    public:
        Lerp(T val)
        {
            if constexpr (AngleWrapAround)
                val = std::fmod(val, M_PI * 2);
            m_Interpolated = m_Destination = val;
        }
        void operator=(T val) 
        { 
            if constexpr (AngleWrapAround)
                val = std::fmod(val, M_PI * 2);
            m_Destination = val; 
            if (m_First)
                m_Interpolated = val;
            m_First = false;
        }
        void Tick(float pct)
        {

            if constexpr (AngleWrapAround)
            {
                if (std::abs(m_Destination - m_Interpolated) < M_PI)
                    m_Interpolated = (m_Destination - m_Interpolated) * pct + m_Interpolated;
                else
                {
                    if (m_Destination > m_Interpolated)
                        m_Interpolated += M_PI * 2;
                    else 
                        m_Destination += M_PI * 2;
                    m_Interpolated = std::fmod((m_Destination - m_Interpolated) * pct + m_Interpolated + M_PI * 2, M_PI * 2);
                }
            }
            else 
                m_Interpolated = (m_Destination - m_Interpolated) * pct + m_Interpolated;
        }

        T Destination() const { return m_Destination; }
        void SetInterpolated(T val) { m_Interpolated = val; }
        operator T() const { return m_Interpolated; }

        void operator+=(T v)
        {
            m_Destination += v;
        }
        
        void operator-=(T v)
        {
            m_Destination -= v;
        }
    };
}
