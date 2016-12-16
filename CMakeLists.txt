cmake_minimum_required(VERSION 2.8)

project(StayAlive)

FILE(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(
    StayAlive
    ${SOURCE_FILES}
    deps/glew/src/glew.c)

target_compile_features(StayAlive PRIVATE cxx_range_for)

add_subdirectory(deps/glfw)
include_directories(deps/glew/include)
include_directories(deps/glfw/include)
include_directories(deps/glm)

if(MINGW)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
        "C:/Program Files/CURL/lib" "C:/Program Files (x86)/CURL/lib")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH}
        "C:/Program Files/CURL/include" "C:/Program Files (x86)/CURL/include")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

if(APPLE)
    target_link_libraries(StayAlive glfw
        ${GLFW_LIBRARIES})
endif()

if(UNIX)
    target_link_libraries(StayAlive dl glfw
        ${GLFW_LIBRARIES})
endif()

if(MINGW)
    target_link_libraries(StayAlive ws2_32.lib glfw
        ${GLFW_LIBRARIES})
endif()
