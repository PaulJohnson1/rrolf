#pragma once

#include <cstdint>
#include <optional>

#include <Component/Physics.hh>
#include <Component/Life.hh>
#include <Component/Position.hh>
#include <Component/Flower.hh>
#include <System/Interpolation.hh>
#include <Entity.hh>

namespace app
{
    class Renderer;

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
        bool m_EntityTracker[MAX_ENTITY_COUNT] = {};
        std::optional<component::Position> m_PositionComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Physics> m_PhysicsComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Life> m_LifeComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Flower> m_FlowerComponents[MAX_ENTITY_COUNT] = {};

        system::Interpolation m_InterpolationSystem;
    public:
        Camera m_Camera{};

        Simulation();
        Simulation(Simulation &&) = delete;
        Simulation(Simulation const &) = delete;
        Simulation &operator=(Simulation &&) = delete;
        Simulation &operator=(Simulation const &) = delete;

        void ReadBinary(uint8_t *);
        void ReadEntity(bc::BinaryCoder &);
        Entity CreateEntityWithId(Entity);
        void RemoveEntity(Entity);
        void TickRenderer(Renderer *);
        // use if you want bound checking
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
