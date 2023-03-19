#pragma once

#include <cstdint>
#include <vector>

#include <Entity.hh>
#include <Vector.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Physics
    {
        float m_Radius;
        float m_Friction = 0.9;
        float m_Mass = 1;

    public:
        Entity m_Parent;
        uint32_t m_QueryId = 0;
        std::vector<Entity> m_Collisions{};

        Vector m_Velocity;
        Vector m_Acceleration;

        using Type = Physics;

        uint16_t m_State;
        Physics(Entity);
        float Radius() const;
        float Friction() const;
        float Mass() const;
        void Radius(float);
        void Friction(float);
        void Mass(float);

        void Reset();

        static void Write(bc::BinaryCoder &coder, Type, bool isCreation);
    };
}
