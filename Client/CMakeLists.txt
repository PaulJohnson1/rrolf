set(CMAKE_SYSTEM_NAME Generic)

project(rrolf-client)
cmake_minimum_required(VERSION 3.16)

include_directories(..)
include_directories(ThirdParty)
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
    System/GameRenderer.cc
    System/Interpolation.cc
    Main.cc
    Renderer.cc
    Simulation.cc
    Socket.cc
    Ui/Button.cc
    Ui/ButtonTypes.cc
    Ui/Container.cc
    Ui/Element.cc
    Ui/MobButton.cc
    Ui/LabeledButton.cc
    Ui/PetalButton.cc
    Ui/RenderFunctions.cc
    Ui/Text.cc
    ThirdParty/BinaryCoder/BinaryCoder.cc
    ThirdParty/BinaryCoder/NativeTypes.cc
    ../Shared/HttpRequest.cc
    ../Shared/StaticData.cc
)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_FLAGS "-std=c++20 -DCLIENT_BUILD")

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


if(WASM_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS=_main,_malloc,_free,_OnMessage,_OnOpen,_OnClose,___Renderer_Render,___Renderer_KeyEvent,___Renderer_MouseEvent")
    set(CMAKE_CXX_COMPILER "em++")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto -lssl -lskia -lglfw")
    set(CMAKE_CXX_COMPILER "clang++")
    include_directories(/usr/include)
    include_directories(/usr/include/skia)
endif()
add_executable(rrolf-client ${SOURCES})
