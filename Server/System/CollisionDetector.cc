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
            if (!m_Simulation.HasComponent<component::Physical>(entity))
                return;
            m_SpatialHash.Insert(entity); });

        // find detection with physical entities
        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (!m_Simulation.HasComponent<component::Physical>(entity))
                return;
                
            component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
            float a = physical.X();
            float b = physical.Y();

            m_Simulation.ForEachEntity([&](Entity entity2)
            {
                if (entity == entity2) return;
                component::Physical &physical2 = m_Simulation.Get<component::Physical>(entity2);
                float c = physical2.X();
                float d = physical2.Y();
                float e = a - c;
                float f = b - d;
                float g = physical.Radius() + physical2.Radius();
                if (e * e + f * f < g * g)
                    if (std::find(physical.m_Collisions.begin(), physical.m_Collisions.end(), entity2) == physical.m_Collisions.end()
                        && std::find(physical2.m_Collisions.begin(), physical2.m_Collisions.end(), entity2) == physical2.m_Collisions.end()
                        && std::find(physical.m_Collisions.begin(), physical.m_Collisions.end(), entity) == physical.m_Collisions.end()
                        && std::find(physical2.m_Collisions.begin(), physical2.m_Collisions.end(), entity) == physical2.m_Collisions.end())
                            physical.m_Collisions.push_back(entity2);
            });

            // std::vector<Entity> possibleCollisions = m_SpatialHash.GetCollisions(entity);
            // for (Entity i = 0; i < possibleCollisions.size(); i++)
            // {
            //     Entity id = possibleCollisions[i];
            //     if (id == entity)
            //         continue;
            //     component::Physical &physical2 = m_Simulation.Get<component::Physical>(id);
            //     float c = physical2.X();
            //     float d = physical2.Y();
            //     float e = a - c;
            //     float f = b - d;
            //     float g = physical.Radius() + physical2.Radius();
            //     if (e * e + f * f < g * g)
            //     {
            //         if (std::find(physical.m_Collisions.begin(), physical.m_Collisions.end(), id) == physical.m_Collisions.end()
            //             && std::find(physical2.m_Collisions.begin(), physical2.m_Collisions.end(), id) == physical2.m_Collisions.end()
            //             && std::find(physical.m_Collisions.begin(), physical.m_Collisions.end(), entity) == physical.m_Collisions.end()
            //             && std::find(physical2.m_Collisions.begin(), physical2.m_Collisions.end(), entity) == physical2.m_Collisions.end())
            //                 physical.m_Collisions.push_back(id);
            //     }
            // }
            });
    }

    void CollisionDetector::PostTick()
    {
        m_SpatialHash.Clear();
    }
}
