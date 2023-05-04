#pragma once

#include <cstdint>
#include <optional>
#include <map>
#include <string>

#define FOR_EACH_COMPONENT               \
    RROLF_COMPONENT_ENTRY(Flower, 0)     \
    RROLF_COMPONENT_ENTRY(Petal, 1)      \
    RROLF_COMPONENT_ENTRY(Ai, 2)         \
    RROLF_COMPONENT_ENTRY(ArenaInfo, 3)  \
    RROLF_COMPONENT_ENTRY(Life, 4)       \
    RROLF_COMPONENT_ENTRY(Physical, 5)   \
    RROLF_COMPONENT_ENTRY(Mob, 6)        \
    RROLF_COMPONENT_ENTRY(PlayerInfo, 7) \
    RROLF_COMPONENT_ENTRY(Basic, 8) \
    RROLF_COMPONENT_ENTRY(Drop, 9) \
    RROLF_COMPONENT_ENTRY(Projectile, 10) \
    RROLF_COMPONENT_ENTRY(Heal, 11)

#include <Client/Component/Ai.hh>
#include <Client/Component/ArenaInfo.hh>
#include <Client/Component/Basic.hh>
#include <Client/Component/Drop.hh>
#include <Client/Component/Flower.hh>
#include <Client/Component/Heal.hh>
#include <Client/Component/Life.hh>
#include <Client/Component/Mob.hh>
#include <Client/Component/Petal.hh>
#include <Client/Component/Physical.hh>
#include <Client/Component/PlayerInfo.hh>
#include <Client/Component/Projectile.hh>
#include <Client/System/Interpolation.hh>
#include <Client/System/GameRenderer.hh>
#include <Shared/Entity.hh>
#include <Client/Util/Lerp.hh>

#include <Client/Ui/Container.hh>

namespace app
{
    class Simulation;
}

extern app::Simulation *g_Simulation;

namespace app
{
    class Simulation
    {
        system::Interpolation m_InterpolationSystem;
        system::GameRenderer m_RendererSystem;

        bool m_EntityTracker[MAX_ENTITY_COUNT];
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    bool m_##COMPONENT##Tracker[MAX_ENTITY_COUNT];
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY

#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)      \
    union COMPONENT##__UT                         \
    {                                             \
        component::COMPONENT d[MAX_ENTITY_COUNT]; \
        COMPONENT##__UT()                         \
        {                                         \
        }                                         \
        ~COMPONENT##__UT()                        \
        {                                         \
        }                                         \
    } m_##COMPONENT##Components;
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY

    public:
        float m_LastTick = 0;
        float m_TickTime = 0;
        class Renderer *m_Renderer;
        class Socket *m_Socket;
        Entity m_PlayerInfo = -1;
        bool m_HasHadPlayer = false;
        std::map <std::string, ui::Container *> m_UiElements{};

        Simulation(class Renderer *);

        float GetTime();
        void ReadBinary(uint8_t *);
        void ReadEntity(bc::BinaryCoder &);
        Entity CreateEntityWithId(Entity);
        void Remove(Entity);
        void TickRenderer();
        template <typename T>
        void ForEachEntity(T callback)
        {
            for (Entity i = 0; i < MAX_ENTITY_COUNT; i++)
                if (m_EntityTracker[i])
                    callback(i);
        }

        template <typename Component>
        Component &Get(Entity);

        template <typename Component>
        Component const &Get(Entity) const;

        template <typename Component>
        bool HasComponent(Entity) const;

        template <typename Component>
        Component &AddComponent(Entity);
    };
}
