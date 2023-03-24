#include <System/Damage.hh>

#include <Component/Life.hh>
#include <Component/Physical.hh>
#include <Simulation.hh>

namespace app::system
{
    Damage::Damage(Simulation &simulation)
        : m_Simulation(simulation),
    {
    }

    void Damage::Tick()
    {
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.GetOptional<component::Physical>(entity))
                return;
            component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
            component::Life &life = m_Simulation.Get<component::Life>(entity);
            Vector tempPos = Vector(physical.X(), physical.Y());
            for (Entity other: physical.m_Collisions)
            {
                if (!m_Simulation.GetOptional<component::Life>(other))
                    continue;
                component::Life &life2 = m_Simulation.Get<component::Life>(entity);
                life -= life2.Damage();
                life2 -= life.Damage();

                // TODO: delete entity
            }
        });
    }
}
