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
        component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_Simulation.m_PlayerInfo);
        playerInfo.m_CameraX.Tick(0.1);
        playerInfo.m_CameraY.Tick(0.1);
        playerInfo.m_Fov.Tick(0.25);

        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (m_Simulation.HasComponent<component::Physical>(entity))
            {
                component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
                physical.m_X.Tick(0.1);
                physical.m_Y.Tick(0.1);
                physical.m_Radius.Tick(0.1);
                physical.m_Angle.Tick(0.1);
            }
            if (m_Simulation.HasComponent<component::Flower>(entity))
            {
                component::Flower &flower = m_Simulation.Get<component::Flower>(entity);
                flower.m_EyeX = 2.5 * std::cos(flower.m_EyeAngle);
                flower.m_EyeY = 4 * std::sin(flower.m_EyeAngle);
                flower.m_EyeX.Tick(0.25);
                flower.m_EyeY.Tick(0.25);
            }
            if (m_Simulation.HasComponent<component::Life>(entity))
            {
                component::Life &life = m_Simulation.Get<component::Life>(entity);
                life.m_Health.Tick(0.2);
                life.m_HealthRedAnimation.Tick(0.05);
                life.m_HealthRedAnimation = (float)life.m_Health;
                life.m_MaxHealth.Tick(0.1);
            }

        });
    }

    void Interpolation::PostTick()
    {
    }
}
