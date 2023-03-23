#include <Simulation.hh>

#include <cmath>
#include <iostream>
#include <vector>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Renderer.hh>

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

    DEFINE_COMPONENT_GETTER(Flower);
    DEFINE_COMPONENT_GETTER(Life);
    DEFINE_COMPONENT_GETTER(Physical);
    DEFINE_COMPONENT_GETTER(Render);
#undef DEFINE_COMPONENT_GETTER

    Simulation::Simulation()
        : m_InterpolationSystem(*this),
          m_RendererSystem(*this)
    {
        std::fill(m_EntityTracker, m_EntityTracker + MAX_ENTITY_COUNT, false);
    }

    void Simulation::ReadBinary(uint8_t *data)
    {
        bc::BinaryCoder coder{data};
        uint8_t type = coder.Read<bc::Uint8>();

        if (type == 0)
        {
            m_Camera.m_FovDestination = coder.Read<bc::Float32>();
            m_Camera.m_XDestination = coder.Read<bc::Float32>();
            m_Camera.m_YDestination = coder.Read<bc::Float32>();

            Entity deletedEntityCount = coder.Read<bc::VarUint>();
            for (Entity i = 0; i < deletedEntityCount; i++)
                RemoveEntity(coder.Read<bc::VarUint>());

            Entity updatedEntityCount = coder.Read<bc::VarUint>();
            for (Entity i = 0; i < updatedEntityCount; i++)
                ReadEntity(coder);
        }
    }

    void Simulation::RemoveEntity(Entity id)
    {
        m_EntityTracker[id] = false;
        GetOptional<component::Flower>(id).reset();
        GetOptional<component::Life>(id).reset();
        GetOptional<component::Physical>(id).reset();
        GetOptional<component::Render>(id).reset();
    }


    void Simulation::TickRenderer(Renderer *ctx)
    {
        m_InterpolationSystem.Tick();
        m_RendererSystem.Tick(ctx);

        m_InterpolationSystem.PostTick();
        m_RendererSystem.PostTick();
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
                AddComponent<component::Physical>(id);
            if (componentFlags & 2)
                AddComponent<component::Life>(id);
            if (componentFlags & 4)
                AddComponent<component::Flower>(id);
            if (componentFlags & 8)
                AddComponent<component::Render>(id);
        }

        if (componentFlags & 1)
            Get<component::Physical>(id).UpdateFromBinary(coder);
        if (componentFlags & 2)
            Get<component::Life>(id).UpdateFromBinary(coder);
        if (componentFlags & 4)
            Get<component::Flower>(id).UpdateFromBinary(coder);
        if (componentFlags & 8)
            Get<component::Render>(id).UpdateFromBinary(coder);
    }

    Entity Simulation::CreateEntityWithId(Entity id)
    {
        m_EntityTracker[id] = true;
        return id;
    }
}
