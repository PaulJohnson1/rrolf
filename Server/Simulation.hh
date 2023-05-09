#pragma once

#include <cstdint>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>

#include <Server/Component/Ai.hh>
#include <Server/Component/ArenaInfo.hh>
#include <Server/Component/Basic.hh>
#include <Server/Component/Drop.hh>
#include <Server/Component/Flower.hh>
#include <Server/Component/Life.hh>
#include <Server/Component/Heal.hh>
#include <Server/Component/Mob.hh>
#include <Server/Component/Petal.hh>
#include <Server/Component/Physical.hh>
#include <Server/Component/PlayerInfo.hh>
#include <Server/Component/Projectile.hh>
#include <Server/System/CollisionDetector.hh>
#include <Server/System/CollisionResolver.hh>
#include <Server/System/Damage.hh>
#include <Server/System/DropCollector.hh>
#include <Server/System/MapBoundaries.hh>
#include <Server/System/MobAi.hh>
#include <Server/System/PetalBehavior.hh>
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
        system::DropCollector m_DropCollector;
        system::MapBoundaries m_MapBoundaries;
        system::Velocity m_Velocity;
        system::MobAi m_MobAi;
        system::PetalBehavior m_PetalBehavior;

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

        std::vector<Entity> FindNearBy(Entity, float);
        std::vector<Entity> FindEntitiesInView(component::PlayerInfo &);
        Entity Create();

        bool HasEntity(Entity);
        void WriteEntity(bc::BinaryCoder &, Entity, bool);
        void ResetEntity(Entity);
        template <bool Animation>
        void RequestDeletion(Entity id)
        {
            if constexpr (Animation)
            {
                component::Physical &physical = Get<component::Physical>(id);
                if (physical.DeletionTick() == 0)
                {
                    physical.DeletionTick(1);
                }
            }
            else
                if (std::find(m_PendingDeletions.begin(), m_PendingDeletions.end(), id) == m_PendingDeletions.end())
                    m_PendingDeletions.push_back(id);
        }
    };
}
