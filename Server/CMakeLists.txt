project(rrolf-server)
cmake_minimum_required(VERSION 3.16)
include_directories(..)
if (WINDOWS)
    include_directories(/c/libwebsockets)
    include_directories(/c/libwebsockets/include)
    include_directories(/c/openssl/include)
    include_directories(/c/libwebsockets/win32port/win32helpers)
endif()

set(SRCS
    System/MapBoundary.c
    System/PetalBehavior.c
    System/Velocity.c
    Main.c
    Client.c
    Server.c
    Simulation.c
    SpatialHash.c
    ../Shared/Component/Arena.c
    ../Shared/Component/Flower.c
    ../Shared/Component/Petal.c
    ../Shared/Component/Physical.c
    ../Shared/Component/PlayerInfo.c
    ../Shared/Bitset.c
    ../Shared/Encoder.c
    ../Shared/SimulationCommon.c
    ../Shared/StaticData.c
    ../Shared/Utilities.c
    ../Shared/Vector.c
)


set(CMAKE_C_FLAGS "-std=gnu11 -DRR_SERVER -DHSHG_D=2 -DHSHG_UNIFORM")
set(CMAKE_C_COMPILER "clang")

# release by default
if(DEBUG_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-4")
    # add_compile_options(-fsanitize=undefined,address)
    # add_link_options(-fsanitize=undefined,address)
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG -O3 -DHSHG_NDEBUG")
    # link time optimiations
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if(RIVET_PRODUCTION_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRIVET_PRODUCTION_BUILD")
endif()

if(RIVET_DEVELOPER_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRIVET_DEVELOPER_BUILD")
endif()

add_executable(rrolf-server ${SRCS})

if(WINDOWS)
    target_link_directories(rrolf-server PRIVATE /c/libwebsockets/unix-build/bin)
    target_link_libraries(rrolf-server ws2_32 wsock32)
endif()
target_link_libraries(rrolf-server pthread websockets)

if(WINDOWS)
    target_link_libraries(rrolf-server ws2_32 wsock32)
endif()

if (RIVET_PRODUCTION_BUILD OR RIVET_DEVELOPER_BUILD)
    target_link_libraries(rrolf-server curl)
endif()
