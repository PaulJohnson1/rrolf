#include <System/Physics.hh>

#include <Entity.hh>
#include <Simulation.hh>

namespace app::system
{
    Physics::Physics(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void Physics::Tick()
    {
        m_Simulation.ForEachEntity([&](Entity &entity)
                                   {
            if (!entity.m_Physics)
                return;

            component::Physics &physics = *entity.m_Physics;
            component::Position &position = *entity.m_Position;
            
            Vector positionVector{position.X(), position.Y()};

            physics.m_Velocity += physics.m_Acceleration;
            physics.m_Acceleration.Set(0, 0);
            positionVector += physics.m_Velocity;

            physics.m_Velocity *= 0.9;
            if (physics.m_Velocity < 0.1)
                physics.m_Velocity.Set(0, 0);

            position.X(positionVector.m_X);
            position.Y(positionVector.m_Y); });
    }
}
