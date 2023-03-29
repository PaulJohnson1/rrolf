#pragma once

#include <cstdint>
#include <vector>
#include <queue>
#include <functional>

#define FOR_EACH_COMPONENT              \
    RROLF_COMPONENT_ENTRY(Ai, 0)        \
    RROLF_COMPONENT_ENTRY(ArenaInfo, 1) \
    RROLF_COMPONENT_ENTRY(Basic, 2)     \
    RROLF_COMPONENT_ENTRY(Flower, 3)    \
    RROLF_COMPONENT_ENTRY(Life, 4)      \
    RROLF_COMPONENT_ENTRY(Physical, 5)  \
    RROLF_COMPONENT_ENTRY(Mob, 6)

#include <Server/Component/Ai.hh>
#include <Server/Component/ArenaInfo.hh>
#include <Server/Component/Basic.hh>
#include <Server/Component/Flower.hh>
#include <Server/Component/Life.hh>
#include <Server/Component/Mob.hh>
#include <Server/Component/Physical.hh>

#include <Server/System/CollisionDetector.hh>
#include <Server/System/CollisionResolver.hh>
#include <Server/System/Damage.hh>
#include <Server/System/MapBoundaries.hh>
#include <Server/System/MobAi.hh>
#include <Server/System/Velocity.hh>

#include <Shared/Entity.hh>
#include <Server/SpatialHash.hh>

namespace app
{
    class Server;
    class Client;
    class Camera;

    class Simulation
    {
        system::CollisionDetector m_CollisionDetector;
        system::CollisionResolver m_CollisionResolver;
        system::Damage m_Damage;
        system::MapBoundaries m_MapBoundaries;
        system::Velocity m_Velocity;
        system::MobAi m_MobAi;

        std::queue<Entity> m_AvailableIds{};
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
        Entity m_Arena;
        Server &m_Server;

        Simulation(Server &);

        void Remove(Entity);
        void WriteUpdate(class bc::BinaryCoder &, Camera &);
        void Tick();

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
        Component &AddComponent(Entity);

        template <typename Component>
        bool HasComponent(Entity) const;

        std::vector<Entity> FindEntitiesInView(Camera &camera);
        Entity Create();

        void WriteEntity(bc::BinaryCoder &, Entity, bool);
        void ResetEntity(Entity);
    };
}
