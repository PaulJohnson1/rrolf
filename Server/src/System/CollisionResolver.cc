#include <System/CollisionResolver.hh>

#include <Component/Physics.hh>
#include <Simulation.hh>
#include <Vector.hh>

namespace app::system
{
    CollisionResolver::CollisionResolver(Simulation &simulation)
        : m_Simulation(simulation),
    {
    }

    void CollisionResolver::Tick()
    {
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.GetOptional<component::Physics>(entity))
                return;
            component::Physics &physics = m_Simulation.Get<component::Physics>(entity);
            component::Position &position = m_Simulation.Get<component::Position>(entity);
            Vector tempPos = Vector(position.X(), position.Y());
            for (Entity other: physics.m_Collisions)
            {
                component::Physics &physics2 = m_Simulation.Get<component::Physics>(other);
                component::Position &position2 = m_Simulation.Get<component::Position>(other);
                Vector tempPos2 = Vector(position2.X(), position2.Y());
                //actual physics
                float ratio = physics.Mass() / (physics.Mass() + physics2.Mass());
                Vector dist = tempPos2 - tempPos;
                float distance = dist.Magnitude();
                tempPos2 += (dist.Normalize() *= (physics.Radius() + physics2.Radius() - distance)) * (ratio);
                tempPos += dist * ((ratio - 1) / ratio);
                //TODO: velocity change
                position2.X(tempPos2.m_X);
                position2.Y(tempPos2.m_Y);
            }
            position.X(tempPos.m_X);
            position.Y(tempPos.m_Y);
        });
    }
}
