//****************************************************************************
//*  This file contains functions related to Joystick.						 *
//*	 			 															 *
//*	                                                          				 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#ifndef JHI_JOYSTICK_H
#define JHI_JOYSTICK_H

#include "SDL/SDL.h"

#define JHI_NUMBER_MAX_JOYSTICKS 2
#define JHI_NUMBER_AXES 2

#define JHI_JOY_BUTTON_PRESSED 1
#define JHI_JOY_BUTTON_RELEASED 0
#define JHI_MAX_AXIS_VALUE 32767
#define JHI_MIN_AXIS_VALUE -32768

/**
 *  \file		jhi_joystick.h
 *  \brief	   	This file contains structures and enumeration of keyboard
 */


/**
 * \brief Enumeration of events of joystick
 */
typedef enum{
	JHI_JOY_AXIS_MOTION = 7,			/**< Joystick axis motion */
    JHI_JOY_BUTTON_DOWN = 10,			/**< Joystick button pressed */
    JHI_JOY_BUTTO_NUP = 11,				/**< Joystick button released */
    JHI_JOY_NOT_EVENT
}JHI_JOYSTICK_EVENT;

/**
 * \brief Enumeration of the possibles dir that will pressed in the joystick
 */
typedef enum {
	JOY_LEFT,
	JOY_RIGHT,
	JOY_UP,
	JOY_DOWN,
	JOY_NOT_DIR,
	JOY_DIR_RELEASED
}JHI_JOY_DIR_;


/**
 * \brief Enumeration of the possibles buttons that will pressed in the joystick
 */
typedef enum {
	JOY_BUTTON_0,
	JOY_BUTTON_1,
	JOY_BUTTON_2,
	JOY_BUTTON_3,
	JOY_BUTTON_4,
	JOY_BUTTON_5,
	JOY_BUTTON_6,
	JOY_BUTTON_7,
	JOY_BUTTON_8,
	JOY_BUTTON_9,
	JOY_NOT_BUTTON

}JHI_JOY_BUTTONS;


/**
 * \brief Joystick structure
 */
typedef struct {
	JHI_JOYSTICK_EVENT joy_event; 				/**< Joystick event that was captured*/
	short int joy_index;		  				/**< Joystick index that was captured*/
	short int axis_index;		  				/**< Joystick axis_index that was captured*/
	short int axis_value[JHI_NUMBER_AXES];		/**< Joystick axis values*/
	short int button;							/**< Joystick value of button pressed*/
	short int button_state;						/**< Joystick buttons is pressed or no */
}JHI_JoystickSt;


/**
 * \brief Initialize the joystick structure
 * \param joy joystick structure
 */
void jhi_init_joystick(JHI_JoystickSt *joy);

/**
 * \brief Open Joystick with index joy_index
 * \param joy_index
 * \return 1 success, 0 otherwise
 */
int jhi_open_joystick_index(short int joy_index);

/**
 * \brief Free the joystick structure
 * \param joy joystick structure
 * \return 1 success, 0 otherwise
 */
void jhi_free_joystick_index(short int joy_index);

/**
 * \brief Get number of joysticks
 * \return number of joysticks
 */
int jhi_get_num_of_joystick();

/**
 * \brief Check if index is valid
 * \return 1 ok, 0 otherwise
 */
int jhi_is_valid_joystick_index(int index);


/**
 * \brief Get dir of joystick
 * \param joy joystick structure
 * \param axe_index index of axe
 * \return 1 ok, 0 otherwise
 */
JHI_JOY_DIR_ jhi_get_joystick_dir(JHI_JoystickSt *joy, int axe_index);


#endif
