set(CMAKE_SYSTEM_NAME Generic)

project(rrolf-client)
cmake_minimum_required(VERSION 3.16)

include_directories(..)
include_directories(ThirdParty)
set(SOURCES
    Component/Ai.cc
    Component/ArenaInfo.cc
    Component/Basic.cc
    Component/Flower.cc
    Component/Life.cc
    Component/Mob.cc
    Component/Physical.cc
    Component/PlayerInfo.cc
    System/Interpolation.cc
    System/Renderer.cc
    Main.cc
    Renderer.cc
    Simulation.cc
    Socket.cc
    ThirdParty/BinaryCoder/BinaryCoder.cc
    ThirdParty/BinaryCoder/NativeTypes.cc
)


if(WASM_BUILD)
    set(CMAKE_CXX_FLAGS "-std=c++20 -g -s EXPORTED_FUNCTIONS=_main,_malloc,_free,_OnMessage,_OnOpen,_OnClose,_Render,_KeyEvent")
    set(CMAKE_CXX_COMPILER "em++")
else()
    set(CMAKE_CXX_FLAGS "-std=c++20 -g -lcrypto -lssl -lskia -lglfw")
    set(CMAKE_CXX_COMPILER "clang++")
    include_directories(/usr/include)
    include_directories(/usr/include/skia)
endif()
add_executable(rrolf-client ${SOURCES})

