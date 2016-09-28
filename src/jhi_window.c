#include "jhi_window.h"

static JHI_Window WinMain;

void jhi_print_pixel(int x, int y, JHI_Color col)
{
	int offset = y * WinMain.screen->w + x;
	Uint32 color = SDL_MapRGB(WinMain.screen->format, colors[col].r, colors[col].g, colors[col].b);
	if (!jhi_out_window(x, y))
	{
		if(WinMain.screen->format->BytesPerPixel == 1)
				*( ((Uint8*)WinMain.screen->pixels) + offset) = color;
		else if(WinMain.screen->format->BytesPerPixel == 2)
				*( ((Uint16*)WinMain.screen->pixels) + offset) = color;
		else
				*( ((Uint32*)WinMain.screen->pixels) + offset) = color;
	}
}

SDL_Surface* jhi_get_window_screen()
{
	return WinMain.screen;
}

int jhi_out_window(int x, int y)
{
	if ( (x <= 0 || x >= WinMain.width)|| (y <= 0 || y >= WinMain.height) )
	{
		return 1;
	}


	return 0;
}

void jhi_draw_object(SDL_Surface *object, int x, int y)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(object, NULL, WinMain.screen, &offset);
}

void jhi_draw_object_with_clip(SDL_Surface *object, int x, int y, int x_clip, int y_clip, int width, int height)
{

    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_Rect clip;

    clip.x = x_clip;
    clip.y = y_clip;
    clip.w = width;
    clip.h = height;


    SDL_BlitSurface(object, &clip, WinMain.screen, &offset);
}



void jhi_initialize_window(int width , int height, int bitperpixel, JHI_Color back_color)
{

	if( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
	{
	    printf("Error initializing window\n");
		exit(1);
	}

	WinMain.screen = NULL;

	WinMain.screen = SDL_SetVideoMode(width, height, bitperpixel, SDL_DOUBLEBUF);

	if (!WinMain.screen) {
		printf("Error while initializing window.\n");
		exit(1);
	}


	WinMain.width = width;
	WinMain.height = height;

	WinMain.check_quit = JHI_NOT_CLOSE;

	SDL_FillRect( WinMain.screen, &WinMain.screen->clip_rect, SDL_MapRGB( WinMain.screen->format, colors[back_color].r,colors[back_color].g ,colors[back_color].b));

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		printf("Error while initializing sound.\n");
		exit(1);
	}

	if(TTF_Init() == -1) 
	{ 
		printf("Error while initializing font.\n");
		exit(1); 
	}

	srand((unsigned)time(NULL));

	WinMain.back_color = back_color;
}

void jhi_choice_window_name(const char *win_name)
{
	const char *win_minimized_name = win_name;
	SDL_WM_SetCaption(win_name, win_minimized_name);
}


void jhi_init_mouse_keyboard_joystick_events()
{
	int i;
	WinMain.number_of_events = 0;
	for (i = 0; i < NUMBER_MAX_EVENTS; i++)
	{
		jhi_init_mouse(&WinMain.mouse[i]);
		jhi_init_keyboard(&WinMain.key[i]);
		jhi_init_joystick(&WinMain.joy[i]);
	}
}

int jhi_get_number_of_events()
{
	return WinMain.number_of_events;
}

void jhi_update()
{

	jhi_init_mouse_keyboard_joystick_events();
	while( SDL_PollEvent(&(WinMain.event))){
		if( WinMain.event.type == SDL_QUIT ){
			WinMain.check_quit = JHI_CLOSE;
		}
		else if (WinMain.event.type == SDL_MOUSEMOTION) {
			WinMain.mouse[WinMain.number_of_events].x = WinMain.event.motion.x;
			WinMain.mouse[WinMain.number_of_events].y = WinMain.event.motion.y;
			WinMain.mouse[WinMain.number_of_events].mouse_event = MOUSE_MOTION;
		}
		else if (WinMain.event.type == SDL_MOUSEBUTTONDOWN) {
			WinMain.mouse[WinMain.number_of_events].x = WinMain.event.motion.x;
			WinMain.mouse[WinMain.number_of_events].y = WinMain.event.motion.y;

			if (WinMain.event.button.button == SDL_BUTTON_LEFT) {
				WinMain.mouse[WinMain.number_of_events].mouse_event = ON_CLICK_LEFT;
			}
			else if (WinMain.event.button.button == SDL_BUTTON_RIGHT) {
				WinMain.mouse[WinMain.number_of_events].mouse_event = ON_CLICK_RIGHT;
			}
		}
		else if (WinMain.event.type == SDL_KEYDOWN) {
			WinMain.key[WinMain.number_of_events].key_event = KEYBOARD_DOWN;
			WinMain.key[WinMain.number_of_events].key = WinMain.event.key.keysym.sym;

		}
		else if (WinMain.event.type == SDL_KEYUP) {
			WinMain.key[WinMain.number_of_events].key_event = KEYBOARD_UP;
			WinMain.key[WinMain.number_of_events].key = WinMain.event.key.keysym.sym;
		}
		else if (WinMain.event.type == SDL_JOYAXISMOTION) {
			WinMain.joy[WinMain.number_of_events].joy_event = SDL_JOYAXISMOTION;
			WinMain.joy[WinMain.number_of_events].axis_value[WinMain.event.jaxis.axis] = WinMain.event.jaxis.value;
			WinMain.joy[WinMain.number_of_events].axis_index = WinMain.event.jaxis.axis;
		}
		else if (WinMain.event.type == SDL_JOYBUTTONUP || WinMain.event.type == SDL_JOYBUTTONDOWN) {
			WinMain.joy[WinMain.number_of_events].joy_event = WinMain.event.type;
			WinMain.joy[WinMain.number_of_events].button = WinMain.event.jbutton.button;
			WinMain.joy[WinMain.number_of_events].button_state =  WinMain.event.jbutton.state;
		}

		WinMain.number_of_events++;
	}

	SDL_Flip(WinMain.screen);
}

void jhi_set_background_color(JHI_Color back_color)
{
	WinMain.back_color = back_color;
}

void jhi_clean()
{
	SDL_FillRect( WinMain.screen, &WinMain.screen->clip_rect, SDL_MapRGB( WinMain.screen->format, colors[WinMain.back_color].r,colors[WinMain.back_color].g ,colors[WinMain.back_color].b));
}

char jhi_get_close_window()
{
	return WinMain.check_quit;
}

JHI_MouseSt jhi_get_mouse_status(int i)
{
	return WinMain.mouse[i];
}

JHI_KeyboardSt jhi_get_keyboard_status(int i)
{
	return WinMain.key[i];
}

JHI_JoystickSt jhi_get_joystick_status(int i)
{
	return WinMain.joy[i];
}

int jhi_get_height_window()
{
	return WinMain.height;
}

int jhi_get_width_window()
{
	return WinMain.width;
}

void jhi_quit_and_free()
{
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();	
}
