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

        static Vector FromPolar(float r, float theta);

        void Set(float, float);
        Vector &operator=(Vector);
        Vector &operator+=(Vector);
        Vector &operator-=(Vector);
        Vector &operator*=(float);
        Vector operator+(Vector);
        Vector operator-(Vector);
        Vector operator*(float);
        float operator*(Vector);
        bool operator>(float);
        bool operator<(float);
        float Magnitude();
        float Theta();
        void Theta(float);
        Vector &Magnitude(float);
        Vector &Normalize();
    };
}
