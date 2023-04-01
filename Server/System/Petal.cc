#include <Server/System/Petal.hh>

#include <Server/Component/Petal.hh>
#include <Server/Component/PlayerInfo.hh>
#include <Server/Simulation.hh>

namespace app::system
{
    Petal::Petal(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void Petal::Tick()
    {
        component::ArenaInfo &arena = m_Simulation.Get<component::ArenaInfo>(m_Simulation.m_Arena);
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.HasComponent<component::Petal>(entity))
                return;
            component::Petal &petal = m_Simulation.Get<component::Petal>(entity);

        });
    }
}
