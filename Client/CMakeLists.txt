set(CMAKE_SYSTEM_NAME Generic)

cmake_minimum_required(VERSION 3.16)

project(rrolf-client)
include_directories(..)

set(SRCS
    Assets/MapFeature/Moss.c
    Assets/MapFeature/WaterLettuce.c
    Assets/Mob/Ankylosaurus/Body.c
    Assets/Mob/Ankylosaurus/Head.c
    Assets/Mob/Ankylosaurus/Tail.c
    Assets/Mob/Dakotaraptor/Body.c
    Assets/Mob/Dakotaraptor/Head.c
    Assets/Mob/Dakotaraptor/Tail.c
    Assets/Mob/Dakotaraptor/Wing1.c
    Assets/Mob/Dakotaraptor/Wing2.c
    Assets/Mob/Edmontosaurus/Body.c
    Assets/Mob/Edmontosaurus/Head.c
    Assets/Mob/Edmontosaurus/Leg1.c
    Assets/Mob/Edmontosaurus/Leg2.c
    Assets/Mob/Edmontosaurus/Tail.c
    Assets/Mob/Ornithomimus/Body.c
    Assets/Mob/Ornithomimus/Head.c
    Assets/Mob/Ornithomimus/Tail.c
    Assets/Mob/Ornithomimus/Wing1.c
    Assets/Mob/Ornithomimus/Wing2.c
    Assets/Mob/Pachycephalosaurus/Body.c
    Assets/Mob/Pachycephalosaurus/Head.c
    Assets/Mob/Pachycephalosaurus/Leg1.c
    Assets/Mob/Pachycephalosaurus/Leg2.c
    Assets/Mob/Pachycephalosaurus/Tail.c
    Assets/Mob/Pectinodon/Body.c
    Assets/Mob/Pectinodon/Head.c
    Assets/Mob/Pectinodon/Tail.c
    Assets/Mob/Pectinodon/Wing1.c
    Assets/Mob/Pectinodon/Wing2.c
    Assets/Mob/Pteranodon/Body.c
    Assets/Mob/Pteranodon/Wing1.c
    Assets/Mob/Pteranodon/Wing2.c
    Assets/Mob/Quetzalcoatlus/Body.c
    Assets/Mob/Quetzalcoatlus/Head.c
    Assets/Mob/Quetzalcoatlus/Wing1.c
    Assets/Mob/Quetzalcoatlus/Wing2.c
    Assets/Mob/Rex/Body.c
    Assets/Mob/Rex/Head.c
    Assets/Mob/Rex/Leg1.c
    Assets/Mob/Rex/Leg2.c
    Assets/Mob/Rex/Tail.c
    Assets/Mob/Triceratops/Body.c
    Assets/Mob/Triceratops/Head.c
    Assets/Mob/Triceratops/Leg1.c
    Assets/Mob/Triceratops/Leg2.c
    Assets/Mob/Triceratops/Tail.c
    Assets/Mob/Fern.c
    Assets/Mob/Meteor.c
    Assets/Mob/Tree.c
    Assets/Init.c
    Assets/RenderPetals.c
    Assets/RenderRarityBackground.c
    Assets/RenderText.c
    DOM.c
    Particle.c
    Renderer/Common.c
    Renderer/RenderDrop.c
    Renderer/RenderFlower.c
    Renderer/RenderFunctions.c
    Renderer/RenderHealth.c
    Renderer/RenderMob.c
    Renderer/RenderPetal.c
    Renderer/RenderWeb.c
    Storage.c
    System/DeletionAnimation.c
    System/Interpolation.c
    System/ParticleRender.c
    Ui/Button.c
    Ui/ChooseElement.c
    Ui/Container.c
    Ui/Element.c
    Ui/Engine.c
    Ui/InGame/Deathscreen.c
    Ui/InGame/Loadout.c
    Ui/InGame/PetalsCollected.c
    Ui/InGame/Squad.c
    Ui/InGame/Wave.c
    Ui/ScrollContainer.c
    Ui/TitleScreen/BiomeButton.c
    Ui/TitleScreen/Changelog.c
    Ui/TitleScreen/Crafting.c
    Ui/TitleScreen/Inventory.c
    Ui/TitleScreen/LevelBar.c
    Ui/TitleScreen/MobGallery.c
    Ui/TitleScreen/Rivet.c
    Ui/TitleScreen/Settings.c
    Ui/TitleScreen/Squad.c
    Ui/Slider.c
    Ui/Text.c
    Ui/TextInput.c
    Ui/ToggleBox.c
    Ui/Tooltip/Petal.c
    Ui/Tooltip/Mob.c
    Ui/Tooltip/Squad.c
    Game.c
    InputData.c
    Main.c
    Mobile.c
    Simulation.c
    Socket.c
    Storage.c
    ../Shared/Api.c
    ../Shared/Binary.c
    ../Shared/Component/Ai.c
    ../Shared/Component/Arena.c
    ../Shared/Component/Centipede.c
    ../Shared/Component/Drop.c
    ../Shared/Component/Flower.c
    ../Shared/Component/Health.c
    ../Shared/Component/Mob.c
    ../Shared/Component/Petal.c
    ../Shared/Component/Physical.c
    ../Shared/Component/PlayerInfo.c
    ../Shared/Component/Projectile.c
    ../Shared/Component/Relations.c
    ../Shared/Component/Web.c
    ../Shared/Bitset.c
    ../Shared/cJSON.c
    ../Shared/Crypto.c
    ../Shared/pb.c
    ../Shared/Rivet.c
    ../Shared/SimulationCommon.c
    ../Shared/StaticData.c
    ../Shared/Utilities.c
    ../Shared/Vector.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRR_CLIENT")
set(CMAKE_C_COMPILER "clang")

# release by default
if(DEBUG_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-4")
    # add_compile_options(-fsanitize=address)
    # add_link_options(-fsanitize=address)
elseif(CALLGRIND_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG -gdwarf-4 -DHSHG_NDEBUG -march=native")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -ffast-math -DNDEBUG")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if (WASM_BUILD)
    set(CMAKE_C_COMPILER "emcc")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWASM_BUILD -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS=_malloc,_free,_rr_rivet_on_log_in,_rr_rivet_lobby_on_find,_rr_renderer_main_loop,_main,_rr_key_event,_rr_mouse_event,_rr_touch_event,_rr_wheel_event,_rr_on_socket_event_emscripten,_rr_api_on_get_petals,_rr_api_on_craft_result")
    set(SRCS ${SRCS} Renderer/Wasm.c)
else()
    set(SRCS ${SRCS} Renderer/Native.cc)
endif()

if(RIVET_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRIVET_BUILD")
endif()

add_executable(rrolf-client ${SRCS})

if(NOT WASM_BUILD)
    target_link_libraries(rrolf-client websockets cairo curl)
endif()

target_link_libraries(rrolf-client m)
