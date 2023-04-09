#include <Server/Simulation.hh>

#include <cstdio>
#include <cstdlib>
#include <unistd.h>

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
        assert(m_EntityTracker[id]);                                                   \
        assert(m_##COMPONENT##Tracker[id]);                                            \
        return m_##COMPONENT##Components.d[id];                                        \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    component::COMPONENT const &Simulation::Get<component::COMPONENT>(Entity id) const \
    {                                                                                  \
        assert(m_EntityTracker[id]);                                                   \
        assert(m_##COMPONENT##Tracker[id]);                                            \
        return m_##COMPONENT##Components.d[id];                                        \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    bool Simulation::HasComponent<component::COMPONENT>(Entity id) const               \
    {                                                                                  \
        assert(m_EntityTracker[id]);                                                   \
        return m_##COMPONENT##Tracker[id];                                             \
    }                                                                                  \
                                                                                       \
    template <>                                                                        \
    component::COMPONENT &Simulation::AddComponent<component::COMPONENT>(Entity id)    \
    {                                                                                  \
        assert(m_EntityTracker[id]);                                                   \
        assert(!m_##COMPONENT##Tracker[id]);                                           \
        m_##COMPONENT##Tracker[id] = true;                                             \
        new (&m_##COMPONENT##Components.d[id]) component::COMPONENT(id, this);         \
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
          m_Damage(*this),
          m_Petal(*this)
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
    }

    void Simulation::Tick()
    {
        uint32_t entityCount = 0;
        ForEachEntity([&](Entity)
                      { entityCount++; });
        if (entityCount < 100)
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
            mob.Id(0);     // baby ant
            mob.Rarity(rand() % 6);
            //mob.Rarity(5);
        }

        {
            std::unique_lock<std::mutex> l(m_Mutex);
            m_Petal.Tick();
            m_Velocity.Tick();
            m_CollisionDetector.Tick();
            m_CollisionResolver.Tick();
            m_MapBoundaries.Tick();
            m_MobAi.Tick();
            m_Damage.Tick();
        }
        for (uint64_t i = 0; i < m_Server.m_Clients.size(); i++)
            m_Server.m_Clients[i]->Tick();
        ForEachEntity([&](Entity id)
                      { ResetEntity(id); });
        for (Entity i = 0; i < m_PendingDeletions.size(); i++)
            Remove(m_PendingDeletions[i]);

        m_PendingDeletions.clear();
    }

    bool Simulation::HasEntity(Entity entity)
    {
        assert(entity < MAX_ENTITY_COUNT);
        return m_EntityTracker[entity];
    }

    std::vector<Entity> Simulation::FindEntitiesInView(component::PlayerInfo &playerInfo)
    {
        std::vector<Entity> entitiesInView{};
        entitiesInView.push_back(m_Arena);
        entitiesInView.push_back(playerInfo.m_Parent);

        int32_t viewWidth = (int32_t)(1280 / playerInfo.Fov());
        int32_t viewHeight = (int32_t)(720 / playerInfo.Fov());
        int32_t viewX = (int32_t)playerInfo.CameraX();
        int32_t viewY = (int32_t)playerInfo.CameraY();
        // not only is this needed for optimization, but it is also needed to ensure only physical entities are added to the list
        std::vector<Entity> nearBy = m_CollisionDetector.m_SpatialHash.GetCollisions(viewX, viewY, viewWidth, viewHeight);
        for (Entity i = 0; i < nearBy.size(); i++)
        {
            Entity other = nearBy[i];
            component::Physical &physical = Get<component::Physical>(other);
            // TODO: box collision
            entitiesInView.push_back(other);
        }
        return entitiesInView;
    }

    void Simulation::WriteUpdate(bc::BinaryCoder &coder, component::PlayerInfo &playerInfo)
    {
        std::vector<Entity> entitiesInView = FindEntitiesInView(playerInfo);
        std::vector<Entity> deletedEntities;

        for (Entity i = 0; i < playerInfo.m_EntitiesInView.size(); i++)
        {
            Entity id = playerInfo.m_EntitiesInView[i];
            // id is not in the entities the client should view
            if (std::find(entitiesInView.begin(), entitiesInView.end(), id) == entitiesInView.end())
            {
                deletedEntities.push_back(id);
                // remove id from the playerInfo's view after writing deletion so it does not get deleted twice
                playerInfo.m_EntitiesInView.erase(std::find(playerInfo.m_EntitiesInView.begin(), playerInfo.m_EntitiesInView.end(), id));
            }
        }

        coder.Write<bc::VarUint>(deletedEntities.size());
        for (Entity i = 0; i < deletedEntities.size(); i++)
            coder.Write<bc::VarUint>(deletedEntities[i]);

        coder.Write<bc::VarUint>(entitiesInView.size());
        for (Entity i = 0; i < entitiesInView.size(); i++)
        {
            Entity id = entitiesInView[i];
            bool isCreation = std::find(playerInfo.m_EntitiesInView.begin(), playerInfo.m_EntitiesInView.end(), id) == playerInfo.m_EntitiesInView.end();
            if (isCreation)
                playerInfo.m_EntitiesInView.push_back(id);

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

    void Simulation::RequestDeletion(Entity id)
    {
        if (HasComponent<component::Petal>(id))
            std::cout << "a petal was deleted\n";

        if (std::find(m_PendingDeletions.begin(), m_PendingDeletions.end(), id) == m_PendingDeletions.end())
            m_PendingDeletions.push_back(id);
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
        if (HasComponent<component::Mob>(id))
        {
            component::Physical &mobPhysical = Get<component::Physical>(id);
            std::cout << "should spawn drop\n";
            Entity dropId = Create();
            component::Drop &drop = AddComponent<component::Drop>(dropId);
            component::Physical &physical = AddComponent<component::Physical>(dropId);
            component::Basic &basic = AddComponent<component::Basic>(dropId);
            drop.Id(1);
            drop.Rarity(1);
            physical.X(mobPhysical.X());
            physical.Y(mobPhysical.Y());
            physical.Radius(60);
        }
#define RROLF_COMPONENT_ENTRY(COMPONENT, ID)    \
    {                                           \
        using T = component::COMPONENT;         \
        if (HasComponent<T>(id))                \
        {                                       \
            T &comp = Get<T>(id);               \
            comp.~T();                          \
            m_##COMPONENT##Tracker[id] = false; \
        }                                       \
    }
        FOR_EACH_COMPONENT;
#undef RROLF_COMPONENT_ENTRY
        m_EntityTracker[id] = false;
        m_AvailableIds.push(id);
    }
}
