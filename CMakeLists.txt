
cmake_minimum_required (VERSION 2.6)
project (incavead)

SET(CMAKE_BUILD_TYPE "Release")

#SET (CMAKE_C_COMPILER   "/usr/bin/clang")
#SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
#SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x -O3 -g -pthread -stdlib=libc++ -nostdinc++ -I/home/itkachev/libc++/include/c++/v1/ -L/home/itkachev/libc++/lib/")

SET(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O4 -pthread -ftime-report -fmem-report")

SET(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET(INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dist)

include_directories(../libmaudit)

find_program(RAGEL ragel)

if(NOT RAGEL) 
  
  add_executable(incavead incavead.cc)

else(NOT RAGEL)

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/configparser.h
    COMMAND ${RAGEL} -G2 -o configparser.h configparser.rl
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/configparser.rl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )

  #add_custom_target(configparserh DEPENDS configparser.h)
  #set_source_files_properties(configparser.h PROPERTIES GENERATED TRUE ) 

  add_executable(incavead incavead.cc ${CMAKE_CURRENT_SOURCE_DIR}/configparser.h)

endif(NOT RAGEL)

if(WIN32)

  target_link_libraries(incavead m pthread ws2_32)

else(WIN32)

  target_link_libraries(incavead m)

endif(WIN32)

add_executable(highscore util/highscore.cc)
add_executable(victory util/victory.cc)
add_executable(printmap util/printmap.cc)

install(TARGETS incavead highscore victory DESTINATION games/incavead)
install(FILES data/celauto.cfg data/constants.cfg data/designs.cfg data/levelskins.cfg data/species.cfg data/terrain.cfg data/vaults.cfg
        DESTINATION games/incavead)

