cmake_minimum_required(VERSION 3.2)
project(piskvorky)

set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    graphics/CheckBox.cpp
    graphics/CheckBox.h
    graphics/Component.cpp
    graphics/Component.h
    graphics/Container.cpp
    graphics/Container.h
    graphics/Font.cpp
    graphics/Font.h
    graphics/Input.cpp
    graphics/Input.h
    graphics/Text.cpp
    graphics/Text.h
    graphics/Window.cpp
    graphics/Window.h
    states/AbstractGameState.cpp
    states/AbstractGameState.h
    states/MainMenuState.cpp
    states/MainMenuState.h
    states/PiskvorkyState.cpp
    states/PiskvorkyState.h
    states/SettingsState.cpp
    states/SettingsState.h
    Game.cpp
    Game.h
    Gfx.cpp
    Gfx.h
    main.cpp Player.cpp Player.h MoveListener.h NormalPlayer.cpp NormalPlayer.h Action.h Action.cpp Action.h AIPlayer.cpp AIPlayer.h NetworkPlayer.cpp NetworkPlayer.h Time.cpp Time.h StatsPanel.cpp StatsPanel.h)

add_executable(piskvorky ${SOURCE_FILES})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf)
find_package( Boost REQUIRED COMPONENTS program_options )

INCLUDE_DIRECTORIES(
	${SDL2_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)
TARGET_LINK_LIBRARIES(piskvorky ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY})