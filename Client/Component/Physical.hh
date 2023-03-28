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

        float m_Radius;
        float m_X;
        float m_Y;
        float m_Angle;
        float m_RadiusDestination;
        float m_XDestination;
        float m_YDestination;


        Physical(Entity);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
