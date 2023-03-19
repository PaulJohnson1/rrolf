#pragma once

class Vector
{
public:
    float m_X;
    float m_Y;
    Vector() = default;
    Vector(float, float);
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
