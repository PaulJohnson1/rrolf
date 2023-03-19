project(rrolf-server)
cmake_minimum_required(VERSION 3.24)

include_directories(src)
include_directories(ThirdParty)

set(SOURCES
    src/Entity/Component/Physics.cc
    src/Entity/Component/Position.cc
    src/Entity/Entity.cc
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

add_executable(rrolf-server ${SOURCES})
