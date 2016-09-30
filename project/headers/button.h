#ifndef BUTTON_H
#define BUTTON_H

#include "jhi_image.h"
#include "jhi_text.h"
#include "jhi_shapes.h"
#include <string.h>

#define BUTTON_TYPE_1 "../images/button.png"
#define BUTTON_TYPE_2 "../images/button_on.png"

typedef struct
{
	JHI_Point2d pos;
	JHI_Text txt;
	JHI_Font *font;
	JHI_Image img;
	char btype[14];
}Button;

void init_button(Button *but, JHI_Font *font, const char *txt, const char *button_type);

void change_button_text(Button *but, const char *new_text);

int change_button_image(Button *but, const char *button_type);

void set_button_size(Button *but, int w, int h);

void draw_button(Button *but, JHI_Point2d pos);

int check_buttons(JHI_MouseSt mouse, Button *vet, int vet_size);

void free_button(Button *but);

#endif


