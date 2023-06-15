set(CMAKE_SYSTEM_NAME Generic)

cmake_minimum_required(VERSION 3.16)

project(rrolf-server)
include_directories(..)
if (WINDOWS)
    include_directories(/c/libwebsockets)
    include_directories(/c/libwebsockets/include)
    include_directories(/c/openssl/include)
    include_directories(/c/libwebsockets/win32port/win32helpers)
endif()

set(SRCS
    System/Ai.c
    System/Centipede.c
    System/CollisionDetection.c
    System/CollisionResolution.c
    System/Drops.c
    System/Health.c
    System/MapBoundary.c
    System/PetalBehavior.c
    System/Respawn.c
    System/Velocity.c
    Main.c
    Client.c
    Logs.c
    Server.c
    Simulation.c
    SpatialHash.c
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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRR_SERVER=1 -DHSHG_D=2 -DHSHG_UNIFORM=1")
set(CMAKE_C_COMPILER "clang")

# release by default
if(DEBUG_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g3 -gdwarf-4")
    if (WINDOWS)
    else()
        add_compile_options(-fsanitize=undefined,address)
        add_link_options(-fsanitize=undefined,address)
    endif()
elseif(CALLGRIND_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG -gdwarf-4 -DHSHG_NDEBUG -march=native")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG -Ofast -DHSHG_NDEBUG")
    # link time optimiations
    if(WINDOWS)
    else()
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
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
target_link_libraries(rrolf-server pthread websockets m)

if (NUSE_CURL)
else()
    target_link_libraries(rrolf-server curl)
endif()
