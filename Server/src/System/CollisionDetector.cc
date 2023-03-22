#include <System/CollisionDetector.hh>

#include <Simulation.hh>
#include <Vector.hh>

namespace app::system
{
    CollisionDetector::CollisionDetector(Simulation &simulation)
        : m_Simulation(simulation),
          m_SpatialHash(simulation)
    {
    }

    void CollisionDetector::Tick()
    {
        // insert physical entitis
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.GetOptional<component::Physics>(entity))
                return;
            m_SpatialHash.Insert(entity);
        });

        // find detection with physical entities
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.GetOptional<component::Physics>(entity))
                return;
                
            component::Physics &physics = m_Simulation.Get<component::Physics>(entity);
            component::Position &position = m_Simulation.Get<component::Position>(entity);
            Vector positionVector{position.X(), position.Y()};

            std::vector<Entity> possibleCollisions = m_SpatialHash.GetCollisions(entity);
            for (Entity id : possibleCollisions)
            {
                if (id == entity)
                    continue;
                component::Physics &physics2 = m_Simulation.Get<component::Physics>(id);
                component::Position &position2 = m_Simulation.Get<component::Position>(id);
                Vector position2Vector{position2.X(), position2.Y()};

                if ((positionVector - position2Vector) < (physics.Radius() + physics2.Radius()))
                {
                    if (std::find(physics.m_Collisions.begin(), physics.m_Collisions.end(), id) == physics.m_Collisions.end()
                    && std::find(physics2.m_Collisions.begin(), physics2.m_Collisions.end(), id) == physics2.m_Collisions.end()
                    && std::find(physics.m_Collisions.begin(), physics.m_Collisions.end(), entity) == physics.m_Collisions.end()
                    && std::find(physics2.m_Collisions.begin(), physics2.m_Collisions.end(), entity) == physics2.m_Collisions.end())
                        physics.m_Collisions.push_back(id);
                }
            }
        });
    }

    void CollisionDetector::PostTick()
    {
        m_SpatialHash.Clear();
    }
}
