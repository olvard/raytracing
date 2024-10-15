cmake_minimum_required(VERSION 3.29)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(raytracer main.cpp
        scene.h
        camera.cpp
        camera.h
        colorDBL.h
        scene.cpp
        ray.cpp
        ray.h
        light.cpp
        light.h
        shape.cpp
        shape.h
)
