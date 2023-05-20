set(CMAKE_SYSTEM_NAME Generic)

cmake_minimum_required(VERSION 3.16)

project(rrolf-client)
include_directories(..)

set(SRCS
    Renderer/Common.c
    Game.c
    InputData.c
    Main.c
    Simulation.c
    Socket.c
    ../Shared/Component/Arena.c
    ../Shared/Component/Flower.c
    ../Shared/Component/Physical.c
    ../Shared/Component/PlayerInfo.c
    ../Shared/Bitset.c
    ../Shared/Encoder.c
    ../Shared/Utilities.c
    ../Shared/Vector.c
    ../Shared/SimulationCommon.c
)

set(CMAKE_C_FLAGS "-DRR_CLIENT")

# release by default
if(DEBUG_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-4")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if (WASM_BUILD)
    set(CMAKE_C_COMPILER "emcc")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s EXPORTED_FUNCTIONS=_rr_renderer_main_loop,_main,_rr_key_event,_rr_on_socket_event_emscripten")
endif()

add_executable(rrolf-client ${SRCS})

if(NOT WASM_BUILD)
    target_link_libraries(rrolf-client websockets)
endif()