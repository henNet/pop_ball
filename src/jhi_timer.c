
static int FPS = 32;
static int StartTicks = 0;

#include "jhi_timer.h"

void jhi_set_fps_timer(int fps)
{
	FPS = fps;
}

int jhi_get_fps_timer()
{
	return FPS;
}

void jhi_timer_start()
{
	StartTicks = SDL_GetTicks();
}

void jhi_wait_time()
{
	int current_tick = SDL_GetTicks() - StartTicks;

	if (current_tick < 1000 / FPS)
	{
		SDL_Delay( (1000 / FPS) - current_tick);
	}
}

void jhi_delay_seconds(int seconds)
{
	SDL_Delay(seconds * 1000.0);
}

void jhi_delay_mili_seconds(int ms)
{
	SDL_Delay(ms);
}
