#pragma once

#include <cstdint>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>

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
    RROLF_COMPONENT_ENTRY(Drop, 9)

#include <Server/Component/Ai.hh>
#include <Server/Component/ArenaInfo.hh>
#include <Server/Component/Basic.hh>
#include <Server/Component/Drop.hh>
#include <Server/Component/Flower.hh>
#include <Server/Component/Life.hh>
#include <Server/Component/Mob.hh>
#include <Server/Component/Petal.hh>
#include <Server/Component/Physical.hh>
#include <Server/Component/PlayerInfo.hh>
#include <Server/System/CollisionDetector.hh>
#include <Server/System/CollisionResolver.hh>
#include <Server/System/Damage.hh>
#include <Server/System/MapBoundaries.hh>
#include <Server/System/MobAi.hh>
#include <Server/System/Petal.hh>
#include <Server/System/Velocity.hh>
#include <Shared/Entity.hh>
#include <Server/SpatialHash.hh>

namespace app
{
    class Server;
    class Client;

    class Simulation
    {
        std::vector<Entity> m_PendingDeletions;
        system::CollisionDetector m_CollisionDetector;
        system::CollisionResolver m_CollisionResolver;
        system::Damage m_Damage;
        system::MapBoundaries m_MapBoundaries;
        system::Velocity m_Velocity;
        system::MobAi m_MobAi;
        system::Petal m_Petal;

        std::mutex m_Mutex;

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

        // IMPORTANT: PUSH TO m_PendingDeletions INSTEAD OF DIRECTLY CALLING THIS FUNCTION
        void Remove(Entity);

    public:
        Entity m_Arena;
        Server &m_Server;
        uint64_t m_TickCount = 0;

        Simulation(Server &);

        void BroadcastUpdates();
        void WriteUpdate(class bc::BinaryCoder &, component::PlayerInfo &);
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

        std::vector<Entity> FindEntitiesInView(component::PlayerInfo &playerInfo);
        Entity Create();

        bool HasEntity(Entity);
        void WriteEntity(bc::BinaryCoder &, Entity, bool);
        void ResetEntity(Entity);
        void RequestDeletion(Entity);
    };
}
