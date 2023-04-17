project(rrolf-server)
cmake_minimum_required(VERSION 3.16)

include_directories(..)
include_directories(ThirdParty)
include_directories(../Shared)

set(SOURCES
    Component/Ai.cc
    Component/ArenaInfo.cc
    Component/Basic.cc
    Component/Drop.cc
    Component/Flower.cc
    Component/Life.cc
    Component/Mob.cc
    Component/Petal.cc
    Component/Physical.cc
    Component/PlayerInfo.cc
    System/CollisionDetector.cc
    System/CollisionResolver.cc
    System/Damage.cc
    System/MapBoundaries.cc
    System/MobAi.cc
    System/Velocity.cc
    System/Petal.cc
    Client.cc
    Main.cc
    Server.cc
    Simulation.cc
    SpatialHash.cc
    Vector.cc
    ThirdParty/BinaryCoder/BinaryCoder.cc
    ThirdParty/BinaryCoder/NativeTypes.cc
    ../Shared/StaticData.cc
)

set(CMAKE_CXX_FLAGS "-std=c++20")

# release by default
if(DEBUG_BUILD)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -gdwarf-4)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRROLF_DISABLE_ASSERTIONS -O3")
endif()

set(CMAKE_CXX_FLAGS "-${CMAKE_CXX_FLAGS} -lpthread")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

add_executable(rrolf-server ${SOURCES})
if(WINDOWS)
    target_link_libraries(rrolf-server ws2_32 wsock32)
endif()