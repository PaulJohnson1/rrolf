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
    Component/Heal.cc 
    Component/Mob.cc
    Component/Petal.cc
    Component/Physical.cc
    Component/PlayerInfo.cc
    Component/Projectile.cc
    System/CollisionDetector.cc
    System/CollisionResolver.cc
    System/Damage.cc
    System/DropCollector.cc
    System/MapBoundaries.cc
    System/MobAi.cc
    System/Velocity.cc
    System/PetalBehavior.cc
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

set(CMAKE_CXX_FLAGS "-std=c++20 -DSERVER_BUILD")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

# release by default
if(DEBUG_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gdwarf-4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRROLF_DISABLE_ASSERTIONS -O3")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if(RIVET_PRODUCTION_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRIVET_PRODUCTION_BUILD")
endif()

if(RIVET_DEVELOPER_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRIVET_DEVELOPER_BUILD")
endif()

add_executable(rrolf-server ${SOURCES})

target_link_libraries(rrolf-server websockets)
target_link_libraries(rrolf-server pthread)

if(WINDOWS)
    target_link_libraries(rrolf-server ws2_32 wsock32)
endif()

if (RIVET_PRODUCTION_BUILD OR RIVET_DEVELOPER_BUILD)
    target_link_libraries(rrolf-server curl)
endif()
