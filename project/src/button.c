#include "button.h"

void init_button(Button *but, JHI_Font *font, const char *txt, const char *button_type)
{
	int w,h;

	but->pos.x = 0;
	but->pos.y = 0;
	jhi_load_image_with_transparent_color(&(but->img), button_type, BLUE);

	but->font = font;


	jhi_init_text(&(but->txt));

	jhi_set_text(font, &(but->txt), BLACK, txt);

	w = but->txt.sur->w + but->txt.sur->w / 2;
	h = but->txt.sur->h + but->txt.sur->h / 2;

	but->txt.pos = jhi_get_central_pos(w, h, but->txt.sur->w, but->txt.sur->h);

	strcpy(but->btype, button_type);
	but->btype[13] = '\0';

	jhi_resize_image(&(but->img), w, h);
}

void change_button_text(Button *but, const char *new_text)
{
	jhi_set_text(but->font, &(but->txt), BLACK, new_text);
}

int change_button_image(Button *but, const char *button_type)
{

	if (strcmp(but->btype, button_type))
	{
		jhi_free_image(&(but->img));
		jhi_load_image_with_transparent_color(&(but->img), button_type, BLUE);
		return 1;
	}

	return 0;
}

void set_button_size(Button *but, int w, int h)
{
	jhi_resize_image(&(but->img), w, h);
}

void draw_button(Button *but, JHI_Point2d pos)
{
	jhi_draw_image(&(but->img), pos);

	but->pos = pos;

	but->txt.pos.x = jhi_get_central_pos(jhi_get_image_width(&(but->img)), jhi_get_image_height(&(but->img)),
			but->txt.sur->w, but->txt.sur->h).x + pos.x;
	but->txt.pos.y = jhi_get_central_pos(jhi_get_image_width(&(but->img)) + pos.x, jhi_get_image_height(&(but->img)),
			but->txt.sur->w, but->txt.sur->h).y + pos.y;

	jhi_draw_text(&(but->txt), but->txt.pos);
}

void free_button(Button *but)
{
	jhi_free_image(&(but->img));
	jhi_free_text(&(but->txt));
}

int check_buttons(JHI_MouseSt mouse, Button *vet, int vet_size)
{
	int i, w,h;

	for (i = 0; i < vet_size; i++)
	{

		if (jhi_check_mouse_is_in(mouse, vet[i].pos.x, vet[i].pos.y,
				jhi_get_image_width(&(vet[i].img)), jhi_get_image_height(&(vet[i].img))))
		{

			w = jhi_get_image_width(&(vet[i].img));
			h = jhi_get_image_height(&(vet[i].img));

			if(change_button_image(&vet[i], BUTTON_TYPE_2))
			{
				set_button_size(&vet[i], w, h);
			}

			if (mouse.mouse_event == ON_CLICK_LEFT)
			{
				return i;
			}


		}

		else
		{
			w = jhi_get_image_width(&(vet[i].img));
			h = jhi_get_image_height(&(vet[i].img));

			if(change_button_image(&vet[i], BUTTON_TYPE_1))
			{
				set_button_size(&vet[i], w, h);
			}


		}
	}

	return -1;
}
