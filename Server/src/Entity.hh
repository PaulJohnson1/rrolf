#pragma once

#include <cstdint>
#include <optional>

#include <Vector.hh>
#include <Component/Position.hh>
#include <Component/Physics.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Entity
    {
    public:
        using Type = Entity;

        uint16_t m_Id;
        uint32_t m_QueryId = 0;
        std::optional<component::Physics> m_Physics;
        std::optional<component::Position> m_Position;

        Entity(uint16_t);

        void ResetState();

        static void Write(bc::BinaryCoder &, Entity const &, bool);
    };
}
