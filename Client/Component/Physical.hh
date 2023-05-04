#pragma once

#include <cstdint>

#include <Shared/Entity.hh>
#include <Client/Util/Lerp.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Simulation;
}

namespace app::component
{
    class Physical
    {
    public:
        Simulation *m_Simulation;
        Entity m_Parent;

        Lerp<float> m_Radius = Lerp<float>(1.0f);
        Lerp<float> m_X = Lerp<float>(0.0f);
        Lerp<float> m_Y = Lerp<float>(0.0f);
        Lerp<float, true> m_Angle = Lerp<float, true>(0.0f);
        Lerp<float> m_DeletionTick = Lerp<float>(0.0f);

        Physical(Entity, Simulation *);

        void UpdateFromBinary(bc::BinaryCoder &);
    };
}
