
cmake_minimum_required (VERSION 2.6)
project (incavead)

SET(CMAKE_BUILD_TYPE "Release")

#SET (CMAKE_C_COMPILER   "/usr/bin/clang")
#SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
#SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x -O3 -g -pthread -stdlib=libc++ -nostdinc++ -I/home/itkachev/libc++/include/c++/v1/ -L/home/itkachev/libc++/lib/")

SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x -O4 -g -pthread")

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

add_executable(incavead incavead.cc
                       talgo/bresenham_c.c
                       talgo/fov_c.c 
                       talgo/path_c.c 
                       talgo/list_c.c
)

add_custom_target(configparserh DEPENDS configparser.h)
add_dependencies(incavead configparserh)

target_link_libraries(incavead m)

