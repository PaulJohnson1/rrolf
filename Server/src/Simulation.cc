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

    DEFINE_COMPONENT_GETTER(Position);
    DEFINE_COMPONENT_GETTER(Physics);
    DEFINE_COMPONENT_GETTER(Life);

#undef DEFINE_COMPONENT_GETTER


    Simulation::Simulation(Server &s)
        : m_Server(s),
          m_Velocity(*this),
          m_CollisionDetector(*this)
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

        m_CollisionDetector.m_SpatialHash.Clear();
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
        /*
            00          // deletion count
            01          // update count

            01          // creation type
            00          // entity id
            03          // component flags

            07          // position state
            00 00 f4 42 // position x value
            00 20 9a 44 // position y value
            b5 1f 92 3f // angle

            01          // physics state
            c8 d5 ea 4c // physics radius
        */

        std::vector<Entity> entitiesInView = FindEntitiesInView(camera);
        std::vector<Entity> deletedEntities;

        std::copy_if(
            camera.m_EntitiesInView.begin(),
            camera.m_EntitiesInView.end(),
            std::back_inserter(deletedEntities),
            [&](Entity id)
            {
                return std::find(entitiesInView.begin(), entitiesInView.end(), id) == entitiesInView.end();
            });

        std::for_each(deletedEntities.begin(), deletedEntities.end(), [&](Entity id)
                      { camera.m_EntitiesInView.erase(std::remove(camera.m_EntitiesInView.begin(), camera.m_EntitiesInView.end(), id),
                                                      camera.m_EntitiesInView.end()); });

        coder.Write<bc::VarUint>(deletedEntities.size());
        std::for_each(deletedEntities.begin(), deletedEntities.end(), [&](Entity id)
                      { coder.Write<bc::VarUint>(id); });

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
            componentFlags |= GetOptional<component::Position>(id).has_value() << 0;
            componentFlags |= GetOptional<component::Physics>(id).has_value() << 1;
            componentFlags |= GetOptional<component::Life>(id).has_value() << 2;
        }
        else
        {
            componentFlags |= (GetOptional<component::Position>(id) && Get<component::Position>(id).m_State != 0) << 0;
            componentFlags |= (GetOptional<component::Physics>(id) && Get<component::Physics>(id).m_State != 0) << 1;
            componentFlags |= (GetOptional<component::Life>(id) && Get<component::Life>(id).m_State != 0) << 2;
        }

        coder.Write<bc::VarUint>(id);
        coder.Write<bc::VarUint>(componentFlags);

        if (componentFlags & 1)
            coder.Write<component::Position>(Get<component::Position>(id), isCreation);
        if (componentFlags & 2)
            coder.Write<component::Physics>(Get<component::Physics>(id), isCreation);
        if (componentFlags & 4)
            coder.Write<component::Life>(Get<component::Life>(id), isCreation);
    }

    void Simulation::ResetEntity(Entity id)
    {
        if (GetOptional<component::Position>(id))
            Get<component::Position>(id).Reset();
        if (GetOptional<component::Physics>(id))
            Get<component::Physics>(id).Reset();
        if (GetOptional<component::Life>(id))
            Get<component::Life>(id).Reset();
    }

    Entity Simulation::Create()
    {
        assert(m_AvailableIds.size());
        Entity id = m_AvailableIds.front();
        m_AvailableIds.pop();
        m_EntityTracker[id] = true;
        return id;
    }
    void Simulation::Remove(Entity id)
    {
        assert(m_EntityTracker[id]);
        m_AvailableIds.push(id);
        m_PhysicsComponents[id].reset();
        m_EntityTracker[id] = false;
    }
}
