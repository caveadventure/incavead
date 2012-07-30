/*
* libtcod 1.5.1
* Copyright (c) 2008,2009,2010 Jice & Mingos
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The name of Jice or Mingos may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY JICE AND MINGOS ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL JICE OR MINGOS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _TALGO_H
#define _TALGO_H

#include <stdint.h>



/* bool support for C */
#ifndef __cplusplus
#ifndef bool
typedef unsigned int bool;
#define false ((bool)0)
#define true ((bool)1)
#endif
#endif


typedef void *TCOD_map_t;

/* FOV_BASIC : http://roguebasin.roguelikedevelopment.org/index.php?title=Ray_casting
   FOV_DIAMOND : http://www.geocities.com/temerra/los_rays.html
   FOV_SHADOW : http://roguebasin.roguelikedevelopment.org/index.php?title=FOV_using_recursive_shadowcasting
   FOV_PERMISSIVE : http://roguebasin.roguelikedevelopment.org/index.php?title=Precise_Permissive_Field_of_View
   FOV_RESTRICTIVE : Mingos' Restrictive Precise Angle Shadowcasting (contribution by Mingos) */

typedef enum {
        FOV_BASIC,
        FOV_DIAMOND,
        FOV_SHADOW,
        FOV_PERMISSIVE_0,
        FOV_PERMISSIVE_1,
        FOV_PERMISSIVE_2,
        FOV_PERMISSIVE_3,
        FOV_PERMISSIVE_4,
        FOV_PERMISSIVE_5,
        FOV_PERMISSIVE_6,
        FOV_PERMISSIVE_7,
        FOV_PERMISSIVE_8,
        FOV_RESTRICTIVE,
        NB_FOV_ALGORITHMS } TCOD_fov_algorithm_t;
#define FOV_PERMISSIVE(x) ((TCOD_fov_algorithm_t)(FOV_PERMISSIVE_0 + (x)))

/* allocate a new map */
TCOD_map_t TCOD_map_new(int width, int height);

/* set all cells as solid rock (cannot see through nor walk) */
void TCOD_map_clear(TCOD_map_t map, bool transparent, bool walkable);

/* copy a map to another, reallocating it when needed */
void TCOD_map_copy(TCOD_map_t source, TCOD_map_t dest);

/* change a cell properties */
void TCOD_map_set_properties(TCOD_map_t map, int x, int y, bool is_transparent, bool is_walkable);

/* destroy a map */
void TCOD_map_delete(TCOD_map_t map);

/* calculate the field of view (potentially visible cells from player_x,player_y) */
void TCOD_map_compute_fov(TCOD_map_t map, int player_x, int player_y, int max_radius, bool light_walls, TCOD_fov_algorithm_t algo);

/* check if a cell is in the last computed field of view */
bool TCOD_map_is_in_fov(TCOD_map_t map, int x, int y);
void TCOD_map_set_in_fov(TCOD_map_t map, int x, int y, bool fov);

/* retrieve properties from the map */
bool TCOD_map_is_transparent(TCOD_map_t map, int x, int y);
bool TCOD_map_is_walkable(TCOD_map_t map, int x, int y);
int TCOD_map_get_width(TCOD_map_t map);
int TCOD_map_get_height(TCOD_map_t map);
int TCOD_map_get_nb_cells(TCOD_map_t map);

/***************************************************************/

typedef bool (*TCOD_line_listener_t) (int x, int y);

void TCOD_line_init(int xFrom, int yFrom, int xTo, int yTo);
bool TCOD_line_step(int *xCur, int *yCur); /* advance one step. returns true if we reach destination */

/* atomic callback function. Stops when the callback returns false */
bool TCOD_line(int xFrom, int yFrom, int xTo, int yTo, TCOD_line_listener_t listener);

/* thread-safe versions */
typedef struct {
        int stepx;
        int stepy;
        int e;
        int deltax;
        int deltay;
        int origx; 
        int origy; 
        int destx; 
        int desty; 
} TCOD_bresenham_data_t;

void TCOD_line_init_mt(int xFrom, int yFrom, int xTo, int yTo, TCOD_bresenham_data_t *data);
bool TCOD_line_step_mt(int *xCur, int *yCur, TCOD_bresenham_data_t *data);
bool TCOD_line_mt(int xFrom, int yFrom, int xTo, int yTo, TCOD_line_listener_t listener, TCOD_bresenham_data_t *data);

/***************************************************************/

typedef float (*TCOD_path_func_t)( int xFrom, int yFrom, int xTo, int yTo, void *user_data );
typedef void *TCOD_path_t;

TCOD_path_t TCOD_path_new_using_map(TCOD_map_t map, float diagonalCost);
TCOD_path_t TCOD_path_new_using_function(int map_width, int map_height, TCOD_path_func_t func, void *user_data, float diagonalCost);
bool TCOD_path_compute(TCOD_path_t path, int ox,int oy, int dx, int dy, int cutoff);
bool TCOD_path_walk(TCOD_path_t path, int *x, int *y, bool recalculate_when_needed, int cutoff);
bool TCOD_path_is_empty(TCOD_path_t path);
int TCOD_path_size(TCOD_path_t path);
void TCOD_path_reverse(TCOD_path_t path);
void TCOD_path_get(TCOD_path_t path, int index, int *x, int *y);
void TCOD_path_get_origin(TCOD_path_t path, int *x, int *y);
void TCOD_path_get_destination(TCOD_path_t path, int *x, int *y);
void TCOD_path_delete(TCOD_path_t path);


/* Dijkstra stuff - by Mingos*/

typedef void *TCOD_dijkstra_t;

TCOD_dijkstra_t TCOD_dijkstra_new (TCOD_map_t map, float diagonalCost);
TCOD_dijkstra_t TCOD_dijkstra_new_using_function(int map_width, int map_height, TCOD_path_func_t func, void *user_data, float diagonalCost);
void TCOD_dijkstra_compute (TCOD_dijkstra_t dijkstra, int root_x, int root_y);
float TCOD_dijkstra_get_distance (TCOD_dijkstra_t dijkstra, int x, int y);
bool TCOD_dijkstra_path_set (TCOD_dijkstra_t dijkstra, int x, int y);
bool TCOD_dijkstra_is_empty(TCOD_dijkstra_t path);
int TCOD_dijkstra_size(TCOD_dijkstra_t path);
void TCOD_dijkstra_reverse(TCOD_dijkstra_t path);
void TCOD_dijkstra_get(TCOD_dijkstra_t path, int index, int *x, int *y);
bool TCOD_dijkstra_path_walk (TCOD_dijkstra_t dijkstra, int *x, int *y);
void TCOD_dijkstra_delete (TCOD_dijkstra_t dijkstra);

typedef void *TCOD_list_t;

TCOD_list_t TCOD_list_new();
TCOD_list_t TCOD_list_allocate(int nb_elements);
TCOD_list_t TCOD_list_duplicate(TCOD_list_t l);
void TCOD_list_delete(TCOD_list_t l);
void TCOD_list_push(TCOD_list_t l, const void * elt);
void * TCOD_list_pop(TCOD_list_t l);
void * TCOD_list_peek(TCOD_list_t l);
void TCOD_list_add_all(TCOD_list_t l, TCOD_list_t l2);
void * TCOD_list_get(TCOD_list_t l,int idx);
void TCOD_list_set(TCOD_list_t l,const void *elt, int idx);
void ** TCOD_list_begin(TCOD_list_t l);
void ** TCOD_list_end(TCOD_list_t l);
void TCOD_list_reverse(TCOD_list_t l);
void **TCOD_list_remove_iterator(TCOD_list_t l, void **elt);
void TCOD_list_remove(TCOD_list_t l, const void * elt);
void **TCOD_list_remove_iterator_fast(TCOD_list_t l, void **elt);
void TCOD_list_remove_fast(TCOD_list_t l, const void * elt);
bool TCOD_list_contains(TCOD_list_t l,const void * elt);
void TCOD_list_clear(TCOD_list_t l);
void TCOD_list_clear_and_delete(TCOD_list_t l);
int TCOD_list_size(TCOD_list_t l);
void ** TCOD_list_insert_before(TCOD_list_t l,const void *elt,int before);
bool TCOD_list_is_empty(TCOD_list_t l);


#endif
