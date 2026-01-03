cmake_minimum_required(VERSION 3.0)

project(Amela_game C)

set(CMAKE_EXPORT_COMPILE_COMMAND ON)

add_executable(Amela_game
  src/main.c
  src/both.c
  src/collision.c
  src/top_lev.c
)
target_include_directories(Amela_game PRIVATE include textures)

target_link_libraries(Amela_game PRIVATE raylib m)

