/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 16:48:16 by malexand          #+#    #+#             */
/*   Updated: 2017/10/24 22:18:38 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	putpxl(t_param *param, int y, int x, Uint32 pixel)
{
	int		num_surf;
	int		bpp;
	Uint8	*p;

	if (y != 0) {
		num_surf = y / (WINDOW_SDL_HEIGHT / NB_THREAD);
		if (num_surf != 0)
			y = y % (num_surf * WINDOW_SDL_HEIGHT / NB_THREAD);
	} else if (y == 0) {
		num_surf = 0;
	}

	if (y < 0 || y > WINDOW_SDL_HEIGHT / NB_THREAD || x < 0 || x > WINDOW_SDL_WIDTH)
		return;

	if (param->graph->show_tmp == 0) {
		pixel =	SDL_MapRGBA(param->graph->surfs[num_surf]->format,
			(pixel) & 0xFF, (pixel >> 8) & 0xFF, (pixel >> 16) & 0xFF, 0xFF);
		bpp = param->graph->surfs[num_surf]->format->BytesPerPixel; 
		p = (Uint8 *)param->graph->surfs[num_surf]->pixels + y * param->graph->surfs[num_surf]->pitch + x *
			bpp;
	} else {
		pixel =	SDL_MapRGBA(param->graph->tmp_surfs[num_surf]->format,
			(pixel) & 0xFF, (pixel >> 8) & 0xFF, (pixel >> 16) & 0xFF, 0xFF);
		bpp = param->graph->tmp_surfs[num_surf]->format->BytesPerPixel;
		p = (Uint8 *)param->graph->tmp_surfs[num_surf]->pixels + y * param->graph->tmp_surfs[num_surf]->pitch + x *
			bpp;
	}

	if (bpp == 1)
		*p = pixel;
	else if (bpp == 2)
		*(Uint16 *)p = pixel;
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xFF;
			p[1] = (pixel >> 8) & 0xFF;
			p[2] = pixel & 0xFF;
		}
		else
		{
			p[0] = pixel & 0xFF;
			p[1] = (pixel >> 8) & 0xFF;
			p[2] = (pixel >> 16) & 0xFF;
		}
	}
	else if (bpp == 4)
		*(Uint32 *)p = pixel;
}

Uint32 getpxl(t_param *param, int y, int x)
{
		int		num_surf;
		int		bpp;
		Uint8	*p;
	
		if (y != 0) {
			num_surf = y / (WINDOW_SDL_HEIGHT / NB_THREAD);
			if (num_surf != 0)
				y = y % (num_surf * WINDOW_SDL_HEIGHT / NB_THREAD);
		} else if (y == 0) {
			num_surf = 0;
		}
	
		if (y < 0 || y > WINDOW_SDL_HEIGHT / NB_THREAD || x < 0 || x > WINDOW_SDL_WIDTH)
			return 0;
		
		bpp = param->graph->surfs[num_surf]->format->BytesPerPixel; 
    p = (Uint8 *)param->graph->surfs[num_surf]->pixels + y * param->graph->surfs[num_surf]->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
