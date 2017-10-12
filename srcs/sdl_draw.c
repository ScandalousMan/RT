/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:46:21 by malexand          #+#    #+#             */
/*   Updated: 2017/09/27 14:44:00 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	sdl_draw(t_sdl *graph)
{
	SDL_Rect		dest;
	SDL_Texture		*text;
	int				count;

	count = 0;
	dest.x = 0;
	dest.w = graph->surfs[count]->w;
	dest.h = graph->surfs[count]->h;
	while (count < NB_THREAD)
	{
		if (graph->show_tmp == 0) {
			text = SDL_CreateTextureFromSurface(graph->render_sdl,
			graph->surfs[count]);
		} else {
			text = SDL_CreateTextureFromSurface(graph->render_sdl,
			graph->tmp_surfs[count]);
		}
		if (text)
		{
			dest.y = (WINDOW_SDL_HEIGHT / NB_THREAD) * count;
			SDL_RenderCopy(graph->render_sdl, text, NULL, &dest);
			SDL_DestroyTexture(text);
		}
		else
			exit(0);
		count++;
	}
	SDL_RenderPresent(graph->render_sdl);
}
