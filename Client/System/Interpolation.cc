#include <Client/System/Interpolation.hh>

#include <iostream>
#include <cmath>

#include <Client/Simulation.hh>
#include <Client/Util/Lerp.hh>

namespace app::system
{
    Interpolation::Interpolation(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void Interpolation::Tick()
    {
        // component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_Simulation.m_PlayerInfo);
        // playerInfo.m_X.tick(0.05);
        // playerInfo.m_Y.tick(0.05);
        // playerInfo.m_Fov.tick(0.25);

        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (m_Simulation.HasComponent<component::Physical>(entity))
            {
                component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
                physical.m_X.tick(0.1);
                physical.m_Y.tick(0.1);
                physical.m_Radius.tick(0.1);
                physical.m_Angle.tick(0.1);
            }
            if (m_Simulation.HasComponent<component::Flower>(entity))
            {
                component::Flower &flower = m_Simulation.Get<component::Flower>(entity);
                flower.m_EyeX = 2.5 * std::cos(flower.m_EyeAngle);
                flower.m_EyeY = 4 * std::sin(flower.m_EyeAngle);
                flower.m_EyeX.tick(0.25);
                flower.m_EyeY.tick(0.25);
            }
        });
    }

    void Interpolation::PostTick()
    {
    }
}
