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
        float m_Radius = 1.0f;
        float m_Friction = 0.9f;
        float m_Mass = 1.0f;

    public:
        Entity m_Parent;
        uint32_t m_QueryId = 0;
        std::vector<Entity> m_Collisions{};

        Vector m_Velocity{0, 0};
        Vector m_Acceleration{0, 0};

        using Type = Physics;

        uint64_t m_State = 0;
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
