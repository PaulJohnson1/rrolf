#pragma once

#include <cstdint>
#include <optional>

#include <Component/Physics.hh>
#include <Component/Life.hh>
#include <Component/Position.hh>
#include <Entity.hh>

namespace app
{
    class Simulation
    {
        bool m_EntityTracker[MAX_ENTITY_COUNT] = {};
        std::optional<component::Position> m_PositionComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Physics> m_PhysicsComponents[MAX_ENTITY_COUNT] = {};
        std::optional<component::Life> m_LifeComponents[MAX_ENTITY_COUNT] = {};

    public:
        void ReadBinary(uint8_t *);
        void ReadEntity(bc::BinaryCoder &);
        Entity CreateEntityWithId(Entity);

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
