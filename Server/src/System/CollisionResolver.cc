#include <System/CollisionResolver.hh>

#include <Component/Physical.hh>
#include <Simulation.hh>
#include <Vector.hh>

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
            if (!m_Simulation.GetOptional<component::Physical>(entity))
                return;

            component::Physical &physical1 = m_Simulation.Get<component::Physical>(entity);
            
            for (Entity other : physical1.m_Collisions)
            {
                component::Physical &physical2 = m_Simulation.Get<component::Physical>(other);
                Vector a = {physical1.X(), physical1.Y()};
                Vector b = {physical2.X(), physical2.Y()};
                Vector delta = a - b;
                float distance = delta.Magnitude();
                float overlap = (distance - physical1.Radius() - physical2.Radius()) / 2.0f;
                physical1.X(physical1.X() - overlap * delta.m_X / distance);
                physical1.Y(physical1.Y() - overlap * delta.m_Y / distance);
                physical2.X(physical2.X() + overlap * delta.m_Y / distance);
                physical2.Y(physical2.Y() + overlap * delta.m_X / distance);
            }
        });
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.GetOptional<component::Physical>(entity))
                return;
            component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
            Vector ball1Position = Vector(physical.X(), physical.Y());
            Vector ball1Velocity = Vector(physical.m_Velocity.m_X, physical.m_Velocity.m_Y);
            for (Entity other : physical.m_Collisions)
            {
                component::Physical &physical2 = m_Simulation.Get<component::Physical>(other);

                Vector ball2Position = Vector(physical2.X(), physical2.Y());
                Vector ball2Velocity = Vector(physical2.m_Velocity.m_X, physical2.m_Velocity.m_Y);
                Vector delta = ball2Position - ball1Position;
                float distance = delta.Magnitude();
                Vector normal = delta.Normalize();

                Vector tangential = {-normal.m_Y, normal.m_X};

                float dotTangential1 = ball1Velocity.m_X * tangential.m_X + ball1Velocity.m_Y * tangential.m_Y;
                float dotTangential2 = ball2Velocity.m_X * tangential.m_X + ball2Velocity.m_Y * tangential.m_Y;

                float dotNormal1 = ball1Velocity.m_X * normal.m_X + ball1Velocity.m_X * normal.m_Y;
                float dotNormal2 = ball2Velocity.m_X * normal.m_X + ball2Velocity.m_Y * normal.m_Y;

                float m1 = (dotNormal1 * (physical.m_Mass - physical2.m_Mass) + 2.0f * physical2.m_Mass * dotNormal2) / (physical.m_Mass + physical2.m_Mass);
                float m2 = (dotNormal2 * (physical2.m_Mass - physical.m_Mass) + 2.0f * physical.m_Mass * dotNormal1) / (physical.m_Mass + physical2.m_Mass);

                physical.m_Velocity.m_X = tangential.m_X * dotTangential1 + normal.m_X * m1;
                physical.m_Velocity.m_Y = tangential.m_Y * dotTangential1 + normal.m_Y * m1;
                physical2.m_Velocity.m_X = tangential.m_X * dotTangential2 + normal.m_X * m2;
                physical2.m_Velocity.m_Y = tangential.m_Y * dotTangential2 + normal.m_Y * m2;

                // Vector velocityDelta = ball1Velocity - ball2Velocity;
                // float p = 2.0f * (normal.m_X * velocityDelta.m_X + normal.m_Y * velocityDelta.m_Y) / (physical.m_Mass + physical2.m_Mass);
                // physical.m_Velocity.m_X -= p * physical2.m_Mass * normal.m_X;
                // physical.m_Velocity.m_X -= p * physical2.m_Mass * normal.m_Y;
                // physical2.m_Velocity.m_X += p * physical.m_Mass * normal.m_X;
                // physical2.m_Velocity.m_X += p * physical.m_Mass * normal.m_Y;

            //    float fDistance = sqrtf((b1->px - b2->px) * (b1->px - b2->px) + (b1->py - b2->py) * (b1->py - b2->py));

                // Normal
            //    float nx = (b2->px - b1->px) / fDistance;
            //    float ny = (b2->py - b1->py) / fDistance;
            //    float kx = (b1->vx - b2->vx);
            //    float ky = (b1->vy - b2->vy);
            //    float p = 2.0 * (nx * kx + ny * ky) / (b1->mass + b2->mass);
            //    b1->vx = b1->vx - p * b2->mass * nx;
            //    b1->vy = b1->vy - p * b2->mass * ny;
            //    b2->vx = b2->vx + p * b1->mass * nx;
            //    b2->vy = b2->vy + p * b1->mass * ny;

                // Vector tempPos2 = Vector(position2.X(), position2.Y());
                // //actual physical
                // float ratio = physical.m_Mass / (physical.m_Mass + physical2.m_Mass);
                // Vector delta = tempPos2 - ball1Position;
                // float distance = delta.Magnitude();
                // tempPos2 += (delta.Normalize() * (physical.Radius() + physical2.Radius() - distance)) * (ratio);
                // ball1Position += delta * ((ratio - 1) / ratio);
                // //TODO: velocity change
                // physical2.X(tempPos2.m_X);
                // physical2.Y(tempPos2.m_Y);
            }
            // physical.X(ball1Position.m_X);
            // physical.Y(ball1Position.m_Y);
        });
    }

    void CollisionResolver::PostTick()
    {
    }
}
