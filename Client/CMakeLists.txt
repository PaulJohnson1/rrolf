project(rrolf-client)
cmake_minimum_required(VERSION 3.16)
include_directories(..)

set(SRCS
    Main.c
    Renderer.c
)

set(CMAKE_C_COMPILER "clang")

# release by default
if(DEBUG_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-4")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()


add_executable(rrolf-client ${SRCS})