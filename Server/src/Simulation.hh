#pragma once

#include <cstdint>
#include <vector>
#include <queue>
#include <functional>
#include <optional>

#include <Component/Physics.hh>
#include <Component/Life.hh>
#include <Component/Position.hh>
#include <System/Velocity.hh>
#include <System/CollisionDetector.hh>
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

    constexpr Entity MAX_ENTITY_COUNT = (Entity)-1;

    class Simulation
    {
        system::Velocity m_Velocity;
        system::CollisionDetector m_CollisionDetector;
        std::queue<Entity> m_AvailableIds{};
        bool m_EntityTracker[MAX_ENTITY_COUNT] = {};
        std::optional<component::Physics> m_PhysicsComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Life> m_LifeComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Position> m_PositionComponents[MAX_ENTITY_COUNT] = {};

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

        std::vector<uint16_t> FindEntitiesInView(Camera &camera);
        uint16_t Create();

        void WriteEntity(bc::BinaryCoder &, Entity, bool);
        void ResetEntity(Entity);
    };
}
