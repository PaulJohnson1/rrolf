project(rrolf-server)
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
    System/CollisionDetector.cc
    System/CollisionResolver.cc
    System/Damage.cc
    System/MapBoundaries.cc
    System/MobAi.cc
    System/Velocity.cc
    Client.cc
    Main.cc
    Server.cc
    Simulation.cc
    SpatialHash.cc
    Vector.cc
    ThirdParty/BinaryCoder/BinaryCoder.cc
    ThirdParty/BinaryCoder/NativeTypes.cc
    )

set(CMAKE_CXX_FLAGS "-std=c++17 -g -lpthread")
set(CMAKE_CXX_COMPILER "clang++")

add_executable(rrolf-server ${SOURCES})
if(WINDOWS)
    target_link_libraries(rrolf-server ws2_32 wsock32)
endif()