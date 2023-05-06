#ifndef M_PI
float M_PI = 3.14159265359;
#endif
#include <Server/System/PetalBehavior.hh>

#include <Server/Component/Heal.hh>
#include <Server/Component/Petal.hh>
#include <Server/Component/PlayerInfo.hh>
#include <Server/Component/Projectile.hh>
#include <Server/Simulation.hh>

#include <cmath>
#include <iostream>

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

            Physical &flowerPhysical = m_Simulation.Get<Physical>(playerInfo.Player());
            uint32_t currRotPos = 0;
            for (uint64_t i = 0; i < playerInfo.m_SlotCount; i++)
            {
                PlayerInfo::PetalSlot &petalSlot = playerInfo.m_PetalSlots[i];
                bool usingClump = petalSlot.m_Data->m_ClumpRadius != 0 && petalSlot.m_Petals.size() > 1;
                for (uint64_t j = 0; j < petalSlot.m_Petals.size(); j++)
                {
                    if (!usingClump || j == 0) ++currRotPos; //fix for clump
                    PlayerInfo::Petal &petalInfo = petalSlot.m_Petals[j];
                    
                    if (petalInfo.m_IsDead)
                    {
                        petalInfo.m_TicksUntilRespawn--;
            
                        if (petalInfo.m_TicksUntilRespawn <= 0)
                        {
                            petalInfo.m_SimulationId = m_Simulation.Create();
                            petalInfo.m_IsDead = false;
                            petalInfo.m_TicksUntilRespawn = petalSlot.m_Data->m_ReloadTicks;

                            Physical &physical = m_Simulation.AddComponent<Physical>(petalInfo.m_SimulationId);
                            Petal &petalEntity = m_Simulation.AddComponent<Petal>(petalInfo.m_SimulationId);
                            Life &life = m_Simulation.AddComponent<Life>(petalInfo.m_SimulationId);
                            Basic &basic = m_Simulation.AddComponent<Basic>(petalInfo.m_SimulationId);

                            basic.m_Owner = entity;
                            basic.Team(0);

                            petalEntity.Id(petalSlot.m_Data->m_Id);
                            petalEntity.Rarity(petalSlot.m_Rarity);
                            petalEntity.m_Detached = false;

                            petalEntity.m_RotationPos = currRotPos - 1; //because it actually starts at 1, not 0
                            petalEntity.m_InnerAngle = j * 2 * M_PI / petalSlot.m_Petals.size();
                            petalEntity.m_ClumpRadius = usingClump ? petalSlot.m_Data->m_ClumpRadius : 0;
                            petalEntity.m_Slot = i;
                            petalEntity.m_InnerPos = j;

                            Vector extension = Vector::FromPolar(flowerPhysical.Radius(), playerInfo.m_GlobalRotation + 2 * M_PI * (currRotPos - 1) / playerInfo.m_RotationCount);

                            physical.X(flowerPhysical.X() + extension.m_X); //fix
                            physical.Y(flowerPhysical.Y() + extension.m_Y);
                            physical.m_Friction = 0.75;

                            life.Health(petalSlot.m_Data->m_BaseHealth);
                            life.MaxHealth(life.Health());

                            if (petalSlot.m_Data->m_ShootDelay != 0)
                            {
                                Projectile &projectile = m_Simulation.AddComponent<Projectile>(petalInfo.m_SimulationId);
                                projectile.m_TicksUntilDeath = 75;
                                projectile.m_ShootDelay = petalSlot.m_Data->m_ShootDelay;
                                physical.Angle(playerInfo.m_GlobalRotation + 2 * M_PI * petalEntity.m_RotationPos / playerInfo.m_RotationCount);
                            }
                            if (petalSlot.m_Data->m_Heal != 0)
                            {
                                Heal &heal = m_Simulation.AddComponent<Heal>(petalInfo.m_SimulationId);
                                heal.m_HealAmount = petalSlot.m_Data->m_Heal * PETAL_DAMAGE_FACTOR[petalSlot.m_Rarity];
                            }
                        }
                    }
                    else
                        m_Simulation.Get<Petal>(petalInfo.m_SimulationId).m_RotationPos = currRotPos - 1;
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
                if (!m_Simulation.HasComponent<Mob>(basic.m_Owner)) //check if the petal is mob owned
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
            Life &flowerLife = m_Simulation.Get<Life>(playerInfo.Player());

            Vector petalPosition{physical.X(), physical.Y()};
            Vector flowerPosition{flowerPhysical.X(), flowerPhysical.Y()};

            if (!petal.m_Detached)
            {
                if (m_Simulation.HasComponent<Projectile>(entity))
                {
                    Projectile &projectile = m_Simulation.Get<Projectile>(entity);
                    projectile.m_ShootDelay--;
                    if (projectile.m_ShootDelay <= 0)
                    {
                        switch (petal.Id())
                        {
                            case PetalId::Missile:
                                if (!(playerInfo.m_MouseButton & 1))
                                    break;
                                MissileTarget(entity);
                                physical.m_Acceleration = Vector::FromPolar(8, physical.Angle());
                                physical.m_Velocity = Vector::FromPolar(100, physical.Angle());
                                ProjectileDetach(entity);
                                return;
                            case PetalId::Pollen:
                                if (!(playerInfo.m_MouseButton & 5))
                                    break;
                                physical.m_Friction = 0.3;
                                ProjectileDetach(entity);
                                return;
                            case PetalId::Rose: //USE FOR ACTIVE HEALS
                                if (flowerLife.Health() < flowerLife.MaxHealth())
                                {
                                    m_Simulation.Get<Heal>(entity).m_Target = playerInfo.Player(); //IT DOES NOT DETACH: IMPORTANT
                                    physical.m_Acceleration = (flowerPosition - petalPosition) * 0.4;
                                    if ((flowerPosition - petalPosition).Magnitude() < (physical.Radius() + flowerPhysical.Radius()))
                                    {
                                        flowerLife.Health(flowerLife.Health() + m_Simulation.Get<Heal>(entity).m_HealAmount);
                                        m_Simulation.RequestDeletion<true>(entity);
                                    }
                                    return; //IT SHOULD RETURN
                                }
                                else
                                    m_Simulation.Get<Heal>(entity).m_Target = NULL_ENTITY;
                                break;
                            default:
                                break; //add rose here
                        }
                    }
                }
                else if (m_Simulation.HasComponent<Heal>(entity))
                    flowerLife.Health(flowerLife.Health() + m_Simulation.Get<Heal>(entity).m_HealAmount);           

                float holdingRadius = 50;
                if (playerInfo.m_MouseButton & 1) holdingRadius = 150;
                else if (playerInfo.m_MouseButton & 4) holdingRadius = 25;

                holdingRadius += flowerPhysical.Radius();
                
                float currAngle = playerInfo.m_GlobalRotation + 2 * M_PI * petal.m_RotationPos / playerInfo.m_RotationCount;
                Vector extension = Vector::FromPolar(holdingRadius, currAngle);
                if (petal.m_ClumpRadius != 0)
                {
                    extension += Vector::FromPolar(petal.m_ClumpRadius, petal.m_InnerAngle + playerInfo.m_GlobalRotation * 4 / 3);
                    currAngle = petal.m_InnerAngle + playerInfo.m_GlobalRotation * 4 / 3;
                }

                Entity closest = NULL_ENTITY;
                if (m_Simulation.m_TickCount - basic.m_CreationTick > 12)
                {
                    std::vector<Entity> nearBy = m_Simulation.FindNearBy(entity, 200);
                    float distance = 1e10;
                    for (uint64_t i = 0; i < nearBy.size(); ++i)
                    {
                        Entity ent = nearBy[i];

                        if (!m_Simulation.HasComponent<Mob>(ent))
                            continue;
                        Physical &mobPhysical = m_Simulation.Get<Physical>(ent);
                        if (mobPhysical.DeletionTick() != 0)
                            continue;
                        Vector mobPosition = Vector{mobPhysical.X(), mobPhysical.Y()};
                        float distTo = (mobPosition - petalPosition).Magnitude();
                        if (distTo < distance && (extension + flowerPosition - mobPosition).Magnitude() < 200 + mobPhysical.Radius())
                        {
                            distance = distTo;
                            closest = ent;
                        }
                    }
                }
                if (closest != NULL_ENTITY)
                {
                    Physical &mobPhysical = m_Simulation.Get<Physical>(closest);
                    physical.m_Acceleration = (Vector{mobPhysical.X(), mobPhysical.Y()} - petalPosition) * 0.2;
                }
                else
                {
                    physical.m_Acceleration = (flowerPosition + extension - petalPosition) * 0.6;
                    if (m_Simulation.HasComponent<Projectile>(entity))
                        physical.Angle(currAngle);
                }
                return;
            }

            if (--m_Simulation.Get<Projectile>(entity).m_TicksUntilDeath <= 0)
                m_Simulation.RequestDeletion<true>(entity);
            //projectile

            switch (petal.Id())
            {
                case PetalId::Missile:
                    if (petal.Rarity() >= RarityId::Ultra)
                        MissileTarget(entity);
                    physical.m_Acceleration = Vector::FromPolar(8, physical.Angle());
                    break;
            }
        });
    }

    void PetalBehavior::MissileTarget(Entity missile)
    {
        component::Petal &petal = m_Simulation.Get<component::Petal>(missile);
        std::vector<Entity> nearBy = m_Simulation.FindNearBy(missile, 600);
        component::Physical &physical = m_Simulation.Get<component::Physical>(missile);
        Vector petalPosition = {physical.X(), physical.Y()};
        Entity closest = NULL_ENTITY;
        float distance = 1e10;
        for (uint64_t i = 0; i < nearBy.size(); ++i)
        {
            Entity ent = nearBy[i];
            if (!m_Simulation.HasComponent<component::Mob>(ent))
                continue;

            component::Physical &mobPhysical = m_Simulation.Get<component::Physical>(ent);
            Vector diff = Vector{mobPhysical.X(), mobPhysical.Y()} - petalPosition;
            float angle = diff.Theta();
            float distTo = diff.Magnitude();
            float diffAngle = std::fmod(angle - physical.Angle(), M_PI * 2);
            if (diffAngle < 0)
                diffAngle += M_PI * 2;
            if ((diffAngle < 0.2 * petal.Rarity() || M_PI * 2 - diffAngle < 0.2 * petal.Rarity()) && distTo < distance)
            {
                distance = distTo;
                closest = ent;
            }
        }
        if (closest != NULL_ENTITY)
        {
            component::Physical &mobPhysical = m_Simulation.Get<component::Physical>(closest);
            physical.Angle((Vector(mobPhysical.X(), mobPhysical.Y()) - petalPosition).Theta());
        }
    }

    void PetalBehavior::ProjectileDetach(Entity e)
    {
        component::Petal &petal = m_Simulation.Get<component::Petal>(e);
        component::Projectile &projectile = m_Simulation.Get<component::Projectile>(e);
        component::PlayerInfo &playerInfo = m_Simulation.Get<component::PlayerInfo>(m_Simulation.Get<component::Basic>(e).m_Owner);
        petal.m_Detached = true;
        playerInfo.m_PetalSlots[petal.m_Slot].m_Petals[petal.m_InnerPos].m_IsDead = true;
        playerInfo.m_PetalSlots[petal.m_Slot].m_Petals[petal.m_InnerPos].m_SimulationId = NULL_ENTITY;
        playerInfo.m_PetalSlots[petal.m_Slot].m_Petals[petal.m_InnerPos].m_TicksUntilRespawn = playerInfo.m_PetalSlots[petal.m_Slot].m_Data->m_ReloadTicks;
    }
}
