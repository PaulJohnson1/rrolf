#pragma once

#include <cstdint>

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
#include <Shared/Entity.hh>

namespace app
{
    class Simulation
    {

        bool m_EntityTracker[MAX_ENTITY_COUNT] = {};
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    bool m_##COMPONENT##Tracker[MAX_ENTITY_COUNT] = {};
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
        Entity m_PlayerInfo = NULL_ENTITY;

        Simulation();
        Simulation(Simulation const &) = delete;
        Simulation(Simulation &&) = delete;
        Simulation &operator=(Simulation const &) = delete;
        Simulation &operator=(Simulation &&) = delete;
        void ReadEntity(bc::BinaryCoder &);
        Entity CreateEntityWithId(Entity);
        void Remove(Entity);
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
