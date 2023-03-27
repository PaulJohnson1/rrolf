#include <Server/Simulation.hh>

#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Server/Entity.hh>
#include <Server/Server.hh>

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

    Simulation::Simulation(Server &s)
        : m_Server(s),
          m_CollisionDetector(*this),
          m_CollisionResolver(*this),
          m_Velocity(*this),
          m_MapBoundaries(*this)
    {
        for (Entity i = 0; i < MAX_ENTITY_COUNT; i++)
        {
            m_AvailableIds.push(i);
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    m_##COMPONENT##Components[i].reset();
            FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        }

        m_Arena = Create();
        AddComponent<component::ArenaInfo>(m_Arena);
        Get<component::ArenaInfo>(m_Arena).MapSize(1650.0f);
    }

    void Simulation::Tick()
    {
        ForEachEntity([&](Entity id)
                      { ResetEntity(id); });

        // order is critical
        m_Velocity.Tick();
        m_CollisionDetector.Tick();
        m_CollisionResolver.Tick();
        m_MapBoundaries.Tick();

        m_Velocity.PostTick();
        m_CollisionDetector.PostTick();
        m_CollisionResolver.PostTick();
        m_MapBoundaries.PostTick();
    }

    std::vector<Entity> Simulation::FindEntitiesInView(Camera &camera)
    {
        std::vector<Entity> entitiesInView;
        ForEachEntity([&](Entity const &entity)
                      {
        // TODO: only send entities in fov
        entitiesInView.push_back(entity); });
        return entitiesInView;
    }

    void Simulation::WriteUpdate(bc::BinaryCoder &coder, Camera &camera)
    {
        std::vector<Entity> entitiesInView = FindEntitiesInView(camera);
        std::vector<Entity> deletedEntities;

        for (Entity i = 0; i < camera.m_EntitiesInView.size(); i++)
        {
            Entity id = camera.m_EntitiesInView[i];
            // id is not in the entities the client should view
            if (std::find(entitiesInView.begin(), entitiesInView.end(), id) == entitiesInView.end())
            {
                deletedEntities.push_back(id);
                // remove id from the camera's view after writing deletion so it does not get deleted twice
                camera.m_EntitiesInView.erase(std::find(camera.m_EntitiesInView.begin(), camera.m_EntitiesInView.end(), id));
            }
        }

        coder.Write<bc::VarUint>(deletedEntities.size());
        for (Entity id : deletedEntities)
            coder.Write<bc::VarUint>(id);

        coder.Write<bc::VarUint>(entitiesInView.size());
        for (Entity id : entitiesInView)
        {
            bool isCreation = std::find(camera.m_EntitiesInView.begin(), camera.m_EntitiesInView.end(), id) == camera.m_EntitiesInView.end();
            if (isCreation)
                camera.m_EntitiesInView.push_back(id);

            WriteEntity(coder, id, isCreation);
        }
    }

    void Simulation::WriteEntity(bc::BinaryCoder &coder, Entity id, bool isCreation)
    {
        uint32_t componentFlags = 0;
        if (isCreation)
        {
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    componentFlags |= GetOptional<component::COMPONENT>(id).has_value() << ID;
            FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        }
        else
        {
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    componentFlags |= (GetOptional<component::COMPONENT>(id) && Get<component::COMPONENT>(id).m_State != 0) << ID;
            FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        }

        coder.Write<bc::VarUint>(id);
        coder.Write<bc::VarUint>(componentFlags);

#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    if (componentFlags & (1 << ID))          \
        coder.Write<component::COMPONENT>(Get<component::COMPONENT>(id), isCreation);
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
    }

    void Simulation::ResetEntity(Entity id)
    {
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)   \
    if (GetOptional<component::COMPONENT>(id)) \
        Get<component::COMPONENT>(id).Reset();
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
    }

    Entity Simulation::Create()
    {
        assert(m_AvailableIds.size());
        Entity id = m_AvailableIds.front();
        m_AvailableIds.pop();
        m_EntityTracker[id] = true;
        std::cout << "entity with id " << std::to_string(id) << " created\n";
        return id;
    }
    void Simulation::Remove(Entity id)
    {
        std::cout << "entity with id " << std::to_string(id) << " deleted\n";
        assert(m_EntityTracker[id]);
        m_AvailableIds.push(id);
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    m_##COMPONENT##Components[id].reset();
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        m_EntityTracker[id] = false;
    }
}
