/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 16:48:16 by malexand          #+#    #+#             */
/*   Updated: 2019/01/10 21:58:47 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		putpxl(t_param *param, int y, int x, Uint32 pixel)
{
	int		num_surf;
	Uint8	*p;

	if (x >= WINDOW_SDL_WIDTH || y >= WINDOW_SDL_HEIGHT)
		return ;
	if (y != 0)
	{
		num_surf = y / (WINDOW_SDL_HEIGHT / NB_THREAD);
		if (num_surf != 0)
			y = y % (num_surf * WINDOW_SDL_HEIGHT / NB_THREAD);
	}
	else if (y == 0)
		num_surf = 0;
	pixel = pixel | 0xFF000000;
	if (y < 0 || y > WINDOW_SDL_HEIGHT / NB_THREAD || x < 0
	|| x > WINDOW_SDL_WIDTH)
		return ;
	if (param->graph->show_tmp == 0)
		p = (Uint8 *)param->graph->surfs[num_surf]->pixels + y *
			param->graph->surfs[num_surf]->pitch + x * 4;
	else
		p = (Uint8 *)param->graph->tmp_surfs[num_surf]->pixels + y *
			param->graph->tmp_surfs[num_surf]->pitch + x *
			param->graph->tmp_surfs[num_surf]->format->BytesPerPixel;
	*(Uint32 *)p = pixel;
}

Uint32		getpxl(t_param *param, int y, int x)
{
	int		num_surf;

	if (y != 0)
	{
		num_surf = y / (WINDOW_SDL_HEIGHT / NB_THREAD);
		if (num_surf != 0)
			y = y % (num_surf * WINDOW_SDL_HEIGHT / NB_THREAD);
	}
	else if (y == 0)
		num_surf = 0;
	if (y < 0 || y > WINDOW_SDL_HEIGHT / NB_THREAD || x < 0
	|| x > WINDOW_SDL_WIDTH)
		return (0);
	return (*(Uint32 *)(param->graph->surfs[num_surf]->pixels +
		y * param->graph->surfs[num_surf]->pitch + x * 4));
}

Uint32		jpg_find_pxl(t_param *param, double w, double h)
{
	int color;

	if (w > 1 || w < 0 || h > 1 || h < 0)
		return (0);
	color = (int)*(Uint32 *)(param->texture->pixels +
		(int)round(param->texture->w * w) * param->texture->pitch +
		(int)round(param->texture->h * h) *
		param->texture->format->BytesPerPixel);
	return (rgb_color((color) & 0xFF, (color >> 8) &
		0xFF, (color >> 16) & 0xFF));
}
