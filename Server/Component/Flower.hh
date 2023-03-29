#pragma once

#include <cstdint>

#include <Shared/Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app
{
    class Simulation;
}

namespace app::component
{
    class Flower
    {
    private:
        uint8_t m_FaceFlags = 0;
        float m_EyeAngle = 0.0f;
        Simulation *m_Simulation;

    public:
        using Type = Flower;
        
        enum class Flags : uint8_t
        {
            Attack = 1,
            Defend = 2,
            Poison = 4,
            Dandelion = 8,
            Antennae = 16,
            Cutter = 32
        };

        uint64_t m_State = 0;
        Entity m_Parent;

        Flower(Entity, Simulation *);
        ~Flower();

        uint8_t FaceFlags() const;
        float EyeAngle() const;
        void FaceFlags(uint8_t);
        void EyeAngle(float);

        void Reset();

        // clone becuase the struct is small
        static void Write(bc::BinaryCoder &, Flower, bool);
    };
}
