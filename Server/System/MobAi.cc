#include <Server/System/MobAi.hh>

#include <cmath>

#include <Server/Component/Ai.hh>
#include <Server/Component/Physical.hh>
#include <Server/Component/Mob.hh>
#include <Server/Simulation.hh>

namespace app::system
{
    MobAi::MobAi(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void MobAi::TickIdle(Entity entity)
    {
        component::Mob &mob = m_Simulation.Get<component::Mob>(entity);
        component::Physical &physical = m_Simulation.Get<component::Physical>(entity);
        component::Ai &ai = m_Simulation.Get<component::Ai>(entity);
        ai.m_TicksUntilNextAction--;
        if (ai.m_TicksUntilNextAction == 0)
        {
            if (ai.m_AiState == component::Ai::AiState::IdleMoving)
            {
                ai.m_AiState = component::Ai::AiState::Idle;
                ai.m_TicksUntilNextAction = rand() % 50 + 25;
            }
            else if (ai.m_AiState == component::Ai::AiState::Idle)
            {
                ai.m_AiState = component::Ai::AiState::IdleMoving;
                ai.m_TicksUntilNextAction = rand() % 100 + 50;
                physical.Angle(((float)rand() / (float)RAND_MAX) * 3.141592653589 * 2);
            }
        }

        if (ai.m_AiState == component::Ai::AiState::IdleMoving)
        {
            physical.m_Acceleration += Vector::FromPolar(0.5f, physical.Angle());
        }
    }

    void MobAi::Tick()
    {
        component::ArenaInfo &arena = m_Simulation.Get<component::ArenaInfo>(m_Simulation.m_Arena);
        m_Simulation.ForEachEntity([&](Entity entity)
        {
            if (!m_Simulation.HasComponent<component::Mob>(entity))
                return;

            TickIdle(entity);
        });
    }

    void MobAi::PostTick()
    {
    }
}
