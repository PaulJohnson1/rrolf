#include <Client/Game.hh>

#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Renderer.hh>
#include <Client/Simulation.hh>
#include <Client/Ui/Button.hh>
#include <Client/Ui/Text.hh>
#include <Client/Ui/Engine.hh>
#include <Client/Ui/ButtonTypes.hh>
#include <Client/Ui/MobButton.hh>

#include <Shared/StaticData.hh>

app::Game *g_Game = nullptr;

namespace app
{
    Game::Game(Renderer *renderer, Simulation *simulation)
    : m_Renderer(renderer)
    , m_Simulation(simulation)
    , m_InterpolationSystem(simulation)
    , m_RendererSystem(simulation, renderer)
    {
        g_Game = this;
        // ui test
        (m_UiElements.m_DeathScreen = ui::Add(
            ui::SetJustify<1, 1>(
                ui::MakeVContainer<200, 0>({
                    new ui::Text(*renderer, "You were killed by", 0xffffffff, 24),
                    ui::CreateRespawnButton(renderer)
                    }
                )
            )
        ))->m_Showing = false;
        m_UiElements.m_TitleScreen = ui::Add(
            ui::SetJustify<1, 1>(
                ui::MakeVContainer<100, 0>({
                    new ui::Text(*renderer, "rrolf", 0xffffffff, 96),
                    ui::MakeHContainer<25, 0>({
                        new ui::Text(*renderer, "this is your name", 0xffffffff, 25),
                        ui::CreateRespawnButton(renderer)
                    })
                })
            )
        );
        m_UiElements.m_Loadout = ui::Add(
            ui::VPad<10>(
                ui::SetJustify<1, 2>(
                    ui::MakeVContainer<10, 0, 1>({
                        ui::MakeHContainer<20, 10>({
                            ui::CreateLoadoutButton(renderer, 0),
                            ui::CreateLoadoutButton(renderer, 1),
                            ui::CreateLoadoutButton(renderer, 2),
                            ui::CreateLoadoutButton(renderer, 3),
                            ui::CreateLoadoutButton(renderer, 4),
                            ui::CreateLoadoutButton(renderer, 5),
                            ui::CreateLoadoutButton(renderer, 6),
                            ui::CreateLoadoutButton(renderer, 7),
                            ui::CreateLoadoutButton(renderer, 8),
                            ui::CreateLoadoutButton(renderer, 9)
                        }),
                        ui::MakeHContainer<20, 10>({
                            ui::CreateSecondaryButton(renderer, 10),
                            ui::CreateSecondaryButton(renderer, 11),
                            ui::CreateSecondaryButton(renderer, 12),
                            ui::CreateSecondaryButton(renderer, 13),
                            ui::CreateSecondaryButton(renderer, 14),
                            ui::CreateSecondaryButton(renderer, 15),
                            ui::CreateSecondaryButton(renderer, 16),
                            ui::CreateSecondaryButton(renderer, 17),
                            ui::CreateSecondaryButton(renderer, 18),
                            ui::CreateSecondaryButton(renderer, 19)
                        })
                    })
                )
            )
        );
        /*
        m_UiElements.m_Test = ui::Add(
            ui::HPad<10>(
                ui::SetJustify<0, 1>(
                    ui::AddBackground<0x80000000>(
                        ui::MakeVContainer<10, 10, 0>({
                            new ui::Text(*renderer, "Stinger", 0xffffffff, 25),
                            new ui::Text(*renderer, "Ultra", RARITY_COLORS[6], 12),
                            new ui::Text(*renderer, "It really hurts, but it's really fragile.", 0xffffffff, 12),
                            ui::MakeHContainer<0,0>({new ui::Text(*renderer, "Health: ", 0xffffffff, 12), new ui::Text(*renderer, "over 9000", 0xff23ee45, 12)}),
                            ui::MakeHContainer<0,0>({new ui::Text(*renderer, "Damage: ", 0xffffffff, 12), new ui::Text(*renderer, "beyond your feeble comprehension", 0xffee2345, 12)})
                        })
                    )
                )
            )
        );
        */
        m_UiElements.m_Test = ui::Add(
            ui::SetJustify<1, 0>(
                ui::MakeVContainer<20, 20>({
                    new ui::Text(*renderer, "Wave 69", 0xffffffff, 30),
                    ui::MakeHContainer<20, 10, 0>({
                        ui::MakeVContainer<-35, 0, 0>({
                            ui::CreateMobIcon(renderer,0,0),
                            ui::CreateMobIcon(renderer,0,1),                           
                            ui::CreateMobIcon(renderer,0,2),
                            ui::CreateMobIcon(renderer,0,3),
                            ui::CreateMobIcon(renderer,0,4),
                            ui::CreateMobIcon(renderer,0,5),
                            ui::CreateMobIcon(renderer,0,6),
                            ui::CreateMobIcon(renderer,0,7),
                        }),
                        ui::MakeVContainer<-35, 0, 0>({
                            ui::CreateMobIcon(renderer,1,0),
                            ui::CreateMobIcon(renderer,1,1),
                            ui::CreateMobIcon(renderer,1,2),
                            ui::CreateMobIcon(renderer,1,3),
                            ui::CreateMobIcon(renderer,1,4),
                            ui::CreateMobIcon(renderer,1,5),
                            ui::CreateMobIcon(renderer,1,6),
                            ui::CreateMobIcon(renderer,1,7)
                        }),
                        ui::MakeVContainer<-35, 0, 0>({
                            ui::CreateMobIcon(renderer,2,0),
                            ui::CreateMobIcon(renderer,2,1),
                            ui::CreateMobIcon(renderer,2,2),
                            ui::CreateMobIcon(renderer,2,3),
                            ui::CreateMobIcon(renderer,2,4),
                            ui::CreateMobIcon(renderer,2,5),
                            ui::CreateMobIcon(renderer,2,6),
                            ui::CreateMobIcon(renderer,2,7)
                        }),
                        ui::MakeVContainer<-35, 0, 0>({
                            ui::CreateMobIcon(renderer,3,0),
                            ui::CreateMobIcon(renderer,3,1),
                            ui::CreateMobIcon(renderer,3,2),
                            ui::CreateMobIcon(renderer,3,3),
                            ui::CreateMobIcon(renderer,3,4),
                            ui::CreateMobIcon(renderer,3,5),
                            ui::CreateMobIcon(renderer,3,6),
                            ui::CreateMobIcon(renderer,3,7)
                        }),
                        ui::MakeVContainer<-35, 0, 0>({
                            ui::CreateMobIcon(renderer,4,0),
                            ui::CreateMobIcon(renderer,4,1),
                            ui::CreateMobIcon(renderer,4,2),
                            ui::CreateMobIcon(renderer,4,3),
                            ui::CreateMobIcon(renderer,4,4),
                            ui::CreateMobIcon(renderer,4,5),
                            ui::CreateMobIcon(renderer,4,6),
                            ui::CreateMobIcon(renderer,4,7)
                        })
                    })
                })
            )
        );
    }

    void Game::Tick()
    {
        float time = GetTime();
        m_TickTime = time - m_LastTick;
        m_LastTick = time;
        if (m_Simulation->m_PlayerInfo != NULL_ENTITY)
        {
            if (!m_HasHadPlayer && m_Simulation->Get<component::PlayerInfo>(m_Simulation->m_PlayerInfo).m_HasPlayer) m_HasHadPlayer = true;
            m_InterpolationSystem.Tick();
            m_RendererSystem.Tick();

            m_InterpolationSystem.PostTick();
            m_RendererSystem.PostTick();

            // ui stuff

            m_UiElements.m_TitleScreen->m_Showing = !m_Simulation->Get<component::PlayerInfo>(m_Simulation->m_PlayerInfo).m_HasPlayer && !m_HasHadPlayer;
            m_UiElements.m_DeathScreen->m_Showing = !m_Simulation->Get<component::PlayerInfo>(m_Simulation->m_PlayerInfo).m_HasPlayer && m_HasHadPlayer;

            ui::Resize(m_UiElements.m_Loadout);
            ui::Resize(m_UiElements.m_Test);
            //((ui::Text *) m_UiElements.m_Test->m_Elements[0])->m_Text = std::string("wave ") + std::to_string(Get<component::ArenaInfo>(0).m_Wave);
            return;
        }
    }

    void Game::ReadBinary(uint8_t *data)
    {
        bc::BinaryCoder coder{data};
        uint8_t type = coder.Read<bc::Uint8>();

        if (type == 0)
        {
            uint64_t deletedEntityCount = coder.Read<bc::VarUint>();
            for (uint64_t i = 0; i < deletedEntityCount; i++)
                m_Simulation->Remove(coder.Read<bc::VarUint>());

            uint64_t updatedEntityCount = coder.Read<bc::VarUint>();
            for (uint64_t i = 0; i < updatedEntityCount; i++)
                m_Simulation->ReadEntity(coder);
        }
    }

    float Game::GetTime()
    {
#ifdef EMSCRIPTEN
        return EM_ASM_DOUBLE({
            return performance.now();
        });
#else
        using namespace std::chrono;
        system_clock::time_point start = system_clock::now();

        return duration_cast<microseconds>(start.time_since_epoch()).count() / 1000;
#endif
    }
}