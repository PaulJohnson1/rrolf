#pragma once

#include <cstdint>
#include <optional>

#include <Client/Component/ArenaInfo.hh>
#include <Client/Component/Physical.hh>
#include <Client/Component/Life.hh>
#include <Client/Component/Flower.hh>
#include <Client/Component/Render.hh>
#include <Client/System/Interpolation.hh>
#include <Client/System/Renderer.hh>
#include <Client/Entity.hh>

namespace app
{
    class Camera
    {
    public:
        float m_Fov = 1;
        float m_X = 0;
        float m_Y = 0;
        float m_FovDestination = 1;
        float m_XDestination = 0;
        float m_YDestination = 0;
    };

    class Simulation
    {
        system::Interpolation m_InterpolationSystem;
        system::Renderer m_RendererSystem;
        bool m_EntityTracker[MAX_ENTITY_COUNT] = {};
        std::optional<component::Physical> m_PhysicalComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Life> m_LifeComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Flower> m_FlowerComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Render> m_RenderComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::ArenaInfo> m_ArenaInfoComponents[MAX_ENTITY_COUNT] = {};

    public:
        Camera m_Camera{};

        Simulation();

        void ReadBinary(uint8_t *);
        void ReadEntity(bc::BinaryCoder &);
        Entity CreateEntityWithId(Entity);
        void RemoveEntity(Entity);
        void TickRenderer(class Renderer *);
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
        std::optional<Component> &GetOptional(Entity);
        template <typename Component>
        std::optional<Component> const &GetOptional(Entity) const;
        template <typename Component>
        Component &AddComponent(Entity);
    };
}
