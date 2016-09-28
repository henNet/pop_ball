#include "jhi_image.h"

void jhi_load_image(JHI_Image *img, const char *filename)
{
	SDL_Surface *loadedImage = NULL, *optimizedImage = NULL;

	loadedImage = IMG_Load(filename);

	if(loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);

		SDL_FreeSurface(loadedImage);
	}
	else {
		printf("File %s not found.\n", filename);
		exit(1);
	}

	img->sur = optimizedImage;
	img->pos.x = 0;
	img->pos.y = 0;
}


void jhi_load_image_with_transparent_color(JHI_Image *img, const char *filename, JHI_Color col)
{
	SDL_Surface *loadedImage = NULL, *optimizedImage = NULL;

	loadedImage = IMG_Load(filename);

	if(loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);

		SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, colors[col].r, colors[col].g, colors[col].b));

		SDL_FreeSurface(loadedImage);
	}
	else {
		printf("Image File %s not found.\n", filename);
		exit(1);
	}

	img->sur = optimizedImage;
	img->pos.x = 0;
	img->pos.y = 0;
}

void jhi_free_image(JHI_Image *img)
{
	SDL_FreeSurface(img->sur);
}

int jhi_get_image_width(JHI_Image *img)
{
	return img->sur->w;
}

int jhi_get_image_height(JHI_Image *img)
{
	return img->sur->h;
}


/*
 * Functions from http://www.dzone.com/snippets/useful-sdl-functions
 */

// matchColorKeys: This copies the transparency data from one
// surface to another.
static void jhi_match_color_keys( SDL_Surface* src, SDL_Surface* dest )
{
	// If the original had an alpha color key, give it to the new one.
	if( src->flags & SDL_SRCCOLORKEY )
	{
		// Acquire the original Key
		Uint32 color_key = src->format->colorkey;

		// Set to the new image
		SDL_SetColorKey( dest, SDL_SRCCOLORKEY, color_key );
	}
}

// resizeImage: Resizes an image at its current place in memory. This means
//      that if you skew and stretch, you'll lose quality, but it also
//      means no worrying about new pointers. This uses the zoomSurface functions
//      in SDL_rotozoom.h ( SDL_gfx package )
static void jhi_resize_surface(JHI_Image *img, double new_width, double new_height)
{
	// Zoom function uses doubles for rates of scaling, rather than
	// exact size values. This is how we get around that:
	double zoomx = new_width  / (float)jhi_get_image_width(img);
	double zoomy = new_height / (float)jhi_get_image_height(img);

	// This function assumes no smoothing, so that any colorkeys wont bleed.
	SDL_Surface* sized = zoomSurface(img->sur, zoomx, zoomy, SMOOTHING_OFF );

	// Copy transparency data.
	jhi_match_color_keys(img->sur, sized);

	// The original picture is no longer needed.
	SDL_FreeSurface(img->sur);

	// Set it instead to the new image.
	img->sur =  sized;
}

/************************************************/

void jhi_resize_image(JHI_Image *img, int width, int height)
{
	jhi_resize_surface(img, width, height);
}

void jhi_draw_image(JHI_Image *img, JHI_Point2d point)
{
	img->pos = point;

	jhi_draw_object(img->sur, point.x, point.y);
}

void jhi_draw_image_with_clip(JHI_Image *img, JHI_Point2d point_position, JHI_Point2d point_clip,
		int width, int height)
{
	img->pos = point_position;

	jhi_draw_object_with_clip(img->sur, point_position.x, point_position.y,
			point_clip.x, point_clip.y, width, height);
}

void jhi_set_alpha_image(JHI_Image *img, int alpha)
{
	SDL_SetAlpha(img->sur, SDL_SRCALPHA, alpha );
}
