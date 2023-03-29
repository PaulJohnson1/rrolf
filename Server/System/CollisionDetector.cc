#include <Server/System/CollisionDetector.hh>

#include <Server/Simulation.hh>
#include <Server/Vector.hh>

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
            if (!m_Simulation.GetOptional<component::Physical>(entity))
                return;
            m_SpatialHash.Insert(entity); });

        // find detection with physical entities
        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (!m_Simulation.GetOptional<component::Physical>(entity))
                return;
                
            component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
            Vector positionVector{physical.X(), physical.Y()};

            std::vector<Entity> possibleCollisions = m_SpatialHash.GetCollisions(entity);
            for (Entity i = 0; i < possibleCollisions.size(); i++)
            {
                Entity id = possibleCollisions[i];
                if (id == entity)
                    continue;
                component::Physical &physical2 = m_Simulation.Get<component::Physical>(id);
                Vector position2Vector{physical2.X(), physical2.Y()};

                if ((positionVector - position2Vector) < (physical.Radius() + physical2.Radius()))
                {
                    if (std::find(physical.m_Collisions.begin(), physical.m_Collisions.end(), id) == physical.m_Collisions.end()
                        && std::find(physical2.m_Collisions.begin(), physical2.m_Collisions.end(), id) == physical2.m_Collisions.end()
                        && std::find(physical.m_Collisions.begin(), physical.m_Collisions.end(), entity) == physical.m_Collisions.end()
                        && std::find(physical2.m_Collisions.begin(), physical2.m_Collisions.end(), entity) == physical2.m_Collisions.end())
                            physical.m_Collisions.push_back(id);
                }
            } });
    }

    void CollisionDetector::PostTick()
    {
        m_SpatialHash.Clear();
    }
}
