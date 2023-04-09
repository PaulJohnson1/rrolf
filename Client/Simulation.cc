#include <Client/Simulation.hh>

#include <cassert>
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
        assert(m_EntityTracker[id]);                                                   \
        assert(m_##COMPONENT##Tracker[id]);                                            \
        return m_##COMPONENT##Components.d[id];                                        \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    component::COMPONENT const &Simulation::Get<component::COMPONENT>(Entity id) const \
    {                                                                                  \
        assert(m_EntityTracker[id]);                                                   \
        assert(m_##COMPONENT##Tracker[id]);                                            \
        return m_##COMPONENT##Components.d[id];                                        \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    bool Simulation::HasComponent<component::COMPONENT>(Entity id) const               \
    {                                                                                  \
        return m_##COMPONENT##Tracker[id];                                             \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    component::COMPONENT &Simulation::AddComponent<component::COMPONENT>(Entity id)    \
    {                                                                                  \
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

        //ui test
        m_UiElements["DeathScreen"] = ui::Add(
            ui::SetJustify<1,1>(
                ui::MakeVContainer<200,0>({
                    new ui::Text(*renderer, "You were killed by", 0xffffffff, 24),
                    ui::CreateRespawnButton(renderer)
                    })
            )
        );
        m_UiElements["Loadout"] = ui::Add(
            ui::VPad<10>(
                ui::SetJustify<1,2>(
                    ui::MakeHContainer<20,10>({
                        ui::CreateLoadoutButton(renderer),
                        ui::CreateLoadoutButton(renderer),
                        ui::CreateLoadoutButton(renderer),
                        ui::CreateLoadoutButton(renderer)
                        })
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
        std::cout << "entity with id " << std::to_string(id) << " deleted\n";
        assert(m_EntityTracker[id]);
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
            m_InterpolationSystem.Tick();
            m_RendererSystem.Tick();

            m_InterpolationSystem.PostTick();
            m_RendererSystem.PostTick();

            //ui stuff
            m_UiElements["DeathScreen"]->m_Showing = !Get<component::PlayerInfo>(m_PlayerInfo).m_HasPlayer;
            return;
        }
        std::cout << "waiting for player to spawn\n";
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
