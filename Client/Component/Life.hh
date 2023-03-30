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
    class Renderer;
    class Simulation;
}

namespace app::component
{
    class Life
    {
    public:
        Simulation *m_Simulation;
        Entity m_Parent;

        Lerp<float> m_Health = Lerp<float>(1.0f);
        Lerp<float> m_MaxHealth = Lerp<float>(1.0f);

        Life(Entity, Simulation *);
        void UpdateFromBinary(bc::BinaryCoder &);
        void Render(Renderer *ctx);
    };
}