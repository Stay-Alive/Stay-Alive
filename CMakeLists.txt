cmake_minimum_required(VERSION 2.8)

project(StayAlive)

FILE(GLOB SOURCE_FILES src/*.cpp)

add_executable(
    StayAlive
    ${SOURCE_FILES}
    deps/glew/src/glew.c)

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
