#ifndef M_PI
float M_PI = 3.14159265359;
#endif
#include <Server/System/PetalBehavior.hh>

#include <Server/Component/Petal.hh>
#include <Server/Component/PlayerInfo.hh>
#include <Server/Component/Projectile.hh>
#include <Server/Simulation.hh>

#include <cmath>

namespace app::system
{
    PetalBehavior::PetalBehavior(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void PetalBehavior::Tick()
    {
        using namespace component;

        // petal timers
        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (!m_Simulation.HasComponent<PlayerInfo>(entity))
                return;
            PlayerInfo &playerInfo = m_Simulation.Get<PlayerInfo>(entity);

            if (!playerInfo.HasPlayer())
                return;

            uint32_t currRotPos = 0;            
            for (uint64_t i = 0; i < playerInfo.m_SlotCount; i++)
            {
                PlayerInfo::PetalSlot &petalSlot = playerInfo.m_PetalSlots[i];
                bool usingClump = petalSlot.m_Data.m_ClumpRadius != 0 && petalSlot.m_Petals.size() > 1;
                for (uint64_t j = 0; j < petalSlot.m_Petals.size(); j++)
                {
                    if (!usingClump || j == 0) currRotPos++; //fix for clump
                    PlayerInfo::Petal &petalInfo = petalSlot.m_Petals[j];
                    
                    if (petalInfo.m_IsDead)
                    {
                        petalInfo.m_TicksUntilRespawn--;
            
                        if (petalInfo.m_TicksUntilRespawn <= 0)
                        {
                            petalInfo.m_SimulationId = m_Simulation.Create();
                            petalInfo.m_IsDead = false;
                            petalInfo.m_TicksUntilRespawn = petalSlot.m_Data.m_ReloadTicks;

                            Physical &physical = m_Simulation.AddComponent<Physical>(petalInfo.m_SimulationId);
                            Petal &petalEntity = m_Simulation.AddComponent<Petal>(petalInfo.m_SimulationId);
                            Life &life = m_Simulation.AddComponent<Life>(petalInfo.m_SimulationId);
                            Basic &basic = m_Simulation.AddComponent<Basic>(petalInfo.m_SimulationId);

                            basic.m_Owner = entity;
                            basic.Team(0);

                            petalEntity.Id(petalSlot.m_Data.m_Id);
                            petalEntity.Rarity(petalSlot.m_Rarity);

                            petalEntity.m_RotationPos = currRotPos - 1; //because it actually starts at 1, not 0
                            petalEntity.m_InnerAngle = j * 2 * M_PI / petalSlot.m_Petals.size();
                            petalEntity.m_ClumpRadius = usingClump ? petalSlot.m_Data.m_ClumpRadius : 0;
                            petalEntity.m_Slot = i;
                            petalEntity.m_InnerPos = j;

                            physical.X(playerInfo.CameraX()); //fix
                            physical.Y(playerInfo.CameraY());
                            physical.m_Friction = 0.75;

                            life.Health(petalSlot.m_Data.m_BaseHealth);
                            life.MaxHealth(life.Health());

                            if (petalSlot.m_Data.m_ShootDelay != 0)
                            {
                                Projectile &projectile = m_Simulation.AddComponent<Projectile>(petalInfo.m_SimulationId);
                                projectile.m_Detached = false;
                                projectile.m_TicksUntilDeath = 1500;
                                projectile.m_ShootDelay = petalSlot.m_Data.m_ShootDelay;
                                physical.Angle(playerInfo.m_GlobalRotation + 2 * M_PI * petalEntity.m_RotationPos / playerInfo.m_RotationCount);
                            }
                        }
                    }
                }
            } 
            playerInfo.m_GlobalRotation += 0.1;
            playerInfo.m_RotationCount = currRotPos;
        });

        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (!m_Simulation.HasComponent<Petal>(entity))
                return;
            Petal &petal = m_Simulation.Get<Petal>(entity);
            Physical &physical = m_Simulation.Get<Physical>(entity);
            if (physical.DeletionTick() != 0)
                return;
            Basic &basic = m_Simulation.Get<Basic>(entity);
            if (!m_Simulation.HasEntity(basic.m_Owner)) // owner left
            {
                m_Simulation.RequestDeletion<true>(entity);
                return;
            }
            if (!m_Simulation.HasComponent<PlayerInfo>(basic.m_Owner)) // owner left and something replaced it
            {
                m_Simulation.RequestDeletion<true>(entity);
                return;
            }
            PlayerInfo &playerInfo = m_Simulation.Get<PlayerInfo>(basic.m_Owner);
            if (!playerInfo.HasPlayer()) // player died
            {
                m_Simulation.RequestDeletion<true>(entity);
                return;
            }
            Physical &flowerPhysical = m_Simulation.Get<Physical>(playerInfo.Player());

            Vector petalPosition{physical.X(), physical.Y()};
            Vector flowerPosition{flowerPhysical.X(), flowerPhysical.Y()};

            bool isProjectile = m_Simulation.HasComponent<Projectile>(entity);

            if (isProjectile)
            {
                Projectile &projectile = m_Simulation.Get<Projectile>(entity);
                --projectile.m_ShootDelay;
                if (playerInfo.m_MouseButton & 1 && !projectile.m_Detached && projectile.m_ShootDelay <= 0)
                {
                    projectile.m_Detached = true;
                    physical.m_Acceleration = Vector::FromPolar(10, physical.Angle());
                    physical.m_Velocity = Vector::FromPolar(100, physical.Angle());

                    //detach
                    playerInfo.m_PetalSlots[petal.m_Slot].m_Petals[petal.m_InnerPos].m_IsDead = true;
                    playerInfo.m_PetalSlots[petal.m_Slot].m_Petals[petal.m_InnerPos].m_TicksUntilRespawn = playerInfo.m_PetalSlots[petal.m_Slot].m_Data.m_ReloadTicks; 

                    //one-time homing
                    if (petal.Id() == PetalId::Missile)
                    {
                        std::vector<Entity> nearBy = m_Simulation.FindNearBy(petalPosition.m_X, petalPosition.m_Y, 200 * petal.Rarity());
                        Entity closest = (Entity)-1;
                        float distance = INFINITY;
                        for (uint64_t i = 0; i < nearBy.size(); ++i)
                        {
                            Entity ent = nearBy[i];
                            if (!m_Simulation.HasComponent<Mob>(ent))
                                continue;
                            
                            Physical &mobPhysical = m_Simulation.Get<Physical>(ent);
                            Vector diff = Vector(mobPhysical.X(), mobPhysical.Y()) - petalPosition;
                            float angle = diff.Theta();
                            float distTo = diff.Magnitude();
                            float diffAngle = std::fmod(angle - physical.Angle(), M_PI * 2);
                            if (diffAngle < 0)
                                diffAngle += M_PI * 2;
                            if ((diffAngle < 0.9 || M_PI * 2 - diffAngle < 0.9) && distTo < distance)
                            {
                                distance = distTo;
                                closest = ent;
                            }
                        }
                        if (closest != (Entity)-1)
                        {
                            Physical &mobPhysical = m_Simulation.Get<Physical>(closest);
                            physical.Angle((Vector(mobPhysical.X(), mobPhysical.Y()) - petalPosition).Theta());
                        }
                    }
                }
            }
            if (!isProjectile || !m_Simulation.Get<Projectile>(entity).m_Detached)
            {
                float holdingRadius = 75;
                if (playerInfo.m_MouseButton & 1) holdingRadius = 175;
                else if (playerInfo.m_MouseButton & 4) holdingRadius = 45;
                
                float currAngle = playerInfo.m_GlobalRotation + 2 * M_PI * petal.m_RotationPos / playerInfo.m_RotationCount;
                Vector extension = Vector::FromPolar(holdingRadius, currAngle);
                if (petal.m_ClumpRadius != 0)
                {
                    extension += Vector::FromPolar(petal.m_ClumpRadius, petal.m_InnerAngle + playerInfo.m_GlobalRotation * 4 / 3);
                    currAngle = petal.m_InnerAngle + playerInfo.m_GlobalRotation * 4 / 3;
                }

                std::vector<Entity> nearBy = m_Simulation.FindNearBy(petalPosition.m_X, petalPosition.m_Y, 400);
                Entity closest = (Entity)-1;
                float distance = INFINITY;
                for (uint64_t i = 0; i < nearBy.size(); ++i)
                {
                    Entity ent = nearBy[i];
                    if (!m_Simulation.HasComponent<Mob>(ent))
                        continue;
                    
                    Physical &mobPhysical = m_Simulation.Get<Physical>(ent);
                    Vector mobPosition = Vector{mobPhysical.X(), mobPhysical.Y()};
                    float distTo = (mobPosition - petalPosition).Magnitude();
                    if (distTo < distance && (extension + flowerPosition - mobPosition).Magnitude() < 200 + mobPhysical.Radius())
                    {
                        distance = distTo;
                        closest = ent;
                    }
                }
                if (closest != (Entity)-1)
                {
                    Physical &mobPhysical = m_Simulation.Get<Physical>(closest);
                    physical.m_Acceleration = (Vector{mobPhysical.X(), mobPhysical.Y()} - petalPosition) * 0.1;
                    return;
                }

                physical.m_Acceleration = (flowerPosition + extension - petalPosition) * 0.8;
                if (m_Simulation.HasComponent<Projectile>(entity))
                    physical.Angle(currAngle);
                return;
            }


            physical.m_Acceleration = Vector::FromPolar(10, physical.Angle());
            if (--m_Simulation.Get<Projectile>(entity).m_TicksUntilDeath <= 0)
            {
                m_Simulation.RequestDeletion<true>(entity);
            }

            if (petal.Id() == PetalId::Missile && petal.Rarity() == RarityId::Ultra)
            {
                std::vector<Entity> nearBy = m_Simulation.FindNearBy(petalPosition.m_X, petalPosition.m_Y, 200 * petal.Rarity());
                Entity closest = (Entity)-1;
                float distance = 1e10;
                for (uint64_t i = 0; i < nearBy.size(); ++i)
                {
                    Entity ent = nearBy[i];
                    if (!m_Simulation.HasComponent<Mob>(ent))
                        continue;
                    
                    Physical &mobPhysical = m_Simulation.Get<Physical>(ent);
                    Vector diff = Vector(mobPhysical.X(), mobPhysical.Y()) - petalPosition;
                    float angle = diff.Theta();
                    float distTo = diff.Magnitude();
                    float diffAngle = std::fmod(angle - physical.Angle(), M_PI * 2);
                    if (diffAngle < 0)
                        diffAngle += M_PI * 2;
                    if ((diffAngle < 0.9 || M_PI * 2 - diffAngle < 0.9) && distTo < distance)
                    {
                        distance = distTo;
                        closest = ent;
                    }
                }
                if (closest != (Entity)-1)
                {
                    Physical &mobPhysical = m_Simulation.Get<Physical>(closest);
                    physical.Angle((Vector(mobPhysical.X(), mobPhysical.Y()) - petalPosition).Theta());
                }
            }
        });
    }
}
