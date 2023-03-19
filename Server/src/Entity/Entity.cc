#include <Entity/Entity.hh>
#include <Entity/Component/Physics.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

Entity::Entity(uint16_t id)
{
    m_Id = id;
    m_Position.emplace(Position{{0.0f, 0.0f}, 0.0f});
    m_Physics.emplace(Physics{0.0f});
}

void Entity::tick()
{
    if (m_Physics && m_Position)
    {
        m_Velocity *= m_Physics.value().Friction();
        m_Velocity += m_Acceleration;
        m_Position.value() += m_Velocity;
    }
}

void Entity::Write(bc::BinaryCoder &coder, Type const &entity)
{
    coder.Write<bc::VarUint>(entity.m_Id);
    uint32_t componentFlags = 0;
    if ((bool)entity.m_Position && entity.m_Position->m_State != 0)
        componentFlags |= 1;
    if ((bool)entity.m_Physics && entity.m_Physics->m_State != 0)
        componentFlags |= 2;

    coder.Write<bc::VarUint>(componentFlags);

    if (componentFlags & 1)
        coder.Write<Position>(*entity.m_Position);
    if (componentFlags & 2)
        coder.Write<Physics>(entity.m_Physics.value());
}
