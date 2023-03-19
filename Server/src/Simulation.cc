#include <Simulation.hh>

#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Entity/Entity.hh>
#include <Server.hh>

Simulation::Simulation(Server &s)
    : m_Server(s)
{
}
void Simulation::Tick()
{
}

void Simulation::ForEachEntity(std::function<void(Entity &)> callback)
{
    for (uint16_t i = 0; i < MAX_ENTITY_COUNT; i++)
        if (m_Entities[i] != nullptr)
            callback(*m_Entities[i]);
}

std::vector<uint16_t> Simulation::FindEntitiesInView(Camera &camera)
{
    std::vector<uint16_t> entityIds{};

    ForEachEntity([&](Entity &entity)
                  {
        // TODO: only send entities in fov
        entityIds.push_back(entity.m_Id); });

    return entityIds;
}

void Simulation::WriteUpdate(bc::BinaryCoder &coder, Camera &camera)
{
    std::vector<uint16_t> entitiesInView = FindEntitiesInView(camera);
    std::vector<uint16_t> deletedEntities;

    for (uint16_t i = 0; i < camera.m_EntitiesInView.size(); i++)
    {
        uint16_t id = camera.m_EntitiesInView[i];
        // id is not in the entities the client should view
        if (std::find(entitiesInView.begin(), entitiesInView.end(), id) == entitiesInView.end())
        {
            deletedEntities.push_back(id);
            // remove id from the camera's view after writing deletion so it does not get deleted twice
            camera.m_EntitiesInView.erase(std::find(camera.m_EntitiesInView.begin(), camera.m_EntitiesInView.end(), id));
        }
    }
    
    coder.Write<bc::VarUint>(deletedEntities.size());
    for (uint16_t id : deletedEntities)
        coder.Write<bc::VarUint>(id);

    coder.Write<bc::VarUint>(entitiesInView.size());
    for (uint16_t i = 0; i < entitiesInView.size(); i++)
    {
        uint16_t id = entitiesInView[i];

        if (std::find(camera.m_EntitiesInView.begin(), camera.m_EntitiesInView.end(), id) == camera.m_EntitiesInView.end())
            coder.Write<bc::Uint8>(1);
        else
            coder.Write<bc::Uint8>(0);

        coder.Write<Entity>(GetEntity(id));
    }
}

Entity &Simulation::GetEntity(uint16_t id)
{
    assert(m_Entities[id] != nullptr);

    return *m_Entities[id];
}

Entity &Simulation::Create()
{
    for (uint16_t i = 0; i < MAX_ENTITY_COUNT; i++)
        if (m_Entities[i] == nullptr)
        {
            m_Entities[i] = new Entity{i};
            return *m_Entities[i];
        }

    assert(false); // ran out of entity ids
}
void Simulation::Remove(Entity *e)
{
    m_Entities[e->m_Id] = nullptr;
    delete e;
}