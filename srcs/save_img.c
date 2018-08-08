#include "rt.h"

void	save_img(t_param *param)
{
	SDL_Surface *surf;
	int 				count;
	SDL_Rect 		rect_to;

	if (!(surf = SDL_CreateRGBSurfaceWithFormat(0,
	WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT, 32, SDL_PIXELFORMAT_ARGB8888)))
		error(0, 0, "Can't create saved image surface");
	count = 0;
	while (count < NB_THREAD)
	{
		rect_to.x = 0;
		rect_to.y = count * WINDOW_SDL_HEIGHT / NB_THREAD;
		rect_to.w = WINDOW_SDL_WIDTH;
		rect_to.h = WINDOW_SDL_HEIGHT / NB_THREAD;
		if (SDL_BlitSurface(param->graph->surfs[count], NULL, surf, &rect_to))
			error(0, 0, "cannot copy surface on total image");
		count++;
	}
	if (IMG_SavePNG(surf, SAVED_IMG_NAME))
		error(0, 0, "cannot save the image");
	else 
		mprintf(1, "image has been saved\n");
	SDL_FreeSurface(surf);
}