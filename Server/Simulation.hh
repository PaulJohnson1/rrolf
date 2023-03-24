#pragma once

#include <cstdint>
#include <vector>
#include <queue>
#include <functional>
#include <optional>

#include <Server/Component/Physical.hh>
#include <Server/Component/Life.hh>
#include <Server/Component/Flower.hh>
#include <Server/Component/Render.hh>
#include <Server/System/Velocity.hh>
#include <Server/System/CollisionDetector.hh>
#include <Server/System/CollisionResolver.hh>
#include <Server/Entity.hh>
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
        system::Velocity m_Velocity;

        std::queue<Entity> m_AvailableIds{};
        bool m_EntityTracker[MAX_ENTITY_COUNT] = {};
        std::optional<component::Physical> m_PhysicalComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Life> m_LifeComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Render> m_RenderComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Flower> m_FlowerComponents[MAX_ENTITY_COUNT] = {};

    public:
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
