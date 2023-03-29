#include <Server/System/CollisionResolver.hh>

#include <Server/Component/Physical.hh>
#include <Server/Simulation.hh>
#include <Server/Vector.hh>

namespace app::system
{
    CollisionResolver::CollisionResolver(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void CollisionResolver::Tick()
    {
        // static collisions
        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (!m_Simulation.HasComponent<component::Physical>(entity))
                return;

            component::Physical &physical1 = m_Simulation.Get<component::Physical>(entity);
            
            for (Entity i = 0 ; i < physical1.m_Collisions.size(); i++)
            {
                Entity other = physical1.m_Collisions[i];
                component::Physical &physical2 = m_Simulation.Get<component::Physical>(other);
                Vector a = {physical1.X(), physical1.Y()};
                Vector b = {physical2.X(), physical2.Y()};
                Vector delta = a - b;
                float distance = delta.Magnitude();
                float overlap = (distance - physical1.Radius() - physical2.Radius()) * 0.5f;
                physical1.X(physical1.X() - overlap * delta.m_X / distance);
                physical1.Y(physical1.Y() - overlap * delta.m_Y / distance);
                physical2.X(physical2.X() + overlap * delta.m_Y / distance);
                physical2.Y(physical2.Y() + overlap * delta.m_X / distance);
            }
        });
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.HasComponent<component::Physical>(entity))
                return;
            component::Physical &physical1 = m_Simulation.Get<component::Physical>(entity);
            Vector ball1Position = Vector(physical1.X(), physical1.Y());
            Vector ball1Velocity = Vector(physical1.m_Velocity.m_X, physical1.m_Velocity.m_Y);
            for (Entity i = 0 ; i < physical1.m_Collisions.size(); i++)
            {
                Entity other = physical1.m_Collisions[i];
                component::Physical &physical2 = m_Simulation.Get<component::Physical>(other);

                Vector ball2Position = Vector(physical2.X(), physical2.Y());
                Vector ball2Velocity = Vector(physical2.m_Velocity.m_X, physical2.m_Velocity.m_Y);
                float v2_Coeff = 2.0f * physical1.m_Mass / (physical1.m_Mass + physical2.m_Mass);
                float v1_Coeff = 2.0f * physical2.m_Mass / (physical1.m_Mass + physical2.m_Mass);
                float v_SharedCoeff = (physical1.m_Mass - physical2.m_Mass) / (physical1.m_Mass + physical2.m_Mass);
                
                Vector delta = (ball2Position - ball1Position).Normalize();
                Vector parallel1 = delta * (delta * ball1Velocity);
                Vector perp1 = ball1Velocity - parallel1;
                Vector parallel2 = delta * (delta * ball2Velocity);
                Vector perp2 = ball2Velocity - parallel2;

                physical1.m_Velocity = ((parallel2 * v1_Coeff) + (parallel1 * v_SharedCoeff)) * physical2.m_Restitution + perp1;
                physical2.m_Velocity = ((parallel1 * v2_Coeff) - (parallel2 * v_SharedCoeff)) * physical1.m_Restitution + perp2;
            }
        });
    }

    void CollisionResolver::PostTick()
    {
    }
}
