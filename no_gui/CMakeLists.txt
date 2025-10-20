cmake_minimum_required(VERSION 3.10)
project(InstaCheckerNoGUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(InstaCheckerNoGUI main_no_gui.cpp)

if(MINGW OR MSYS)
    message(STATUS "Building statically for Windows (MinGW/MSYS)")
    target_link_options(InstaCheckerNoGUI PRIVATE -static -static-libgcc -static-libstdc++)
endif()
