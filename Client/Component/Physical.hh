#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Physical
    {
    public:
        Entity m_Parent;

        float m_Radius = 1.0f;
        float m_X = 0;
        float m_Y = 0;
        float m_Angle = 0;
        float m_RadiusDestination = 1.0f;
        float m_XDestination = 0;
        float m_YDestination = 0;


        Physical(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
