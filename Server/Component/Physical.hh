#pragma once

#include <cstdint>
#include <vector>

#include <Server/Entity.hh>
#include <Server/Vector.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Physical
    {
        float m_Radius = 1.0f;
        float m_X = 0.0f;
        float m_Y = 0.0f;
        float m_Angle = 0.0f;

    public:
        Entity m_Parent;
        uint32_t m_QueryId = 0;
        float m_Mass = 1.0f;
        float m_Friction = 0.9f;
        float m_Restitution = 1.0f;
        uint64_t m_State = 0;

        Vector m_Velocity{0, 0};
        Vector m_Acceleration{0, 0};
        std::vector<Entity> m_Collisions{};

        using Type = Physical;

        Physical(Entity);

        float Radius() const;
        float Friction() const;
        float X() const;
        float Y() const;
        float Angle() const;
        void Radius(float);
        void Friction(float);
        void X(float);
        void Y(float);
        void Angle(float);

        void Reset();

        static void Write(bc::BinaryCoder &coder, Type const &, bool isCreation);
    };
}
