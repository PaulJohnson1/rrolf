project(rrolf-client)
cmake_minimum_required(VERSION 3.16)
include_directories(..)

set(SRCS
    Main.c
    Renderer.c
)

# release by default
if(DEBUG_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-4")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if (WASM_BUILD)
    set(CMAKE_C_COMPILER "emcc")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s EXPORTED_FUNCTIONS=_rr_renderer_main_loop,_main")
endif()

add_executable(rrolf-client ${SRCS})