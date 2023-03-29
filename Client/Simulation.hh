#pragma once

#include <cstdint>
#include <optional>

#define FOR_EACH_COMPONENT              \
    RROLF_COMPONENT_ENTRY(ArenaInfo, 0) \
    RROLF_COMPONENT_ENTRY(Basic, 1)     \
    RROLF_COMPONENT_ENTRY(Flower, 2)    \
    RROLF_COMPONENT_ENTRY(Life, 3)      \
    RROLF_COMPONENT_ENTRY(Physical, 4)  \
    RROLF_COMPONENT_ENTRY(Render, 5)    \
    RROLF_COMPONENT_ENTRY(Mob, 6)

#include <Client/Component/ArenaInfo.hh>
#include <Client/Component/Basic.hh>
#include <Client/Component/Flower.hh>
#include <Client/Component/Life.hh>
#include <Client/Component/Mob.hh>
#include <Client/Component/Physical.hh>
#include <Client/Component/Render.hh>
#include <Client/System/Interpolation.hh>
#include <Client/System/Renderer.hh>
#include <Shared/Entity.hh>

namespace app
{
    class Camera
    {
    public:
        float m_Fov = 0.9f;
        float m_X = 0;
        float m_Y = 0;
        float m_FovDestination = 0.9f;
        float m_XDestination = 0;
        float m_YDestination = 0;
    };
    class Simulation
    {
        system::Interpolation m_InterpolationSystem;
        system::Renderer m_RendererSystem;
        bool m_EntityTracker[MAX_ENTITY_COUNT] = {};
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    std::optional<component::COMPONENT> m_##COMPONENT##Components[MAX_ENTITY_COUNT] = {};
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY

    public:
        Camera m_Camera{};
        float m_LastTick = 0;
        float m_TickTime = 0;

        Simulation();

        float GetTime(); 
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
