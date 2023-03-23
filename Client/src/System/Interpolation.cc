#include <System/Interpolation.hh>

#include <cmath>
#include <iostream>

#include <Simulation.hh>

namespace app::system
{
    Interpolation::Interpolation(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void Interpolation::Tick()
    {
        m_Simulation.m_Camera.m_X = std::lerp<float>(m_Simulation.m_Camera.m_X, m_Simulation.m_Camera.m_XDestination, 0.05);
        m_Simulation.m_Camera.m_Y = std::lerp<float>(m_Simulation.m_Camera.m_Y, m_Simulation.m_Camera.m_YDestination, 0.05);
        m_Simulation.m_Camera.m_Fov = std::lerp<float>(m_Simulation.m_Camera.m_Fov, m_Simulation.m_Camera.m_FovDestination, 0.025);

        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (m_Simulation.GetOptional<component::Render>(entity))
            {
                component::Physical &physical = m_Simulation.Get<component::Physical>(entity);

                if (physical.m_X == 0)
                    physical.m_X = physical.m_XDestination;
                if (physical.m_Y == 0)
                    physical.m_Y = physical.m_YDestination;
                if (physical.m_Radius == 0)
                    physical.m_Y = physical.m_YDestination;
                physical.m_X = std::lerp<float>(physical.m_X, physical.m_XDestination, 0.1);
                physical.m_Y = std::lerp<float>(physical.m_Y, physical.m_YDestination, 0.1);
                physical.m_Radius = std::lerp<float>(physical.m_Radius, physical.m_RadiusDestination, 0.1);
            } });
    }

    void Interpolation::PostTick()
    {
    }
}
