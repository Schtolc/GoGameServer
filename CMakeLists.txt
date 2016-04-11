cmake_minimum_required(VERSION 3.3)
project(GoGameServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


find_package(Boost 1.60.0 COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
set(SOURCE_FILES main.cpp Frontend.cpp Frontend.h Backend.cpp Backend.h )
add_executable(GoGameServer ${SOURCE_FILES})

target_link_libraries( GoGameServer ${Boost_LIBRARIES} pthread)