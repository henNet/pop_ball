#include "jhi_joystick.h"

static SDL_Joystick *Joy[JHI_NUMBER_MAX_JOYSTICKS];

void jhi_init_joystick(JHI_JoystickSt *joy)
{
	int i;

	for (i = 0; i < JHI_NUMBER_AXES; i++)
	{
		joy->axis_value[i] = 0;
	}

	joy->axis_index = -1;

	joy->button = JOY_NOT_BUTTON;
	joy->button_state = 0;
	joy->joy_event = JHI_JOY_NOT_EVENT;
}

int jhi_open_joystick_index(short int joy_index)
{
	Joy[joy_index] = SDL_JoystickOpen(joy_index);

	if (Joy[joy_index] == NULL)
	{
		return 0;
	}

	return 1;
}

void jhi_free_joystick_index(short int joy_index)
{
	SDL_JoystickClose(Joy[joy_index]);
}

int jhi_is_valid_joystick_index(int index)
{
	if (index >= 0 && index < JHI_NUMBER_AXES)
	{
		return 1;
	}

	return 0;
}

int jhi_get_num_of_joystick()
{
	return SDL_NumJoysticks();
}

JHI_JOY_DIR_ jhi_get_joystick_dir(JHI_JoystickSt *joy, int axe_index)
{
	if (joy->axis_value[axe_index]== JHI_MAX_AXIS_VALUE)
	{
		if (axe_index == 0)
		{
			return JOY_RIGHT;
		}
		return JOY_DOWN;
	}
	else if (joy->axis_value[axe_index] == JHI_MIN_AXIS_VALUE)
	{
		if (axe_index == 0)
		{
			return JOY_LEFT;
		}

		return JOY_UP;
	}

	return JOY_DIR_RELEASED;
}
