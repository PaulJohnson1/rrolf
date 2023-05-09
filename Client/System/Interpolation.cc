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
            if (m_Simulation.HasComponent<component::Drop>(entity))
            {
                component::Drop &drop = m_Simulation.Get<component::Drop>(entity);
                if (drop.m_PickedUp)
                {
                    component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
                    if (physical.m_ClientDeletionTick < 5)
                        physical.m_ClientDeletionTick += 0.5;
                    physical.m_X = (float) playerInfo.m_CameraX;
                    physical.m_Y = (float) playerInfo.m_CameraY;
                }
            }
            if (m_Simulation.HasComponent<component::Physical>(entity))
            {
                component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
                physical.m_X.Tick(0.2);
                physical.m_Y.Tick(0.2);
                physical.m_Radius.Tick(0.1);
                physical.m_Angle.Tick(0.1);
                if (physical.m_DeletionTick > 0 && physical.m_ClientDeletionTick < 5)
                    physical.m_ClientDeletionTick += 0.5;
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
                

                if (life.m_DamageAnimationTick > 0)
                    --life.m_DamageAnimationTick;
                else
                    life.m_HealthRedAnimation.Tick(0.2);
                life.m_HealthRedAnimation = (float)life.m_Health;
            }
        });
    }

    void Interpolation::PostTick()
    {
    }
}
