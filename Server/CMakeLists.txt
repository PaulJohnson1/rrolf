project(rrolf-server)
cmake_minimum_required(VERSION 3.24)

include_directories(src)
include_directories(ThirdParty)

set(SOURCES
    src/Component/Flower.cc
    src/Component/Life.cc
    src/Component/Physical.cc
    src/Component/Render.cc
    src/System/CollisionDetector.cc
    src/System/CollisionResolver.cc
    src/System/Velocity.cc
    src/Client.cc
    src/Main.cc
    src/Server.cc
    src/Simulation.cc
    src/SpatialHash.cc
    src/Vector.cc
    ThirdParty/BinaryCoder/BinaryCoder.cc
    ThirdParty/BinaryCoder/NativeTypes.cc
    )

set(CMAKE_CXX_FLAGS "-std=c++17 -g")
set(CMAKE_CXX_COMPILER "clang++")

add_executable(rrolf-server ${SOURCES})
