#pragma once

#include <cstdint>
#include <vector>
#include <queue>
#include <functional>
#include <optional>

#include <Component/Physics.hh>
#include <Component/Life.hh>
#include <Component/Position.hh>
#include <Component/Flower.hh>
#include <System/Velocity.hh>
#include <System/CollisionDetector.hh>
#include <System/CollisionResolver.hh>
#include <Entity.hh>
#include <SpatialHash.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Server;
    class Client;
    class Camera;

    class Simulation
    {
        system::Velocity m_Velocity;
        system::CollisionDetector m_CollisionDetector;
        // system::CollisionResolver m_CollisionResolver;
        std::queue<Entity> m_AvailableIds{};
        bool m_EntityTracker[MAX_ENTITY_COUNT] = {};
        std::optional<component::Physics> m_PhysicsComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Life> m_LifeComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Position> m_PositionComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Flower> m_FlowerComponents[MAX_ENTITY_COUNT] = {};

    public:
        Server &m_Server;

        Simulation(Server &);

        void Remove(Entity);
        void WriteUpdate(bc::BinaryCoder &, Camera &);
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
