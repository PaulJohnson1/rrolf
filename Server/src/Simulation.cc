#include <Simulation.hh>

#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Entity.hh>
#include <Server.hh>

namespace app
{
    Simulation::Simulation(Server &s)
        : m_Server(s),
          m_Physics(*this)
    {
    }

    void Simulation::Tick()
    {
        m_Physics.Tick();
        ForEachEntity([&](Entity &entity)
                      { entity.ResetState(); });
    }

    std::vector<uint16_t> Simulation::FindEntitiesInView(Camera &camera)
    {
        std::vector<uint16_t> entitiesInView;
        ForEachEntity([&](Entity const &entity)
                      {
        // TODO: only send entities in fov
        entitiesInView.push_back(entity.m_Id); });
        return entitiesInView;
    }

    void Simulation::WriteUpdate(bc::BinaryCoder &coder, Camera &camera)
    {
        std::vector<uint16_t> entitiesInView = FindEntitiesInView(camera);
        std::vector<uint16_t> deletedEntities;

        std::copy_if(
            camera.m_EntitiesInView.begin(),
            camera.m_EntitiesInView.end(),
            std::back_inserter(deletedEntities),
            [&](uint16_t id)
            {
                return std::find(entitiesInView.begin(), entitiesInView.end(), id) == entitiesInView.end();
            });

        std::for_each(deletedEntities.begin(), deletedEntities.end(), [&](uint16_t id)
                      { camera.m_EntitiesInView.erase(std::remove(camera.m_EntitiesInView.begin(), camera.m_EntitiesInView.end(), id),
                                                      camera.m_EntitiesInView.end()); });

        coder.Write<bc::VarUint>(deletedEntities.size());
        std::for_each(deletedEntities.begin(), deletedEntities.end(), [&](uint16_t id)
                      { coder.Write<bc::VarUint>(id); });

        coder.Write<bc::VarUint>(entitiesInView.size());
        for (uint16_t id : entitiesInView)
        {
            bool isCreation = std::find(camera.m_EntitiesInView.begin(), camera.m_EntitiesInView.end(), id) == camera.m_EntitiesInView.end();
            if (isCreation)
                camera.m_EntitiesInView.push_back(id);
            coder.Write<Entity>(GetEntity(id), isCreation);
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
}
