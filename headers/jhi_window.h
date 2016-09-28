//****************************************************************************
//*  This file contains functions related to Window.						 *
//*	 			 															 *
//*	                                                          				 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#ifndef JHI_WINDOW_H
#define JHI_WINDOW_H
/**
 *  \file		jhi_window.h
 *  \brief	   	This file contains functions related to Window.
 */
#include "SDL/SDL_mixer.h"
#include "jhi_colorsSt.h"
#include "jhi_keyboard.h"
#include "jhi_mouse.h"
#include "jhi_joystick.h"
#include <stdio.h>

#define JHI_CLOSE 1
#define JHI_NOT_CLOSE 0
#define NUMBER_MAX_EVENTS 100

/**
 * \brief Struct of configuration of the Window
 *
 */
typedef struct{
	SDL_Surface *screen;					/**< SDL Surface of the Window. */
	char check_quit;						/**< Flag that indicate if the Window was close*/
	SDL_Event event;						/**< SDL event struct*/
	JHI_Color back_color;					/**< Background color of the Window*/
	JHI_MouseSt mouse[NUMBER_MAX_EVENTS];	/**< Vector to mouse status for each event captured*/
	JHI_KeyboardSt key[NUMBER_MAX_EVENTS];	/**< Vector to keyboard status for each event captured*/
	JHI_JoystickSt joy[NUMBER_MAX_EVENTS];	/**< Vector to joystick status for each event captured*/
	int number_of_events;					/**< Number of events captured in the iteration*/
	int width;								/**< Width of the Window*/
	int height;								/**< Height of the Window*/
}JHI_Window;


/**
* \brief Check if (x,y) are in valid position inside of the Window
*
* \param x		Coordinate x
* \param y		Coordinate y
* \return 1 if is out, 0 otherwise
*/
int jhi_out_window(int x, int y);

/**
* \brief Initialize configurations of the Window
*
* \param width	Width of the Window
* \param height	Height of the Window
* \param bitperpixel Number of the bits by pixel
* \param back_color	Background color of the Window
*/
void jhi_initialize_window(int width, int height, int bitperpixel, JHI_Color back_color);

/**
* \brief Draw a pixel in the screen
*
* \param x		Coordinate x of the pixel
* \param y		Coordinate y of the pixel
* \param color	Color of the pixel
*/
void jhi_print_pixel(int x, int y, JHI_Color col);

SDL_Surface* jhi_get_window_screen();

/**
 * \brief Draw object in the window
 * \param object Object to draw
 */
void jhi_draw_object(SDL_Surface *object, int x, int y);


/**
* \brief Draw a cut/clip of an image in the screen
* \param object		Object to draw
* \param x			Coordinate x to clip object in the screen
* \param y			Coordinate y to to clip object in the screen
* \param x_clip		x position initial of clip
* \param y_clip		y position initial of clip
* \param width		Width of this clip
* \param height		Height of this clip
*/
void jhi_draw_object_with_clip(SDL_Surface *object, int x, int y, int x_clip, int y_clip,
		int width, int height);

/**
* \brief Set the name of the Window
*
* \param win_name	Name of the Window
*/
void jhi_choice_window_name(const char *win_name);

/**
* \brief Initialize structs of the mouse, keyboard and joystick
*
*/
void jhi_init_mouse_keyboard_joystick_events();

/**
* \brief Return the number of events captured in the iteration
*
* \return Number of events captured in the iteration
*/
int jhi_get_number_of_events();

/**
* \brief Capture the events of iteration and updates the Window
*/
void jhi_update();

/**
* \brief Set the background color with the color especified
*
*  \param back_color	Color to fill the background
*/
void jhi_set_background_color(JHI_Color back_color);

/**
* \brief Clean the Window with the background color
*/
void jhi_clean();

/**
* \brief Get if close the Window
* \return NOT_CLOSE, case this Window wasn't closed, CLOSE otherwise
*/
char jhi_get_close_window();

/**
* \brief Get status of the mouse input
* \param i			Number of event
* \return Mouse status
*/
JHI_MouseSt jhi_get_mouse_status(int i);

/**
* \brief Get status of the keyboard input
* \param i			Number of event
* \return keyboard status
*/
JHI_KeyboardSt jhi_get_keyboard_status(int i);

/**
* \brief 	Get status of the joystick input
* \param i	Number of event
* \return 	keyboard status
*/
JHI_JoystickSt jhi_get_joystick_status(int i);

/**
* \brief Free structure of the Window
*/
void jhi_quit_and_free();

/**
 * \brief Get the height of the window
 * \return height of the window
 */
int jhi_get_height_window();

/**
 * \brief Get the height of the window
 * \return height of the window
 */
int jhi_get_width_window();


#endif
