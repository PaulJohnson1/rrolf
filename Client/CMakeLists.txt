project(rrolf-client)
cmake_minimum_required(VERSION 3.24)

include_directories(src)
include_directories(ThirdParty)

set(SOURCES
    src/Main.cc
    src/Socket.cc
)

# set(CMAKE_CXX_FLAGS "-std=c++17 -g -DWASM_BUILD -sEXPORTED_FUNCTIONS=_main,_malloc,_free,_OnMessage,_OnOpen,_OnClose")
# set(CMAKE_CXX_COMPILER "em++")

set(CMAKE_CXX_FLAGS "-std=c++17 -g -lcrypto -lssl")
set(CMAKE_CXX_COMPILER "clang++")

add_executable(rrolf-client ${SOURCES})
