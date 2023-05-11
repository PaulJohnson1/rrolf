#include <Client/Simulation.hh>

#include <iostream>
#include <vector>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

namespace app
{
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)                                           \
    template <>                                                                        \
    component::COMPONENT &Simulation::Get<component::COMPONENT>(Entity id)             \
    {                                                                                  \
        RROLF_ASSERT(m_EntityTracker[id], "entity does not exist");                    \
        RROLF_ASSERT(m_##COMPONENT##Tracker[id], "component does not exist");          \
        return m_##COMPONENT##Components.d[id];                                        \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    component::COMPONENT const &Simulation::Get<component::COMPONENT>(Entity id) const \
    {                                                                                  \
        RROLF_ASSERT(m_EntityTracker[id], "entity does not exist");                    \
        RROLF_ASSERT(m_##COMPONENT##Tracker[id], "component does not exist");          \
        return m_##COMPONENT##Components.d[id];                                        \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    bool Simulation::HasComponent<component::COMPONENT>(Entity id) const               \
    {                                                                                  \
        RROLF_ASSERT(m_EntityTracker[id], "entity does not exist");                    \
        return m_##COMPONENT##Tracker[id];                                             \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    component::COMPONENT &Simulation::AddComponent<component::COMPONENT>(Entity id)    \
    {                                                                                  \
        RROLF_ASSERT(m_EntityTracker[id], "entity does not exist");                    \
        RROLF_ASSERT(!m_##COMPONENT##Tracker[id], "component already exists");         \
        m_##COMPONENT##Tracker[id] = true;                                             \
        new (&m_##COMPONENT##Components.d[id]) component::COMPONENT(id, this);         \
        return Get<component::COMPONENT>(id);                                          \
    }

    FOR_EACH_COMPONENT;

#undef RROLF_COMPONENT_ENTRY

    Simulation::Simulation()
    {
        std::fill(m_EntityTracker, m_EntityTracker + MAX_ENTITY_COUNT, false);
    }

    void Simulation::Remove(Entity id)
    {
        RROLF_ASSERT(m_EntityTracker[id], "cannot remove nonexistant entity");
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)    \
    {                                           \
        using T = component::COMPONENT;         \
        if (HasComponent<T>(id))                \
        {                                       \
            T &comp = Get<T>(id);               \
            m_##COMPONENT##Tracker[id] = false; \
            comp.~T();                          \
        }                                       \
    }
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        m_EntityTracker[id] = false;
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