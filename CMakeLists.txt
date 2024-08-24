cmake_minimum_required(VERSION 3.29)
project(rt_weekend)

set(CMAKE_CXX_STANDARD 20)

add_executable(rt_weekend main.cpp
        vec3.h
        color.h
        ray.cpp
        ray.h
        hittable.cpp
        hittable.h
        sphere.cpp
        sphere.h
        hittable_list.cpp
        hittable_list.h
        rtweekend.h
)
