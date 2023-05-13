project(rrolf-server)
cmake_minimum_required(VERSION 3.16)
include_directories(..)

set(SRCS
    Main.c
    Simulation.c
    ../Shared/Component/Physical.c
    ../Shared/BinaryEncoder.c
    ../Shared/Vector.c)


set(CMAKE_C_FLAGS "-std=c99 -DSERVER_BUILD")
set(CMAKE_C_COMPILER "clang")

# release by default
if(DEBUG_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-4")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG -O3")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if(RIVET_PRODUCTION_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRIVET_PRODUCTION_BUILD")
endif()

if(RIVET_DEVELOPER_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRIVET_DEVELOPER_BUILD")
endif()

add_executable(rrolf-server ${SRCS})

target_link_libraries(rrolf-server websockets)
target_link_libraries(rrolf-server pthread)

if(WINDOWS)
    target_link_libraries(rrolf-server ws2_32 wsock32)
endif()

if (RIVET_PRODUCTION_BUILD OR RIVET_DEVELOPER_BUILD)
    target_link_libraries(rrolf-server curl)
endif()
