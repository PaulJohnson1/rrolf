#include <Server/System/DropCollector.hh>

#include <Server/Component/Physical.hh>
#include <Server/Simulation.hh>
#include <Server/Vector.hh>

namespace app::system
{
    DropCollector::DropCollector(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void DropCollector::Tick()
    {
        // drop collection
        std::vector<Entity> deletedEntities = {};
        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (!m_Simulation.HasComponent<component::Physical>(entity))
                return;
            if (!m_Simulation.HasComponent<component::Flower>(entity))
                return;

            component::Physical &physical1 = m_Simulation.Get<component::Physical>(entity);
            component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_Simulation.Get<component::Basic>(entity).m_Owner);
            
            for (Entity i = 0; i < physical1.m_Collisions.size(); i++)
            {
                Entity other = physical1.m_Collisions[i];
                
                if (!m_Simulation.HasComponent<component::Drop>(other))
                    continue;
                
                component::Drop &drop = m_Simulation.Get<component::Drop>(other);
                ++playerInfo.m_Inventory[drop.Id() * RarityId::kMaxRarities + drop.Rarity()];
                if (std::find(deletedEntities.begin(), deletedEntities.end(), other) == deletedEntities.end())
                    deletedEntities.push_back(other);
            }
        });
        for (uint64_t i = 0; i < deletedEntities.size(); i++)
            m_Simulation.RequestDeletion(deletedEntities[i]);
    }

    void DropCollector::PostTick()
    {
    }
}
