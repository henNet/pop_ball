#ifndef INPUTST_H
#define INPUTST_H

//****************************************************************************
//*  This file contains structures and enumeration of keyboard    			 *
//*  	 	 									 			 				 *
//*           																 *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

#include "SDL/SDL.h"

/**
 *  \file		jhi_keyboard.h
 *  \brief	   	This file contains structures and enumeration of keyboard
 */


/**
 * \brief Enumeration of the possibles keys that will pressed in the keyboard
 */
typedef enum {
	KEY_ENTER = 13, 			/**< Key Enter*/
	KEY_0 = 48,					/**< Key 0*/
	KEY_1 = 49,					/**< Key 1*/
	KEY_2 = 50,					/**< Key 2*/
	KEY_3 = 51,					/**< Key 3*/
	KEY_4 = 52,					/**< Key 4*/
	KEY_5 = 53,					/**< Key 5*/
	KEY_6 = 54,					/**< Key 6*/
	KEY_7 = 55,					/**< Key 7*/
	KEY_8 = 56,					/**< Key 8*/
	KEY_9 = 57,					/**< Key 9*/
	KEY_UP = 273,				/**< Key UP*/
	KEY_DOWN = 274,				/**< Key DOWN*/
	KEY_RIGHT = 275,			/**< Key RIGHT*/
	KEY_LEFT = 276,				/**< Key LEFT*/
	KEY_A = 97,					/**< Key A*/
	KEY_B = 98,					/**< Key B*/
	KEY_C = 99,					/**< Key C*/
	KEY_D = 100,				/**< Key D*/
	KEY_E = 101,				/**< Key E*/
	KEY_F = 102,				/**< Key F*/
	KEY_G = 103,				/**< Key G*/
	KEY_H = 104,				/**< Key H*/
	KEY_I = 105,				/**< Key I*/
	KEY_J = 106,				/**< Key J*/
	KEY_K = 107,				/**< Key K*/
	KEY_L = 108,				/**< Key L*/
	KEY_M = 109,				/**< Key M*/
	KEY_N = 110,				/**< Key N*/
	KEY_O = 111,				/**< Key O*/
	KEY_P = 112,				/**< Key P*/
	KEY_Q = 113,				/**< Key Q*/
	KEY_R = 114,				/**< Key R*/
	KEY_S = 115,				/**< Key S*/
	KEY_T = 116,				/**< Key T*/
	KEY_U = 117,				/**< Key U*/
	KEY_V = 118,				/**< Key V*/
	KEY_W = 119,				/**< Key W*/
	KEY_X = 120,				/**< Key X*/
	KEY_Y = 121,				/**< Key Y*/
	KEY_Z = 122,				/**< Key Z*/
	NO_KEY = 123				/**< No Key*/
}JHI_Keys;


/**
 * \brief Enumeration of events of keyboard
 */
typedef enum {
	KEYBOARD_UP,					/**< Keyboard was pressed*/
	KEYBOARD_DOWN,					/**< Keyboard was released*/
	KEYBOARD_NOT_EVENT				/**< Nothing*/
}JHI_KeyBoardEvents;

/**
 * \brief Keyboard structure
 */
typedef struct {
	Uint8 key_event;			/**< Keyboard event that was captured*/
	JHI_Keys key;					/**< Keyboard key that was pressed*/
}JHI_KeyboardSt;


/**
 * \brief init the keyboard structure
 * \param key keyboard that will init
 */
void jhi_init_keyboard(JHI_KeyboardSt *key);

/**
 * \brief Check if the key is arrow key
 * \param key key to check
 * \return 1 yes, 0 no
 */
int jhi_is_key_arrow(JHI_Keys key);

/**
 * \brief Get the opposite dir key
 * \param key key dir
 * \return opposite dir key, NO_KEY is return in error case
 */
JHI_Keys jhi_get_opposite_key_arrow(JHI_Keys key);


#endif
