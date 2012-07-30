

include_directories(../libtcod/include)
include_directories(../libmaudit)

add_executable(netgame netgame.cc
                       bresenham_c.c fov_circular_raycasting.c fov_permissive2.c              
                       fov_restrictive.c fov_c.c fov_diamond_raycasting.c 
                       fov_recursive_shadowcasting.c path_c.c list_c.c
)

target_link_libraries(netgame m)

