set(CMAKE_SYSTEM_NAME Generic)

cmake_minimum_required(VERSION 3.16)

project(rrolf-client)
include_directories(..)

set(SRCS
    Renderer/Common.c
    Renderer/RenderDrop.c
    Renderer/RenderFlower.c
    Renderer/RenderFunctions.c
    Renderer/RenderHealth.c
    Renderer/RenderMob.c
    Renderer/RenderPetal.c
    System/Interpolation.c
    Ui/Button.c
    Ui/Container.c
    Ui/Crafting.c
    Ui/Element.c
    Ui/Engine.c
    Ui/InGameSquadUi.c
    Ui/InventoryUi.c
    Ui/LoadoutUi.c
    Ui/PairedButton.c
    Ui/ScrollContainer.c
    Ui/SquadUi.c
    Ui/Text.c
    Ui/TextInput.c
    Ui/WaveUi.c
    Game.c
    InputData.c
    Main.c
    Simulation.c
    Socket.c
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
    ../Shared/Bitset.c
    ../Shared/Crypto.c
    ../Shared/pb.c
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
    # add_compile_options(-fsanitize=undefined,address)
    # add_link_options(-fsanitize=undefined,address)
elseif(CALLGRIND_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG -gdwarf-4 -DHSHG_NDEBUG -march=native")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -ffast-math -DNDEBUG")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if (WASM_BUILD)
    set(CMAKE_C_COMPILER "emcc")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS=_rr_renderer_main_loop,_main,_rr_key_event,_rr_mouse_event,_rr_wheel_event,_rr_on_socket_event_emscripten")
endif()

add_executable(rrolf-client ${SRCS})

if(NOT WASM_BUILD)
    target_link_libraries(rrolf-client websockets)
endif()

target_link_libraries(rrolf-client m)
