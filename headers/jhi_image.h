//****************************************************************************
//*  This file contains functions structure of the Image.		 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#ifndef JHI_IMAGE_H
#define JHI_IMAGE_H

/**
 *  \file		jhi_image.h
 *  \brief	   	This file contains functions structure of the Image.
 */
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "jhi_colorsSt.h"
#include "jhi_shapes.h"
#include <stdio.h>

#define JHI_MAX_ALPHA SDL_ALPHA_OPAQUE
#define JHI_MIN_ALPHA SDL_ALPHA_TRANSPARENT

/**
 * \brief Structure of configuration of the Image
 */
typedef struct {
	JHI_Point2d	pos;			/**< Image's position			*/
	SDL_Surface *sur;			/**< SDL Surface of the Window. */
}JHI_Image;


/**
 * \brief Load the Image with the filename
 * \param img				Structure of Image to load
 * \param filename			Name of the music file
 */
void jhi_load_image(JHI_Image *img, const char *filename);

/**
 * \brief Load the Image with the filename and that will be transparent in the Image
 * \param img				Structure of the image to load
 * \param filename			Name of the music file
 * \param cor				Transparent color in the image
 */
void jhi_load_image_with_transparent_color(JHI_Image *img, const char *filename, JHI_Color col);

/**
 * \brief Free image structure
 */
void jhi_free_image(JHI_Image *img);

/**
* \brief Get the Image width
* \param img	Image Structure
* \return Image width
*/
int jhi_get_image_width(JHI_Image *img);

/**
* \brief Get the Image height
* \param img	Image Structure
* \return Image height
*/
int jhi_get_image_height(JHI_Image *img);

/**
* \brief resize the image
* \param img Image Structure
* \param width the new width for image
* \param width the new height for image
*/
void jhi_resize_image(JHI_Image *img, int width, int height);

/**
* \brief Draw image in the window
* \param img Image Structure
* \param point new pos of the image
*/
void jhi_draw_image(JHI_Image *img, JHI_Point2d point);

/**
* \brief Draw clip image in the window
* \param img 		Image Structure
* \param point 		new pos of the clip image
* \param width		Width of this clip
* \param height		Height of this clip
*/
void jhi_draw_image_with_clip(JHI_Image *img, JHI_Point2d point_position, JHI_Point2d point_clip,
		int width, int height);

void jhi_set_alpha_image(JHI_Image *img, int alpha);

#endif
