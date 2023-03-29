#include <Server/Simulation.hh>

#include <iostream>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Shared/Entity.hh>
#include <Server/Server.hh>

namespace app
{
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)                                           \
    template <>                                                                        \
    component::COMPONENT &Simulation::Get<component::COMPONENT>(Entity id)             \
    {                                                                                  \
        return m_##COMPONENT##Components.d[id];                                        \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    component::COMPONENT const &Simulation::Get<component::COMPONENT>(Entity id) const \
    {                                                                                  \
        return m_##COMPONENT##Components.d[id];                                        \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    bool Simulation::HasComponent<component::COMPONENT>(Entity id) const               \
    {                                                                                  \
        return m_##COMPONENT##Tracker[id];                                             \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    component::COMPONENT &Simulation::AddComponent<component::COMPONENT>(Entity id)    \
    {                                                                                  \
        m_##COMPONENT##Tracker[id] = true;                                             \
        new (&m_##COMPONENT##Components.d[id]) component::COMPONENT(id, this);               \
        return Get<component::COMPONENT>(id);                                          \
    }

    FOR_EACH_COMPONENT;

#undef RROLF_COMPONENT_ENTRY

    Simulation::Simulation(Server &s)
        : m_Server(s),
          m_CollisionDetector(*this),
          m_CollisionResolver(*this),
          m_Velocity(*this),
          m_MobAi(*this),
          m_MapBoundaries(*this),
          m_Damage(*this)
    {
        for (Entity i = 0; i < MAX_ENTITY_COUNT; i++)
        {
            m_AvailableIds.push(i);
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    m_##COMPONENT##Tracker[i] = false;
            FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        }

        m_Arena = Create();
        AddComponent<component::ArenaInfo>(m_Arena);
        Get<component::ArenaInfo>(m_Arena).MapSize(1650.0f);

        for (uint32_t i = 0; i < 100; i++)
        {
            Entity id = Create();
            component::Mob &mob = AddComponent<component::Mob>(id);
            component::Life &life = AddComponent<component::Life>(id);
            component::Physical &physical = AddComponent<component::Physical>(id);
            component::Basic &basic = AddComponent<component::Basic>(id);
            component::Ai &ai = AddComponent<component::Ai>(id);
            Vector p = Vector::FromPolar(sqrt(((float)rand() / (float)RAND_MAX)) * 1650, (float)rand() / (float)RAND_MAX * 1000.0);
            physical.X(p.m_X);
            physical.Y(p.m_Y);
            basic.Team(1); // arena team
            mob.Rarity(5);
            mob.Id(0); // baby ant
            life.Damage(10);
            life.MaxHealth(100);
            life.Health(100);
        }
    }

    void Simulation::Tick()
    {
        ForEachEntity([&](Entity id)
                      { ResetEntity(id); });

        std::string output;

#define TICK_SYSTEM(SYSTEM)                                                                           \
    {                                                                                                 \
        using namespace std::chrono;                                                                  \
        time_point start = system_clock::now();                                                       \
        m_##SYSTEM.Tick();                                                                            \
        time_point end = system_clock::now();                                                         \
        duration<double> difference = end - start;                                                    \
        output += #SYSTEM;                                                                            \
        output += "::Tick(): ";                                                                       \
        output += std::to_string((double)(duration_cast<microseconds>(difference).count()) / 1000.0); \
        output += "ms\n";                                                                             \
    }
        // order is critical
        TICK_SYSTEM(Velocity);
        TICK_SYSTEM(CollisionDetector);
        TICK_SYSTEM(CollisionResolver);
        TICK_SYSTEM(MapBoundaries);
        TICK_SYSTEM(MobAi);
        TICK_SYSTEM(Damage); // potentially deletes entities so it must come last to avoid reading deleted entities
        output += '\n';
        std::cout << output;
        // m_Velocity.Tick();
        // m_CollisionDetector.Tick();
        // m_CollisionResolver.Tick();
        // m_MapBoundaries.Tick();
        // m_MobAi.Tick();
#undef TICK_SYSTEM

        m_Velocity.PostTick();
        m_CollisionDetector.PostTick();
        m_CollisionResolver.PostTick();
        m_MapBoundaries.PostTick();
        m_MobAi.PostTick();
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
        for (Entity i = 0; i < deletedEntities.size(); i++)
            coder.Write<bc::VarUint>(deletedEntities[i]);

        coder.Write<bc::VarUint>(entitiesInView.size());
        for (Entity i = 0; i < entitiesInView.size(); i++)
        {
            Entity id = entitiesInView[i];
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
    componentFlags |= HasComponent<component::COMPONENT>(id) << ID;
            FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        }
        else
        {
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID) \
    componentFlags |= (HasComponent<component::COMPONENT>(id) && Get<component::COMPONENT>(id).m_State != 0) << ID;
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
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)    \
    if (HasComponent<component::COMPONENT>(id)) \
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
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)    \
    {                                           \
        using T = component::COMPONENT;         \
        if (HasComponent<T>(id))                \
        {                                       \
            m_##COMPONENT##Tracker[id] = false; \
            T &comp = Get<T>(id);               \
            comp.~T();                          \
        }                                       \
    }
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        m_EntityTracker[id] = false;
    }
}
