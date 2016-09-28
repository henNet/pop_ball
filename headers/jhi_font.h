//****************************************************************************
//*  This file contains functions structure of the Font.		 			 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#ifndef JHI_FONT_H
#define JHI_FONT_H

#include "SDL/SDL_ttf.h"
#include "jhi_shapes.h"
#include <stdio.h>
/**
 *  \file		jhi_font.h
 *  \brief	   	This file contains functions structure of the Font.
 *
 */

/**
 * \brief Structure of configuration of the Font
 */
typedef struct {
	TTF_Font *font; 		/**< SDL structure of Font*/
	int length;				/**< Length of the Font*/
}JHI_Font;

/**
 * \brief Load the music with the font_name
 * \param font				Structure of the Font to load
 * \param font_name			Name of the Font file
 * \param length			Length of the Font
 */
void jhi_load_font(JHI_Font *font, const char *font_name, int length);

/**
 * \brief Free font structure
 */
void jhi_free_font(JHI_Font *font);

/**
* \brief Get the Font length
* \return Font length
*/
int jhi_get_lenght_font(JHI_Font *font);

#endif
