

include_directories(../libtcod/include)
include_directories(../libmaudit)

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

target_link_libraries(netgame m)

