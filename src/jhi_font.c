#include "jhi_font.h"

void jhi_load_font(JHI_Font *font, const char *font_name, int length)
{
	font->font = NULL;
	font->font = TTF_OpenFont(font_name, length);

	font->length = length;

	if (font->font == NULL)
	{
		printf("File %s not found.\n", font_name);
	}

}

void jhi_free_font(JHI_Font *font)
{
	TTF_CloseFont(font->font);
}

int jhi_get_lenght_font(JHI_Font *font)
{
	return font->length;
}
