cmake_minimum_required(VERSION 3.16)
project(maze_generator VERSION 1.0 LANGUAGES CXX)

find_package(SDL3 REQUIRED CONFIG)

add_executable(maze_generator
  ./src/main.cpp
  ./src/maze_functions.cpp
  ./src/render.cpp
  ./src/modes.cpp
)
target_link_libraries(maze_generator PRIVATE SDL3::SDL3)


set_target_properties(maze_generator PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)
