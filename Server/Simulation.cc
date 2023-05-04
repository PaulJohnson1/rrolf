#ifndef M_PI
#define M_PI 3.14169265358979
#endif
#include <Server/Simulation.hh>

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <set>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Shared/Assert.hh>
#include <Shared/Entity.hh>
#include <Server/Server.hh>
#include <Shared/StaticData.hh>

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
          m_PetalBehavior(*this),
          m_DropCollector(*this)
    {
        for (Entity i = 0; i < MAX_ENTITY_COUNT - 1; i++)
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
        std::lock_guard<std::mutex> l(m_Server.m_Mutex);
        uint32_t mobCount = 0;
        ForEachEntity([&](Entity e)
                      { mobCount += HasComponent<component::Mob>(e); });
        if (mobCount < 4)
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
            mob.Rarity(7);
        }

        {
            m_Velocity.Tick();
            m_CollisionDetector.Tick();
            m_PetalBehavior.Tick();
            m_CollisionResolver.Tick();
            m_DropCollector.Tick();
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

        m_TickCount++;
    }

    bool Simulation::HasEntity(Entity entity)
    {
        assert(entity < MAX_ENTITY_COUNT);
        return m_EntityTracker[entity];
    }

    std::vector<Entity> Simulation::FindNearBy(Entity e, float r)
    {
        // assert(m_PhysicalTracker[e]);
        component::Physical &physical = Get<component::Physical>(e);
        return m_CollisionDetector.m_SpatialHash.GetCollisions(physical.X(), physical.Y(), r, r);
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

            // Check if the entity's position and size fall within the viewport
            if (physical.X() + physical.Radius() < viewX - viewWidth ||
                physical.X() - physical.Radius() > viewX + viewWidth ||
                physical.Y() + physical.Radius() < viewY - viewHeight ||
                physical.Y() - physical.Radius() > viewY + viewHeight)
                continue;

            if (!HasComponent<component::Drop>(other))
            {
                entitiesInView.push_back(other);
                continue;
            }
            std::vector<Entity> collectedBy = Get<component::Drop>(other).m_CollectedBy;
            if (std::find(collectedBy.begin(), collectedBy.end(), playerInfo.Player()) == collectedBy.end())
                entitiesInView.push_back(other);
        }
        return entitiesInView;
    }

    void Simulation::WriteUpdate(bc::BinaryCoder &coder, component::PlayerInfo &playerInfo)
    {
        std::vector<Entity> _entitiesInView = FindEntitiesInView(playerInfo);
        std::set<Entity> entitiesInView(
            std::make_move_iterator(_entitiesInView.begin()),
            std::make_move_iterator(_entitiesInView.end()));
        std::vector<Entity> deletedEntities;

        auto it = playerInfo.m_EntitiesInView.begin();
        while (it != playerInfo.m_EntitiesInView.end())
        {
            Entity id = *it;
            if (entitiesInView.find(id) == entitiesInView.end())
            {
                deletedEntities.push_back(id);
                it = playerInfo.m_EntitiesInView.erase(it);
            }
            else
                ++it;
        }

        coder.Write<bc::VarUint>(deletedEntities.size());
        for (Entity i = 0; i < deletedEntities.size(); i++)
            coder.Write<bc::VarUint>(deletedEntities[i]);

        coder.Write<bc::VarUint>(entitiesInView.size());
        for (Entity id : entitiesInView)
        {
            bool isCreation = playerInfo.m_EntitiesInView.find(id) == playerInfo.m_EntitiesInView.end();
            if (isCreation)
                playerInfo.m_EntitiesInView.insert(id);

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
        if (HasComponent<component::Mob>(id))
        {
            component::Mob &mob = Get<component::Mob>(id);
            component::Physical &mobPhysical = Get<component::Physical>(id);
            std::vector<component::Physical *> spawned = {};
            for (uint64_t i = 0; i < MOB_DATA[mob.Id()].m_Loot.size(); ++i)
            {
                std::vector<float> const &table = MOB_DATA[mob.Id()].m_Loot[i].m_Table[mob.Rarity()];
                float seed = ((float)rand()) / RAND_MAX;
                for (uint32_t rarity = 0; rarity <= RarityId::kMaxRarities; ++rarity)
                {
                    seed -= table[rarity];
                    if (seed < 0)
                    {
                        if (rarity != RarityId::kMaxRarities)
                        {
                            Entity dropId = Create();
                            component::Drop &drop = AddComponent<component::Drop>(dropId);
                            component::Physical &physical = AddComponent<component::Physical>(dropId);
                            component::Basic &basic = AddComponent<component::Basic>(dropId);
                            drop.Id(MOB_DATA[mob.Id()].m_Loot[i].m_Id);
                            drop.Rarity(rarity);
                            physical.X(mobPhysical.X());
                            physical.Y(mobPhysical.Y());
                            physical.Radius(25);
                            spawned.push_back(&physical);
                        }
                        break;
                    }
                }
            }
            if (spawned.size() > 1)
            {
                for (uint32_t i = 0; i < spawned.size(); ++i)
                {
                    spawned[i]->m_Velocity = Vector::FromPolar(10, i * M_PI * 2 / spawned.size());
                }
            }
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
