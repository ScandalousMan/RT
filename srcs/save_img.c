/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:45:46 by itsalex           #+#    #+#             */
/*   Updated: 2018/08/29 14:45:48 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	save_img(t_param *param, char *name)
{
	int 			count;
	SDL_Surface 	*surf;
	SDL_Rect 		rect_to;

	count = 0;
	if (!(surf = SDL_CreateRGBSurfaceWithFormat(0,
	WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT, 32, SDL_PIXELFORMAT_ARGB8888)))
		error(0, 0, "Can't create saved image surface");
	while (count < NB_THREAD)
	{
		rect_to.x = 0;
		rect_to.y = count * WINDOW_SDL_HEIGHT / NB_THREAD;
		rect_to.w = WINDOW_SDL_WIDTH;
		rect_to.h = WINDOW_SDL_HEIGHT / NB_THREAD;
		if ((param->graph->show_tmp == 0 && SDL_BlitSurface(param->graph->surfs[count], NULL, surf, &rect_to)) || (param->graph->show_tmp == 1 && SDL_BlitSurface(param->graph->tmp_surfs[count], NULL, surf, &rect_to)))
			error(0, 0, "cannot copy surface on total image");
		count++;
	}
	name = ft_strjoin_free(name, ft_strdup(".png"));
	if (IMG_SavePNG(surf, name))
		error(0, 0, "Cannot save the image");
	else 
		mprintf(1, "Image has been saved\n");
	ft_strdel(&name);
	SDL_FreeSurface(surf);
}
