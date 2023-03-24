project(rrolf-client)
cmake_minimum_required(VERSION 3.24)

include_directories(..)
include_directories(ThirdParty)

set(SOURCES
    Component/Flower.cc
    Component/Life.cc
    Component/Physical.cc
    Component/Render.cc
    System/Interpolation.cc
    System/Renderer.cc
    Main.cc
    Renderer.cc
    Simulation.cc
    Socket.cc
    ThirdParty/BinaryCoder/BinaryCoder.cc
    ThirdParty/BinaryCoder/NativeTypes.cc
)

set(CMAKE_CXX_FLAGS "-std=c++20 -g -lcrypto -lssl -lskia -lglfw")
set(CMAKE_CXX_COMPILER "clang++")

if(WASM_BUILD)
    set(CMAKE_CXX_FLAGS "-std=c++20 -g -DWASM_BUILD -sEXPORTED_FUNCTIONS=\"_main,_malloc,_free,_OnMessage,_OnOpen,_OnClose,_Render,_KeyEvent\"")
    set(CMAKE_CXX_COMPILER "em++")
else()
    include_directories(/usr/include)
    include_directories(/usr/include/skia)
endif()

add_executable(rrolf-client ${SOURCES})
