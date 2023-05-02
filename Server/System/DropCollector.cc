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
                if (std::find(drop.m_CollectedBy.begin(), drop.m_CollectedBy.end(), entity) != drop.m_CollectedBy.end())
                    continue;
                ++playerInfo.m_Inventory[drop.Id() * RarityId::kMaxRarities + drop.Rarity()];
                drop.m_CollectedBy.push_back(entity);
            }
        });
        m_Simulation.ForEachEntity([&](Entity entity) 
        {
            if (!m_Simulation.HasComponent<component::Drop>(entity))
                return;
            component::Drop &drop = m_Simulation.Get<component::Drop>(entity);
            if (m_Simulation.m_TickCount - m_Simulation.Get<component::Basic>(entity).m_CreationTick >= (drop.Rarity() + 1) * 50)
                m_Simulation.RequestDeletion<true>(entity);
        });
    }

    void DropCollector::PostTick()
    {
    }
}
