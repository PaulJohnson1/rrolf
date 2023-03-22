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
            if (m_Simulation.GetOptional<component::Position>(entity))
            {
                component::Position &position = m_Simulation.Get<component::Position>(entity);

                if (position.m_X == 0)
                    position.m_X = position.m_XDestination;
                if (position.m_Y == 0)
                    position.m_Y = position.m_YDestination;
                position.m_X = std::lerp<float>(position.m_X, position.m_XDestination, 0.1);
                position.m_Y = std::lerp<float>(position.m_Y, position.m_YDestination, 0.1);
            } });
    }

    void Interpolation::PostTick()
    {
    }
}
