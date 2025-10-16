cmake_minimum_required(VERSION 3.10)
project(InstaChecker)

set(CMAKE_CXX_STANDARD 17)

if(MINGW)
    # Only include flags supported by all MinGW versions
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

add_executable(InstaChecker WIN32 main.cpp)
