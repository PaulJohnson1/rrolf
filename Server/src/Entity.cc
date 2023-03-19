#include <Entity.hh>
#include <Component/Physics.hh>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app
{
    Entity::Entity(uint16_t id)
    {
        m_Id = id;
    }

    void Entity::Write(bc::BinaryCoder &coder, Type const &entity, bool isCreation)
    {
        uint32_t componentFlags = 0;
        if (isCreation)
            // not going about 128 so vu doesn't add another byte lol
            componentFlags = 0b11;
        else
        {
            if (entity.m_Position && entity.m_Position->m_State != 0)
                componentFlags |= 1;
            if (entity.m_Physics && entity.m_Physics->m_State != 0)
                componentFlags |= 2;
        }

        coder.Write<bc::VarUint>(entity.m_Id);
        coder.Write<bc::VarUint>(componentFlags);

        if (componentFlags & 1)
            coder.Write<component::Position>(*entity.m_Position, isCreation);
        if (componentFlags & 2)
            coder.Write<component::Physics>(*entity.m_Physics, isCreation);
    }

    void Entity::ResetState()
    {
        if (m_Position)
            m_Position->m_State = 0;
        if (m_Physics)
            m_Physics->m_State = 0;
    }
}
