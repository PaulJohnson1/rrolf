#pragma once

namespace app
{
    class Vector
    {
    public:
        float m_X;
        float m_Y;
        Vector() = default;
        Vector(float, float);
        void Set(float, float);
        Vector &operator=(Vector);
        Vector &operator+=(Vector);
        Vector &operator-=(Vector);
        Vector &operator*=(float);
        Vector operator+(Vector);
        Vector operator-(Vector);
        Vector operator*(float);
        bool operator>(float);
        bool operator<(float);
        float Magnitude();
        Vector &Normalize();
    };
}
