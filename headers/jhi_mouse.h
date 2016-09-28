#ifndef JHI_MOUSE_H
#define JHI_MOUSE_H

#include "SDL/SDL.h"

//****************************************************************************
//*  This file contains structures of mouse	 	 							 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/


/**
 *  \file		jhi_mouse.h
 *  \brief	   	This file contains structure of the mouse.
 *
 */


/**
 * \brief Enumeration of the events of the mouse
 */
typedef enum {
	ON_CLICK_RIGHT,				/**< Click of right button*/
	ON_CLICK_LEFT,				/**< Click of left button*/
	MOUSE_MOTION,				/**< Mouse was moved*/
	MOUSE_NOT_EVENT,			/**< Nothing Event*/
}JHI_MouseEvents;

/**
 * \brief Mouse structure
 */
typedef struct {
	int x;									/**< Coordinate x of the mouse*/
	int y;									/**< Coordinate y of the mouse*/
	JHI_MouseEvents mouse_event;			/**< Mouse event that was captured*/
}JHI_MouseSt;


/**
 * \brief Initalize the mouse structure
 * \param mouse the scructure mouse to configure
 */
void jhi_init_mouse(JHI_MouseSt *mouse);


/**
 * \brief Check if the mouse is in the space object
 * \param xp x of object
 * \param yp y of object
 * \param w width of the object
 * \param h height of the object
 * \return 1 ok, 0 otherwise
 */
int jhi_check_mouse_is_in(JHI_MouseSt mouse, int xp, int yp, int w, int h);

#endif
