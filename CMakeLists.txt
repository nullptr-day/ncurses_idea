cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

if(Curses_FOUND AND NOT TARGET Curses::Curses)
    add_library(Curses::Curses INTERFACE IMPORTED)
    set_target_properties(
            Curses::Curses
            PROPERTIES
            INTERFACE_LINK_LIBRARIES "${CURSES_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${CURSES_INCLUDE_DIRS}"
    )
endif()

add_executable(untitled main.cpp
        OutputPad.cpp
        OutputPad.h
        InputBox.cpp
        InputBox.h
        StatusBar.cpp
        StatusBar.h)
target_link_libraries(untitled PRIVATE Curses::Curses)
