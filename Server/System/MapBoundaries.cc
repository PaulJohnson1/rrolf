#include <Server/System/MapBoundaries.hh>

#include <Server/Component/Life.hh>
#include <Server/Component/Physical.hh>
#include <Server/Simulation.hh>

namespace app::system
{
    MapBoundaries::MapBoundaries(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void MapBoundaries::Tick()
    {
        component::ArenaInfo &arena = m_Simulation.Get<component::ArenaInfo>(m_Simulation.m_Arena);
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.HasComponent<component::Physical>(entity))
                return;

            component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
            Vector position = {physical.X(), physical.Y()};
            if (position > arena.MapSize() - physical.Radius())
            {
                if (m_Simulation.HasComponent<component::Petal>(entity) && m_Simulation.Get<component::Petal>(entity).m_Detached)
                    m_Simulation.RequestDeletion<true>(entity);
                position.Magnitude(arena.MapSize() - physical.Radius());
            }

            physical.X(position.m_X);
            physical.Y(position.m_Y);
        });
    }

    void MapBoundaries::PostTick()
    {
    }
}
