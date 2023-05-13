#include <Server/System/CollisionDetector.hh>

#include <Server/Simulation.hh>
#include <Server/Vector.hh>

#include <iostream>
namespace app::system
{
    CollisionDetector::CollisionDetector(Simulation &simulation)
        : m_Simulation(simulation),
          m_SpatialHash(simulation)
    {
    }

    void CollisionDetector::Tick()
    {
        m_SpatialHash.Clear();
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
                        
            /*
            THIS IS INTENTIONAL
            */
            component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
            
            if (physical.DeletionTick() != 0)
            {
                if (physical.DeletionTick() >= 5)
                    m_Simulation.RequestDeletion<false>(entity);
                else 
                    physical.DeletionTick(1);
                return;
            }
            if (m_Simulation.HasComponent<component::Petal>(entity))
                return;
            if (m_Simulation.HasComponent<component::Drop>(entity))
                return;

            float a = physical.X();
            float b = physical.Y();
            /*
            //brute force implementation

            m_Simulation.ForEachEntity([&](Entity entity2)
            {
                if (entity == entity2) return;
                if (!m_Simulation.HasComponent<component::Physical>(entity2))
                    return;
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
            */

            // spatial hashing implementation
            std::vector<Entity> possibleCollisions = m_SpatialHash.GetCollisions(entity);
            for (Entity i = 0; i < possibleCollisions.size(); i++)
            {
                Entity id = possibleCollisions[i];
                if (id >= 768)
                    std::cout << "cooldetect" << id << '\n';
                if (!IsValidCollision(entity, id))
                    continue;
                component::Physical &physical2 = m_Simulation.Get<component::Physical>(id);
                if (physical2.DeletionTick() != 0)
                    continue;
                float c = physical2.X();
                float d = physical2.Y();
                float e = a - c;
                float f = b - d;
                float g = physical.Radius() + physical2.Radius();
                if (e * e + f * f < g * g)
                {
                    if (std::find(physical.m_Collisions.begin(), physical.m_Collisions.end(), id) == physical.m_Collisions.end()
                        && std::find(physical2.m_Collisions.begin(), physical2.m_Collisions.end(), id) == physical2.m_Collisions.end()
                        && std::find(physical.m_Collisions.begin(), physical.m_Collisions.end(), entity) == physical.m_Collisions.end()
                        && std::find(physical2.m_Collisions.begin(), physical2.m_Collisions.end(), entity) == physical2.m_Collisions.end())
                            physical.m_Collisions.push_back(id);
                }
            }
        });
    }

    bool CollisionDetector::IsValidCollision(Entity a, Entity b)
    {
        //ORDER MATTERS! a cannot be a petal or drop
        if (a == b) 
            return false;

        if (m_Simulation.HasComponent<component::Flower>(a))
        {
            if (m_Simulation.HasComponent<component::Petal>(b))
                return false;
            return true;
        }
        return true;
    }
}
