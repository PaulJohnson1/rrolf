#include <System/Velocity.hh>

#include <Simulation.hh>
#include <Vector.hh>

namespace app::system
{
    Velocity::Velocity(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void Velocity::Tick()
    {
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.GetOptional<component::Physics>(entity))
                return;

            component::Physics &physics = m_Simulation.Get<component::Physics>(entity);
            component::Position &position = m_Simulation.Get<component::Position>(entity);
            
            Vector positionVector{position.X(), position.Y()};

            physics.m_Velocity += physics.m_Acceleration;
            physics.m_Acceleration.Set(0, 1);
            positionVector += physics.m_Velocity;

            // for testing
            // physics.m_Velocity *= physics.Friction();
            if (physics.m_Velocity < 0.1f)
                physics.m_Velocity.Set(0, 0);

            position.X(positionVector.m_X);
            position.Y(positionVector.m_Y); });
    }
}
