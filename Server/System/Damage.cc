#include <Server/System/Damage.hh>

#include <Server/Component/Life.hh>
#include <Server/Component/Physical.hh>
#include <Server/Simulation.hh>

namespace app::system
{
    Damage::Damage(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void Damage::Tick()
    {
        std::vector<Entity> deletedEntities = {};
        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (!m_Simulation.HasComponent<component::Life>(entity))
                return;
            component::Life &life = m_Simulation.Get<component::Life>(entity);
            component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
            component::Basic &basic = m_Simulation.Get<component::Basic>(entity);
            for (Entity i = 0; i < physical.m_Collisions.size(); i++)
            {
                Entity other = physical.m_Collisions[i];
                if (!m_Simulation.HasComponent<component::Life>(other))
                    continue;
                component::Life &life2 = m_Simulation.Get<component::Life>(other);
                component::Basic &basic2 = m_Simulation.Get<component::Basic>(other);
                if (basic.Team() == basic2.Team())
                    continue;
                life.Health(life.Health() - life2.m_Damage);
                life2.Health(life2.Health() - life.m_Damage);

                if (life.Health() == 0) 
                    if (std::find(deletedEntities.begin(), deletedEntities.end(), entity) == deletedEntities.end())
                        deletedEntities.push_back(entity);
                if (life2.Health() == 0)
                    if (std::find(deletedEntities.begin(), deletedEntities.end(), other) == deletedEntities.end())
                        deletedEntities.push_back(other);
            } });

            for (uint64_t i = 0; i < deletedEntities.size(); i++)
                m_Simulation.RequestDeletion(deletedEntities[i]);
    }

    void Damage::PostTick()
    {
    }
}
