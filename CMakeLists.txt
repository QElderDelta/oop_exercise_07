cmake_minimum_required(VERSION 3.1)

project(lab7)

add_executable(lab7
    main.cpp
    point.cpp
    rhombus.cpp
    pentagon.cpp
    hexagon.cpp)

set_property(TARGET lab7 PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
