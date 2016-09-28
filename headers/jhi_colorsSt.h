//****************************************************************************
//*  This file contains structures and enumeration of the Colors     		 *
//*  	 	 									 			 				 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#ifndef JHI_COLORS_H
#define JHI_COLORS_H

#include "SDL/SDL.h"

/**
 *  \file		jhi_colorsSt.h
 *  \brief	   	This file contains structures and enumeration of the Colors
 */



/**
 * \brief Enumeration of the possibles colors for this lib
 */
typedef enum {
	RED,
	GREEN,
	BLUE,
	YELLOW,
	BLACK,
	WHITE,
	ORANGE
	//MYNEWCOLOR put commas in the previos color
}JHI_Color;

/**
 * \brief Structure of the RGB color
 */
typedef struct {
	Uint8 r;			/**<Red value to color*/
	Uint8 g;			/**<Green value to color*/
	Uint8 b;			/**<Blue value to color*/
}JHI_Color_RGB;

/*
This variable maps the values ​​of the enumeration Color for a ColorRGB value. If you
want to include a new color, just include the values ​​in this variable and its value
ot the corresponding enumeration */
static const JHI_Color_RGB colors[] = {
{.r = 255, .g = 0, .b = 0},	//RED
{.r = 0, .g = 255, .b = 0},	//GREEN
{.r = 0, .g = 0, .b = 255},	//BLUE
{.r = 255, .g = 255, .b = 0},	//YELLOW
{.r = 0, .g = 0, .b = 0},	//BLACK
{.r = 255, .g = 255, .b = 255},	//WHITE
{.r = 255, .g = 165, .b = 0}	//ORANGE
//Example to include new color:
//{.r = myvalue_r, .g = myvalue_g, .b = myvalue_b} //MYNEWCOLOR
};

#endif
