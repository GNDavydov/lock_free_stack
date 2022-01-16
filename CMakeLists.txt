cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

option(BUILD_EXAMPLES "Build examples" ON)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
        SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

project(LockFreeStack VERSION 0.1.0)

hunter_add_package(GTest)
find_package(GTest)


add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE .)

if(BUILD_EXAMPLES)
    add_executable(examples
            ${CMAKE_CURRENT_SOURCE_DIR}/examples/example.cpp
            )
    target_link_libraries(examples ${PROJECT_NAME})
endif()