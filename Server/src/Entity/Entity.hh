#pragma once

#include <cstdint>
#include <optional>

#include <Vector.hh>
#include <Entity/Component/Position.hh>
#include <Entity/Component/Physics.hh>

namespace bc
{
    class BinaryCoder;
}

class Entity
{
public:
    using Type = Entity;

    uint8_t m_QueryId = 0;
    uint16_t m_Id;
    std::optional<Physics> m_Physics;
    std::optional<Position> m_Position;
    Vector m_Velocity, m_Acceleration;

    Entity(uint16_t);

    void tick();

    static void Write(bc::BinaryCoder &, Entity const &);
};
