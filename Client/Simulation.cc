#include <Client/Simulation.hh>

#include <cmath>
#include <iostream>
#include <vector>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Renderer.hh>

namespace app
{
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)                                                                  \
    template <>                                                                                               \
    component::COMPONENT &Simulation::Get<component::COMPONENT>(Entity id)                                    \
    {                                                                                                         \
        return *m_##COMPONENT##Components[id];                                                                \
    }                                                                                                         \
    template <>                                                                                               \
    component::COMPONENT const &Simulation::Get<component::COMPONENT>(Entity id) const                        \
    {                                                                                                         \
        return *m_##COMPONENT##Components[id];                                                                \
    }                                                                                                         \
    template <>                                                                                               \
    std::optional<component::COMPONENT> &Simulation::GetOptional<component::COMPONENT>(Entity id)             \
    {                                                                                                         \
        return m_##COMPONENT##Components[id];                                                                 \
    }                                                                                                         \
    template <>                                                                                               \
    std::optional<component::COMPONENT> const &Simulation::GetOptional<component::COMPONENT>(Entity id) const \
    {                                                                                                         \
        return m_##COMPONENT##Components[id];                                                                 \
    }                                                                                                         \
    template <>                                                                                               \
    component::COMPONENT &Simulation::AddComponent(Entity id)                                                 \
    {                                                                                                         \
        m_##COMPONENT##Components[id].emplace(id);                                                            \
        return Get<component::COMPONENT>(id);                                                                 \
    }

    FOR_EACH_COMPONENT;

#undef RROLF_COMPONENT_ENTRY

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
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    GetOptional<component::COMPONENT>(id).reset();
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
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
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    if (componentFlags & (1 << ID))          \
        AddComponent<component::COMPONENT>(id);
            FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        }

#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    if (componentFlags & (1 << ID))          \
        Get<component::COMPONENT>(id).UpdateFromBinary(coder);
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
    }

    Entity Simulation::CreateEntityWithId(Entity id)
    {
        m_EntityTracker[id] = true;
        return id;
    }
}
