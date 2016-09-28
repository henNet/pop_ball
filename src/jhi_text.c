#include "jhi_text.h"


void jhi_init_text(JHI_Text *text)
{
	text->sur = NULL;
	text->pos.x = 0;
	text->pos.y = 0;
}

void jhi_set_text(JHI_Font *font, JHI_Text *text, JHI_Color cor, const char *txt)
{
	SDL_Color textColor;

	textColor.r = colors[cor].r;
	textColor.g = colors[cor].g;
	textColor.b = colors[cor].b;

	if (text->sur != NULL)
	{
		jhi_free_text(text);
	}

	text->sur = NULL;

	text->sur = TTF_RenderUTF8_Solid(font->font, txt, textColor);

	if (text->sur == NULL)
	{
		printf("Error while rendering text %s.\n",txt);
	}

}

void jhi_free_text(JHI_Text *text)
{
	SDL_FreeSurface(text->sur);
}

int jhi_get_text_width(JHI_Text *text)
{
	return text->sur->w;
}

int jhi_get_text_height(JHI_Text *text)
{
	return text->sur->h;
}
void jhi_draw_text(JHI_Text *text, JHI_Point2d point)
{
	text->pos = point;

	jhi_draw_object(text->sur, point.x, point.y);
}

void jhi_set_alpha_text(JHI_Text *txt, int alpha)
{
	SDL_SetAlpha(txt->sur, SDL_SRCALPHA, alpha );
}
