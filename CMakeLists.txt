
cmake_minimum_required (VERSION 2.6)
project (netgame)

SET(CMAKE_BUILD_TYPE "Release")

SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x -O3 -g -pthread")

SET(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET(INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dist)

include_directories(../libmaudit)

find_program(RAGEL ragel)

add_custom_command(
  OUTPUT configparser.h
  COMMAND ${RAGEL} -G2 -o configparser.h configparser.rl
  DEPENDS configparser.rl
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(netgame netgame.cc
                       talgo/bresenham_c.c 
                       talgo/fov_circular_raycasting.c 
                       talgo/fov_permissive2.c              
                       talgo/fov_restrictive.c 
                       talgo/fov_c.c 
                       talgo/fov_diamond_raycasting.c 
                       talgo/fov_recursive_shadowcasting.c 
                       talgo/path_c.c 
                       talgo/list_c.c
)

add_custom_target(configparserh DEPENDS configparser.h)
add_dependencies(netgame configparserh)

target_link_libraries(netgame m)

