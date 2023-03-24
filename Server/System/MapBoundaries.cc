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
            if (!m_Simulation.GetOptional<component::Physical>(entity))
                return;

            component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
            Vector position = {physical.X(), physical.Y()};
            if (position > arena.MapSize() - physical.Radius())
            {
                position.Magnitude(arena.MapSize() - physical.Radius());
                // physical.m_Acceleration += position.Normalize() * -0.1;
            }

            physical.X(position.m_X);
            physical.Y(position.m_Y);
        });
    }

    void MapBoundaries::PostTick()
    {
    }
}
