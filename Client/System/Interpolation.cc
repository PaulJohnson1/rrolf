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
        // float fpsScale = 60 / (1_000_000 / m_TickTime);
        float fpsScale = 1;
        m_Simulation.m_Camera.m_X = Lerp<float>(m_Simulation.m_Camera.m_X, m_Simulation.m_Camera.m_XDestination, 0.05 * fpsScale);
        m_Simulation.m_Camera.m_Y = Lerp<float>(m_Simulation.m_Camera.m_Y, m_Simulation.m_Camera.m_YDestination, 0.05 * fpsScale);
        m_Simulation.m_Camera.m_Fov = Lerp<float>(m_Simulation.m_Camera.m_Fov, m_Simulation.m_Camera.m_FovDestination, 0.025 * fpsScale);

        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (m_Simulation.GetOptional<component::Physical>(entity))
            {
                component::Physical &physical = m_Simulation.Get<component::Physical>(entity);

                if (physical.m_X == 0)
                    physical.m_X = physical.m_XDestination;
                if (physical.m_Y == 0)
                    physical.m_Y = physical.m_YDestination;
                if (physical.m_Radius == 0)
                    physical.m_Radius = physical.m_YDestination;
                if (physical.m_Angle == 0)
                    physical.m_Angle = physical.m_AngleDestination;
                physical.m_X = Lerp<float>(physical.m_X, physical.m_XDestination, 0.1 * fpsScale);
                physical.m_Y = Lerp<float>(physical.m_Y, physical.m_YDestination, 0.1 * fpsScale);
                physical.m_Radius = Lerp<float>(physical.m_Radius, physical.m_RadiusDestination, 0.1 * fpsScale);
                physical.m_Angle = Lerp<float>(physical.m_Angle, physical.m_AngleDestination, 0.1 * fpsScale);
            }
            if (m_Simulation.GetOptional<component::Flower>(entity))
            {
                component::Flower &flower = m_Simulation.Get<component::Flower>(entity);

                flower.m_EyeX = Lerp<float>(flower.m_EyeX, flower.m_EyeXDestination, 0.25 * fpsScale);
                flower.m_EyeY = Lerp<float>(flower.m_EyeY, flower.m_EyeYDestination, 0.25 * fpsScale);
                flower.m_EyeXDestination = 2.5 * std::cos(flower.m_EyeAngle);
                flower.m_EyeYDestination = 4 * std::sin(flower.m_EyeAngle);
            }
        });
    }

    void Interpolation::PostTick()
    {
    }
}
