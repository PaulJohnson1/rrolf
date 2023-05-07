#include <Client/Simulation.hh>

#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Renderer.hh>
#include <Client/Ui/Button.hh>
#include <Client/Ui/Text.hh>
#include <Client/Ui/Engine.hh>
#include <Client/Ui/ButtonTypes.hh>

#include <Shared/StaticData.hh>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

app::Simulation *g_Simulation = nullptr;

namespace app
{
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)                                           \
    template <>                                                                        \
    component::COMPONENT &Simulation::Get<component::COMPONENT>(Entity id)             \
    {                                                                                  \
        RROLF_ASSERT(m_EntityTracker[id], "entity does not exist");                    \
        RROLF_ASSERT(m_##COMPONENT##Tracker[id], "component does not exist");          \
        return m_##COMPONENT##Components.d[id];                                        \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    component::COMPONENT const &Simulation::Get<component::COMPONENT>(Entity id) const \
    {                                                                                  \
        RROLF_ASSERT(m_EntityTracker[id], "entity does not exist");                    \
        RROLF_ASSERT(m_##COMPONENT##Tracker[id], "component does not exist");          \
        return m_##COMPONENT##Components.d[id];                                        \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    bool Simulation::HasComponent<component::COMPONENT>(Entity id) const               \
    {                                                                                  \
        RROLF_ASSERT(m_EntityTracker[id], "entity does not exist");                    \
        return m_##COMPONENT##Tracker[id];                                             \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    component::COMPONENT &Simulation::AddComponent<component::COMPONENT>(Entity id)    \
    {                                                                                  \
        RROLF_ASSERT(m_EntityTracker[id], "entity does not exist");                    \
        RROLF_ASSERT(!m_##COMPONENT##Tracker[id], "component already exists");         \
        m_##COMPONENT##Tracker[id] = true;                                             \
        new (&m_##COMPONENT##Components.d[id]) component::COMPONENT(id, this);         \
        return Get<component::COMPONENT>(id);                                          \
    }

    FOR_EACH_COMPONENT;

#undef RROLF_COMPONENT_ENTRY

    Simulation::Simulation(Renderer *renderer)
        : m_InterpolationSystem(*this),
          m_RendererSystem({*this, renderer}),
          m_Renderer(renderer)
    {
        std::fill(m_EntityTracker, m_EntityTracker + MAX_ENTITY_COUNT, false);
        g_Simulation = this;

        // ui test
        (m_UiElements.m_DeathScreen = ui::Add(
            ui::SetJustify<1, 1>(
                ui::MakeVContainer<200, 0>({
                    new ui::Text(*renderer, "You were killed by", 0xffffffff, 24),
                    ui::CreateRespawnButton(renderer)
                    }
                )
            )
        ))->m_Showing = false;
        m_UiElements.m_TitleScreen = ui::Add(
            ui::SetJustify<1, 1>(
                ui::MakeVContainer<100, 0>({
                    new ui::Text(*renderer, "florr.io", 0xffffffff, 96),
                    ui::MakeHContainer<25, 0>({
                        new ui::Text(*renderer, "this is your name", 0xffffffff, 25),
                        ui::CreateRespawnButton(renderer)
                    })
                })
            )
        );
        m_UiElements.m_Loadout = ui::Add(
            ui::VPad<10>(
                ui::SetJustify<1, 2>(
                    ui::MakeVContainer<10, 0, 1>({
                        ui::MakeHContainer<20, 10>({
                            ui::CreateLoadoutButton(renderer, 0),
                            ui::CreateLoadoutButton(renderer, 1),
                            ui::CreateLoadoutButton(renderer, 2),
                            ui::CreateLoadoutButton(renderer, 3),
                            ui::CreateLoadoutButton(renderer, 4),
                            ui::CreateLoadoutButton(renderer, 5),
                            ui::CreateLoadoutButton(renderer, 6),
                            ui::CreateLoadoutButton(renderer, 7),
                            ui::CreateLoadoutButton(renderer, 8),
                            ui::CreateLoadoutButton(renderer, 9)
                        }),
                        ui::MakeHContainer<20, 10>({
                            ui::CreateSecondaryButton(renderer, 10),
                            ui::CreateSecondaryButton(renderer, 11),
                            ui::CreateSecondaryButton(renderer, 12),
                            ui::CreateSecondaryButton(renderer, 13),
                            ui::CreateSecondaryButton(renderer, 14),
                            ui::CreateSecondaryButton(renderer, 15),
                            ui::CreateSecondaryButton(renderer, 16),
                            ui::CreateSecondaryButton(renderer, 17),
                            ui::CreateSecondaryButton(renderer, 18),
                            ui::CreateSecondaryButton(renderer, 19)
                        })
                    })
                )
            )
        );
        m_UiElements.m_Test = ui::Add(
            ui::HPad<10>(
                ui::SetJustify<0, 1>(
                    ui::AddBackground<0x80000000>(
                        ui::MakeVContainer<10, 10, 0>({
                            new ui::Text(*renderer, "Stinger", 0xffffffff, 25),
                            new ui::Text(*renderer, "Ultra", RARITY_COLORS[6], 12),
                            new ui::Text(*renderer, "It really hurts, but it's really fragile.", 0xffffffff, 12),
                            ui::MakeHContainer<0,0>({new ui::Text(*renderer, "Health: ", 0xffffffff, 12), new ui::Text(*renderer, "over 9000", 0xff23ee45, 12)}),
                            ui::MakeHContainer<0,0>({new ui::Text(*renderer, "Damage: ", 0xffffffff, 12), new ui::Text(*renderer, "beyond your feeble comprehension", 0xffee2345, 12)})
                        })
                    )
                )
            )
        );
    }

    float Simulation::GetTime()
    {
#ifdef EMSCRIPTEN
        return EM_ASM_DOUBLE({
            return performance.now();
        });
#else
        using namespace std::chrono;
        system_clock::time_point start = system_clock::now();

        return duration_cast<microseconds>(start.time_since_epoch()).count() / 1000;
#endif
    }

    void Simulation::ReadBinary(uint8_t *data)
    {
        bc::BinaryCoder coder{data};
        uint8_t type = coder.Read<bc::Uint8>();

        if (type == 0)
        {
            Entity deletedEntityCount = coder.Read<bc::VarUint>();
            for (Entity i = 0; i < deletedEntityCount; i++)
                Remove(coder.Read<bc::VarUint>());

            Entity updatedEntityCount = coder.Read<bc::VarUint>();
            for (Entity i = 0; i < updatedEntityCount; i++)
                ReadEntity(coder);
        }
    }

    void Simulation::Remove(Entity id)
    {
        RROLF_ASSERT(m_EntityTracker[id], "cannot remove nonexistant entity");
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)    \
    {                                           \
        using T = component::COMPONENT;         \
        if (HasComponent<T>(id))                \
        {                                       \
            T &comp = Get<T>(id);               \
            m_##COMPONENT##Tracker[id] = false; \
            comp.~T();                          \
        }                                       \
    }
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        m_EntityTracker[id] = false;
    }

    void Simulation::TickRenderer()
    {
        float time = GetTime();
        m_TickTime = time - m_LastTick;
        m_LastTick = time;
        if (m_PlayerInfo != (Entity)-1)
        {
            if (!m_HasHadPlayer && Get<component::PlayerInfo>(m_PlayerInfo).m_HasPlayer) m_HasHadPlayer = true;
            m_InterpolationSystem.Tick();
            m_RendererSystem.Tick();

            m_InterpolationSystem.PostTick();
            m_RendererSystem.PostTick();

            // ui stuff
            m_UiElements.m_TitleScreen->m_Showing = !Get<component::PlayerInfo>(m_PlayerInfo).m_HasPlayer && !m_HasHadPlayer;
            m_UiElements.m_DeathScreen->m_Showing = !Get<component::PlayerInfo>(m_PlayerInfo).m_HasPlayer && m_HasHadPlayer;
            ui::Resize((ui::Container *) m_UiElements.m_Loadout->m_Elements[0]);
            ui::Resize((ui::Container *) m_UiElements.m_Loadout->m_Elements[1]);
            ui::Resize(m_UiElements.m_Loadout);
            return;
        }
    }

    void Simulation::ReadEntity(bc::BinaryCoder &coder)
    {
        Entity id = coder.Read<bc::VarUint>();
        uint32_t componentFlags = coder.Read<bc::VarUint>();
        bool isCreation = !m_EntityTracker[id];
        if (isCreation)
        {
            CreateEntityWithId(id);
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    if (componentFlags & (1 << ID))          \
        AddComponent<component::COMPONENT>(id);
            FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        }

#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    if (componentFlags & (1 << ID))          \
        Get<component::COMPONENT>(id).UpdateFromBinary(coder);
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
    }

    Entity Simulation::CreateEntityWithId(Entity id)
    {
        m_EntityTracker[id] = true;
        return id;
    }
}