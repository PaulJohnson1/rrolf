#pragma once

#include <cstdint>
#include <vector>
#include <queue>
#include <functional>
#include <optional>

#define FOR_EACH_COMPONENT              \
    RROLF_COMPONENT_ENTRY(ArenaInfo, 0) \
    RROLF_COMPONENT_ENTRY(Basic, 1)     \
    RROLF_COMPONENT_ENTRY(Flower, 2)    \
    RROLF_COMPONENT_ENTRY(Life, 3)      \
    RROLF_COMPONENT_ENTRY(Physical, 4)  \
    RROLF_COMPONENT_ENTRY(Render, 5)    \
    RROLF_COMPONENT_ENTRY(Mob, 6)

#include <Server/Component/ArenaInfo.hh>
#include <Server/Component/Basic.hh>
#include <Server/Component/Flower.hh>
#include <Server/Component/Life.hh>
#include <Server/Component/Mob.hh>
#include <Server/Component/Physical.hh>
#include <Server/Component/Render.hh>
#include <Server/System/CollisionDetector.hh>
#include <Server/System/CollisionResolver.hh>
#include <Server/System/MapBoundaries.hh>
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
        system::MapBoundaries m_MapBoundaries;
        system::Velocity m_Velocity;

        std::queue<Entity> m_AvailableIds{};
        bool m_EntityTracker[MAX_ENTITY_COUNT] = {};
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    std::optional<component::COMPONENT> m_##COMPONENT##Components[MAX_ENTITY_COUNT] = {};
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY

    public:
        Entity m_Arena;
        Server &m_Server;

        Simulation(Server &);

        void Remove(Entity);
        void WriteUpdate(class bc::BinaryCoder &, Camera &);
        void Tick();
        // use if you want bound checking
        template <typename T>
        void ForEachEntity(T callback)
        {
            for (Entity i = 0; i < MAX_ENTITY_COUNT; i++)
                if (m_EntityTracker[i])
                    callback(i);
        }

        template <typename Component>
        Component &AddComponent(Entity);

        template <typename Component>
        Component &Get(Entity);
        template <typename Component>
        Component const &Get(Entity) const;
        template <typename Component>
        std::optional<Component> &GetOptional(Entity);
        template <typename Component>
        std::optional<Component> const &GetOptional(Entity) const;

        std::vector<Entity> FindEntitiesInView(Camera &camera);
        Entity Create();

        void WriteEntity(bc::BinaryCoder &, Entity, bool);
        void ResetEntity(Entity);
    };
}
