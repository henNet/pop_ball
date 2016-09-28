#include "jhi_keyboard.h"


void jhi_init_keyboard(JHI_KeyboardSt *key)
{
	key->key = NO_KEY;
	key->key_event = KEYBOARD_NOT_EVENT;
}


int jhi_is_key_arrow(JHI_Keys key)
{
	return (key >= KEY_UP && key <= KEY_LEFT);
}

JHI_Keys jhi_get_opposite_key_arrow(JHI_Keys key)
{
	switch(key)
	{
		case KEY_DOWN:
			return KEY_UP;
		case KEY_UP:
			return KEY_DOWN;
		case KEY_RIGHT:
			return KEY_LEFT;
		case KEY_LEFT:
			return KEY_RIGHT;
	}
	return NO_KEY;
}
