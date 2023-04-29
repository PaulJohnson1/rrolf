#ifndef M_PI
float M_PI = 3.14159265359;
#endif
#include <Server/System/PetalBehavior.hh>

#include <Server/Component/Petal.hh>
#include <Server/Component/PlayerInfo.hh>
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
                            component::Petal &petalEntity = m_Simulation.AddComponent<component::Petal>(petalInfo.m_SimulationId);
                            Life &life = m_Simulation.AddComponent<Life>(petalInfo.m_SimulationId);
                            Basic &basic = m_Simulation.AddComponent<Basic>(petalInfo.m_SimulationId);

                            basic.m_Owner = entity;
                            basic.Team(0);

                            petalEntity.Id(petalSlot.m_Data.m_Id);
                            petalEntity.Rarity(petalSlot.m_Rarity);
                            petalEntity.Shootable(petalSlot.m_Data.m_Shootable);
                            petalEntity.Independent(false);
                            petalEntity.m_RotationPos = currRotPos - 1; //because it actually starts at 1, not 0
                            petalEntity.m_InnerAngle = j * 2 * M_PI / petalSlot.m_Petals.size();
                            petalEntity.m_ClumpRadius = usingClump ? petalSlot.m_Data.m_ClumpRadius : 0;

                            physical.X(playerInfo.CameraX()); //fix
                            physical.Y(playerInfo.CameraY());
                            physical.m_Friction = 0.75;

                            life.Health(petalSlot.m_Data.m_BaseHealth);
                            life.MaxHealth(life.Health());
                        }
                    }
                }
            } 
            playerInfo.m_GlobalRotation += 0.1;
            playerInfo.m_RotationCount = currRotPos;
        });

        m_Simulation.ForEachEntity([&](Entity entity)
                                   {
            if (!m_Simulation.HasComponent<component::Petal>(entity))
                return;
            component::Petal &petal = m_Simulation.Get<component::Petal>(entity);
            Physical &physical = m_Simulation.Get<Physical>(entity);
            Basic &basic = m_Simulation.Get<Basic>(entity);
            if (!m_Simulation.HasEntity(basic.m_Owner)) // owner left
            {
                m_Simulation.RequestDeletion(entity);
                return;
            }
            if (!m_Simulation.HasComponent<PlayerInfo>(basic.m_Owner)) // owner left and something replaced it
            {
                m_Simulation.RequestDeletion(entity);
                return;
            }
            PlayerInfo &playerInfo = m_Simulation.Get<PlayerInfo>(basic.m_Owner);
            if (!playerInfo.HasPlayer()) // player died
            {
                m_Simulation.RequestDeletion(entity);
                return;
            }
            Physical &flowerPhysical = m_Simulation.Get<Physical>(playerInfo.Player());
            Vector petalPosition{physical.X(), physical.Y()};
            Vector flowerPosition{flowerPhysical.X(), flowerPhysical.Y()};
            if (petal.Shootable() && playerInfo.m_MouseButton & 1 && !petal.Independent())
            {
                petal.Independent(true);
                physical.m_Acceleration = Vector::FromPolar(10, physical.Angle());
                physical.m_Velocity = Vector::FromPolar(100, physical.Angle());
            }
            if (!petal.Independent())
            {
                float holdingRadius = 75;
                if (playerInfo.m_MouseButton & 1) holdingRadius = 175;
                else if (playerInfo.m_MouseButton & 4) holdingRadius = 45;
                
                float currAngle = playerInfo.m_GlobalRotation + 2 * M_PI * petal.m_RotationPos / playerInfo.m_RotationCount;
                Vector extension = Vector::FromPolar(holdingRadius, currAngle);
                extension += Vector::FromPolar(petal.m_ClumpRadius, petal.m_InnerAngle + playerInfo.m_GlobalRotation * 4 / 3);
                physical.m_Acceleration = (flowerPosition + extension - petalPosition) * 0.8;
                if (petal.Shootable())
                    physical.Angle(currAngle);
                return;
            }

            physical.m_Acceleration = Vector::FromPolar(10, physical.Angle());
        });
    }
}
