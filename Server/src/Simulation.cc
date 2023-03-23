#include <Simulation.hh>

#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Entity.hh>
#include <Server.hh>

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

    Simulation::Simulation(Server &s)
        : m_Server(s),
          m_CollisionDetector(*this),
          m_CollisionResolver(*this),
          m_Velocity(*this)
    {
        for (Entity i = 0; i < MAX_ENTITY_COUNT; i++)
            m_AvailableIds.push(i);
    }

    void Simulation::Tick()
    {
        ForEachEntity([&](Entity id)
                      { ResetEntity(id); });
        m_Velocity.Tick();
        m_CollisionDetector.Tick();
        m_CollisionResolver.Tick();

        m_Velocity.PostTick();
        m_CollisionDetector.PostTick();
        m_CollisionResolver.PostTick();
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
            componentFlags |= GetOptional<component::Physical>(id).has_value() << 0;
            componentFlags |= GetOptional<component::Life>(id).has_value() << 1;
            componentFlags |= GetOptional<component::Flower>(id).has_value() << 2;
            componentFlags |= GetOptional<component::Render>(id).has_value() << 3;
        }
        else
        {
            componentFlags |= (GetOptional<component::Physical>(id) && Get<component::Physical>(id).m_State != 0) << 0;
            componentFlags |= (GetOptional<component::Life>(id) && Get<component::Life>(id).m_State != 0) << 1;
            componentFlags |= (GetOptional<component::Flower>(id) && Get<component::Flower>(id).m_State != 0) << 2;
            componentFlags |= (GetOptional<component::Render>(id) && Get<component::Flower>(id).m_State != 0) << 3;
        }

        coder.Write<bc::VarUint>(id);
        coder.Write<bc::VarUint>(componentFlags);

        if (componentFlags & 1)
            coder.Write<component::Physical>(Get<component::Physical>(id), isCreation);
        if (componentFlags & 2)
            coder.Write<component::Life>(Get<component::Life>(id), isCreation);
        if (componentFlags & 4)
            coder.Write<component::Flower>(Get<component::Flower>(id), isCreation);
        if (componentFlags & 8)
            coder.Write<component::Render>(Get<component::Render>(id), isCreation);
    }

    void Simulation::ResetEntity(Entity id)
    {
        if (GetOptional<component::Physical>(id))
            Get<component::Physical>(id).Reset();
        if (GetOptional<component::Life>(id))
            Get<component::Life>(id).Reset();
        if (GetOptional<component::Flower>(id))
            Get<component::Flower>(id).Reset();
        if (GetOptional<component::Render>(id))
            Get<component::Render>(id).Reset();
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
        m_PhysicalComponents[id].reset();
        m_EntityTracker[id] = false;
    }
}
