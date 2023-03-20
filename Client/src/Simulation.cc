#include <Simulation.hh>

#include <vector>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

namespace app
{
#define DEFINE_COMPONENT_GETTER(NAME)                                                               \
    template <>                                                                                     \
    component::NAME &Simulation::Get<component::NAME>(Entity id)                                    \
    {                                                                                               \
        return *m_##NAME##Components[id];                                                           \
    }                                                                                               \
    template <>                                                                                     \
    component::NAME const &Simulation::Get<component::NAME>(Entity id) const                        \
    {                                                                                               \
        return *m_##NAME##Components[id];                                                           \
    }                                                                                               \
    template <>                                                                                     \
    std::optional<component::NAME> &Simulation::GetOptional<component::NAME>(Entity id)             \
    {                                                                                               \
        return m_##NAME##Components[id];                                                            \
    }                                                                                               \
    template <>                                                                                     \
    std::optional<component::NAME> const &Simulation::GetOptional<component::NAME>(Entity id) const \
    {                                                                                               \
        return m_##NAME##Components[id];                                                            \
    }                                                                                               \
    template <>                                                                                     \
    component::NAME &Simulation::AddComponent(Entity id)                                            \
    {                                                                                               \
        m_##NAME##Components[id].emplace(id);                                                       \
        return Get<component::NAME>(id);                                                            \
    }

    DEFINE_COMPONENT_GETTER(Position);
    DEFINE_COMPONENT_GETTER(Physics);
    DEFINE_COMPONENT_GETTER(Life);
#undef DEFINE_COMPONENT_GETTER

    void Simulation::ReadBinary(uint8_t *data)
    {
        bc::BinaryCoder coder{data};
        uint8_t type = coder.Read<bc::Uint8>();

        if (type == 0)
        {
            m_Camera.m_Fov = coder.Read<bc::Float32>();
            m_Camera.m_X = coder.Read<bc::Float32>();
            m_Camera.m_Y = coder.Read<bc::Float32>();

            std::vector<Entity> deletedEntities;
            Entity deletedEntityCount = coder.Read<bc::VarUint>();
            for (Entity i = 0; i < deletedEntityCount; i++)
                deletedEntities.push_back(coder.Read<bc::VarUint>());

            Entity updatedEntityCount = coder.Read<bc::VarUint>();
            for (Entity i = 0; i < updatedEntityCount; i++)
                ReadEntity(coder);
        }
    }

    void Simulation::ReadEntity(bc::BinaryCoder &coder)
    {
        Entity id = coder.Read<bc::VarUint>();
        uint32_t componentFlags = coder.Read<bc::VarUint>();
        bool isCreation = !m_EntityTracker[id];
        if (isCreation)
        {
            CreateEntityWithId(id);
            if (componentFlags & 1)
                AddComponent<component::Position>(id);
            if (componentFlags & 2)
                AddComponent<component::Physics>(id);
            if (componentFlags & 4)
                AddComponent<component::Life>(id);
        }

        if (componentFlags & 1)
            Get<component::Position>(id).UpdateFromBinary(coder);
        if (componentFlags & 2)
            Get<component::Physics>(id).UpdateFromBinary(coder);
        if (componentFlags & 4)
            Get<component::Life>(id).UpdateFromBinary(coder);
    }

    Entity Simulation::CreateEntityWithId(Entity id)
    {
        m_EntityTracker[id] = true;
        return id;
    }
}
