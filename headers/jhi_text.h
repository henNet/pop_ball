//****************************************************************************
//*  This file contains functions structure Text.					 		 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#ifndef JHI_TEXT_H
#define JHI_TEXT_H
/**
 *  \file		jhi_text.h
 *  \brief	   	This file contains functions and structures of the Text.
 *
 */
#include "jhi_font.h"
#include "jhi_colorsSt.h"
#include "jhi_shapes.h"
#include "SDL/SDL.h"

/**
 * \brief Structure of configuration of the Text
 */
typedef struct {
	JHI_Point2d pos;		/**< Position of text		   */
	SDL_Surface *sur;	/**< SDL Surface of the Window */
}JHI_Text;


/**
 * \brief Init the Text structure
 * \param text Text structure to be initialized
 */
void jhi_init_text(JHI_Text *text);

/**
* \brief Set the Text with the configurations
*
* \param font			Font of the Text
* \param text			Text to be configured
* \param color			Color of the Text
* \param txt			String to the Text
*/
void jhi_set_text(JHI_Font *font, JHI_Text *text, JHI_Color cor, const char *txt);

/**
* \brief Free memory of the Text strucure
*/
void jhi_free_text(JHI_Text *text);

/**
* \brief Get the Text width
* \param text 			Text Structure
* \return Text width
*/
int jhi_get_text_width(JHI_Text *text);
/**
* \brief Get the Text height
* \param text			Text Structure
* \return Text height
*/
int jhi_get_text_height(JHI_Text *text);

/**
* \brief Draw the text in the window
* \param text			Text Structure
* \param point			New text position
*/
void jhi_draw_text(JHI_Text *text, JHI_Point2d point);

void jhi_set_alpha_text(JHI_Text *txt, int alpha);

#endif
