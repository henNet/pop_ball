//****************************************************************************
//*  This file contains shapes functions of libjhi-sdl    				 	 *
//*  	 	 									 			 				 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#ifndef JHI_SHAPES_H
#define JHI_SHAPES_H

#include "jhi_window.h"
#include "jhi_colorsSt.h"
#include "jhi_list.h"
#include "jhi_rand.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <math.h>

#define PI 3.1415
#define E 2.718


/**
 *  \file		jhi_shapes.h
 *  \brief	   	This file contains shapes functions of libjhi-sdl
 */


/**
 * \brief Point that contain position (x,y)
 */
typedef struct {
	int x;			/**<X position*/
	int y;			/**<Y position*/
}JHI_Point2d;

typedef enum {
	DEFAULT_DIST = 0,
	NORMAL_DIST = 1,
	EXPO_DIST = 2,
}DistFunction;

typedef struct {
	int (*f)(double, int, double);
}DistFunctionsMap;

/**
 * \brief draw point in the window
 * \param point point position
 * \param col point color
 */
void jhi_draw_point(JHI_Point2d point, JHI_Color col);

/**
* \brief Drawning a line in the screen
*
* \param s_point	Source point of the line
* \param d_point	Destination point of the line
* \param col		Line Color
*/
void jhi_draw_line(JHI_Point2d s_point, JHI_Point2d d_point, JHI_Color col);

/**
* \brief Draw a rectangle or square in the screen
*
* \param point		Upper left point of the rect
* \param height		Rect's height
* \param base		Rect's base
* \param col		Rect's Color
*/
void jhi_draw_rect(JHI_Point2d point, int height, int base, JHI_Color col);

/**
* \brief Draw a fill rectangle or square in the screen
*
* \param point		Upper left point of the rect
* \param height		Rect's height
* \param base		Rect's base
* \param col		Rect's Color
*/
void jhi_draw_fill_rect(JHI_Point2d point, int height, int base, JHI_Color col);

/**
* \brief Drawning a cirle in the screen
*
* \param center_point		Center point of the circle center
* \param radius				Circle's radius
* \param col				Circle's color
*/
void jhi_draw_circle(JHI_Point2d center_point, float radius, JHI_Color col);

/**
* \brief Draw a fill cirle in the screen
*
* \param center_point		Center point of the circle center
* \param radius				Circle's radius
* \param col				Circle's color
*/
void jhi_draw_fill_circle(JHI_Point2d center_point, int radius, JHI_Color col);

/**
* \brief Draw a Polygon in the screen
*
* \param points	Set of the Polygon's points
* \param num_points Number of points of the polygon
* \parma color	Color of the Polygon's lines
*/
void jhi_draw_polygon(JHI_Point2d *points, int num_points, JHI_Color col);

/**
 * \brief Checks whether the objects collide
 * \param p1 Point of object 1
 * \param h1 Height of object 1
 * \param w1 Weight of object 1
 * \param p2 Point of object 2
 * \param h2 Height of object 2
 * \param w2 Weight of object 2
 * \return 1 colid, 0 otherwise
 */
int jhi_is_colid(JHI_Point2d p1, int h1, int w1, JHI_Point2d p2, int h2, int w2);

/**
 * \brief Get the central position of object in the window
 * \param win_w Width of the window
 * \param win_h Height of the windows
 * \param obj_w Object's width
 * \param obj_h Object's height
 * \return Central position for this object
 */
JHI_Point2d jhi_get_central_pos(int win_w, int win_h, int obj_w, int obj_h);

/**
 * \brief Get the struct JHI_Point2 by (x,y)
 * \param x x pos
 * \param y y pos
 * \param point
 */
JHI_Point2d jhi_get_point(int x, int y);

int jhi_dist_default(double v, int max, double lambda);
int jhi_dist_normal(double v, int max, double lambda);
int jhi_dist_expo(double v, int max, double lambda);

static const DistFunctionsMap dist_funcs[] = {
		{.f = jhi_dist_default},
		{.f = jhi_dist_normal},
		{.f = jhi_dist_expo}
};

void jhi_transition_square_color(JHI_Color color, DistFunction dist, int length, double lambda);

void jhi_transition_circle_color(JHI_Color color, DistFunction dist, int length, double lambda);



#endif
