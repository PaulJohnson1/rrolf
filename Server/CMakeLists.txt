project(rrolf-server)
cmake_minimum_required(VERSION 3.16)
include_directories(..)

set(SRCS
    System/Velocity.c
    Main.c
    Server.c
    Simulation.c
    SpatialHash.c
    ../Shared/Component/Physical.c
    ../Shared/Component/PlayerInfo.c
    ../Shared/Bitset.c
    ../Shared/Encoder.c
    ../Shared/Utilities.c
    ../Shared/Vector.c)


set(CMAKE_C_FLAGS "-std=gnu11 -DRR_SERVER -DHSHG_D=2 -DHSHG_UNIFORM")
set(CMAKE_C_COMPILER "clang")

# release by default
if(DEBUG_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-4 -D_FORTIFY_SOURCE=3")
    add_compile_options(-fsanitize=undefined,address)
    add_link_options(-fsanitize=undefined,address)
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

target_link_libraries(rrolf-server websockets pthread m)

if(WINDOWS)
    target_link_libraries(rrolf-server ws2_32 wsock32)
endif()

if (RIVET_PRODUCTION_BUILD OR RIVET_DEVELOPER_BUILD)
    target_link_libraries(rrolf-server curl)
endif()
