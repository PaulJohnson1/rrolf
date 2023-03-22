#include <System/Damage.hh>

#include <Component/Life.hh>
#include <Component/Physics.hh>
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
            if (!m_Simulation.GetOptional<component::Physics>(entity))
                return;
            component::Physics &physics = m_Simulation.Get<component::Physics>(entity);
            component::Position &life = m_Simulation.Get<component::Life>(entity);
            Vector tempPos = Vector(position.X(), position.Y());
            for (Entity other: physics.m_Collisions)
            {
                if (!m_Simulation.GetOptional<component::Life>(other))
                    continue;
                component::Position &life2 = m_Simulation.Get<component::Life>(entity);
                life -= life2.Damage();
                life2 -= life.Damage();

                // TODO: delete entity
            }
        });
    }
}
