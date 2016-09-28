#include "jhi_mouse.h"


void jhi_init_mouse(JHI_MouseSt *mouse)
{
	mouse->mouse_event = MOUSE_NOT_EVENT;
	mouse->x = 0;
	mouse->y = 0;
}

int jhi_check_mouse_is_in(JHI_MouseSt mouse, int xp, int yp, int w, int h)
{
	if (!(mouse.y >= yp  && mouse.y  <= yp + h))
	{
		return 0;
	}


	if (!(mouse.x >= xp  && mouse.x  <= xp + w))
	{
		return 0;
	}

	return 1;
}
