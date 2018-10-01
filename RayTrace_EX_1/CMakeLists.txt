cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_compile_options(-std=c++11)
project(dragon)

SET(DRAGON_SOURCE
src/main.cpp
)
SET(DRAGON_HEADERS
src/light.h
src/scene.h
src/object.h
src/camera.h
src/math.h
src/transform.h
src/primitive.h
src/integrator.h
src/material.h
src/utility.h
)
add_executable(
dragon
${DRAGON_SOURCE}
${DRAGON_HEADERS}
)
