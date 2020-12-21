cmake_minimum_required(VERSION 3.15)
project(tron CXX)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

MATH(EXPR stack_size "16 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}") # Increase stack size

#[[add_compile_options(
        -c
        -Wall
        -Wextra
        -Winit-self
        -Woverloaded-virtual
        -Wuninitialized
        -g)]]

set(SRC_TRON
        src/main.cpp
        src/wall.cpp src/wall.h
        src/menu.cpp src/menu.h
        src/player.cpp src/player.h
        src/globalParameters.h src/backGround.cpp
        src/backGround.h
        src/controller.cpp src/controller.h
        src/view.cpp src/view.h
        src/gameModel.cpp src/gameModel.h
        src/observer.h
        src/bot.cpp src/bot.h
        src/human.cpp src/human.h)


add_executable(tron ${SRC_TRON})

target_link_libraries (tron sfml-graphics sfml-window sfml-system)
