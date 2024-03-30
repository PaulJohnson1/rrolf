# Copyright (C) 2024  Paul Johnson

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.

# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

set(CMAKE_SYSTEM_NAME Generic)

cmake_minimum_required(VERSION 3.16)

project(rrolf-client)
include_directories(..)

set(SRCS
    Assets/MapFeature/Fern3.c
    Assets/MapFeature/Moss.c
    Assets/MapFeature/WaterLettuce.c
    Assets/Mob/Ankylosaurus.c
    Assets/Mob/Ant.c
    Assets/Mob/Beehive.c
    Assets/Mob/Dakotaraptor.c
    Assets/Mob/Dragonfly.c
    Assets/Mob/Edmontosaurus.c
    Assets/Mob/Honeybee.c
    Assets/Mob/Hornet.c
    Assets/Mob/HouseCentipede.c
    Assets/Mob/Ornithomimus.c
    Assets/Mob/Pachycephalosaurus.c
    Assets/Mob/Pteranodon.c
    Assets/Mob/Quetzalcoatlus.c
    Assets/Mob/Rex.c
    Assets/Mob/Spider.c
    Assets/Mob/Triceratops.c
    Assets/Mob/Fern.c
    Assets/Mob/Meteor.c
    Assets/Mob/Tree.c
    Assets/Tile/Garden.c
    Assets/Tile/HellCreek.c
    Assets/Tile/Ocean.c
    Assets/Init.c
    Assets/RenderMisc.c
    Assets/RenderMobs.c
    Assets/RenderPetals.c
    Assets/RenderRarityBackground.c
    Assets/RenderText.c
    DOM.c
    Particle.c
    Renderer/Common.c
    Renderer/RenderArena.c
    Renderer/RenderDrop.c
    Renderer/RenderFlower.c
    Renderer/RenderHealth.c
    Renderer/RenderMob.c
    Renderer/RenderPetal.c
    Renderer/RenderWeb.c
    Storage.c
    System/DeletionAnimation.c
    System/Interpolation.c
    System/ParticleRender.c
    Ui/Button.c
    Ui/ChooseElement.c
    Ui/CloseButton.c
    Ui/Container.c
    Ui/Element.c
    Ui/Engine.c
    Ui/InGame/AntiAfk.c
    Ui/InGame/Chat.c
    Ui/InGame/Deathscreen.c
    Ui/InGame/Loadout.c
    Ui/InGame/Minimap.c
    Ui/InGame/PetalsCollected.c
    Ui/InGame/Squad.c
    Ui/ScrollContainer.c
    Ui/TitleScreen/Account.c
    Ui/TitleScreen/BiomeButton.c
    Ui/TitleScreen/Crafting.c
    Ui/TitleScreen/DevSquadPanel.c
    Ui/TitleScreen/Discord.c
    Ui/TitleScreen/Inventory.c
    Ui/TitleScreen/LevelBar.c
    Ui/TitleScreen/MobGallery.c
    Ui/TitleScreen/Settings.c
    Ui/TitleScreen/Squad.c
    Ui/Slider.c
    Ui/Text.c
    Ui/TextInput.c
    Ui/ToggleBox.c
    Ui/Tooltip/Petal.c
    Ui/Tooltip/Mob.c
    Ui/Tooltip/Squad.c
    Game.c
    InputData.c
    Main.c
    Mobile.c
    Simulation.c
    Socket.c
    Storage.c
    ../Shared/Api.c
    ../Shared/Binary.c
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
    ../Shared/Component/Relations.c
    ../Shared/Component/Web.c
    ../Shared/Bitset.c
    ../Shared/cJSON.c
    ../Shared/Crypto.c
    ../Shared/pb.c
    ../Shared/Rivet.c
    ../Shared/SimulationCommon.c
    ../Shared/StaticData.c
    ../Shared/Utilities.c
    ../Shared/Vector.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRR_CLIENT")
set(CMAKE_C_COMPILER "clang")

if(DEBUG_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-4")
    # add_compile_options(-fsanitize=address)
    # add_link_options(-fsanitize=address)
elseif(CALLGRIND_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG -gdwarf-4 -DHSHG_NDEBUG -march=native")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -ffast-math -DNDEBUG")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if (WASM_BUILD)
    set(CMAKE_C_COMPILER "emcc")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --closure=1 -DWASM_BUILD -s INITIAL_MEMORY=33554432 -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS=_malloc,_free,_rr_rivet_on_log_in,_rr_rivet_lobby_on_find,_rr_renderer_main_loop,_main,_rr_key_event,_rr_mouse_event,_rr_touch_event,_rr_wheel_event,_rr_paste_event,_rr_on_socket_event_emscripten,_rr_api_on_get_password")
    set(SRCS ${SRCS} Renderer/Wasm.c)
else()
    set(SRCS ${SRCS} Renderer/Native.cc)
endif()

if(RIVET_BUILD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRIVET_BUILD")
endif()

add_executable(rrolf-client ${SRCS})

if(NOT WASM_BUILD)
    target_link_libraries(rrolf-client websockets cairo curl)
endif()

target_link_libraries(rrolf-client m)
