#pragma once

#include <cstdint>

#include <Entity.hh>

namespace bc
{
    class BinaryCoder;
}

namespace app::component
{
    class Flower
    {
    public:
        enum class Flags
        {
            Attack = 1,
            Defend = 2,
            Poison = 4,
            Dandelion = 8,
            Antennae = 16,
            Cutter = 32
        };
        
    private:
        Flags m_FaceFlags = 0;
        float m_EyeAngle = 0.0f;

    public:
        using Type = Flower;

        uint64_t m_State = 0;
        Entity m_Parent;

        Flower(Entity);

        Flags FaceFlags();
        float EyeAngle();
        void FaceFlags(Flags);
        void EyeAngle(float);

        void Reset();

        // clone becuase the struct is small
        static void Write(bc::BinaryCoder &, Flower, bool);
    };
}
