/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:46:21 by malexand          #+#    #+#             */
/*   Updated: 2017/11/19 23:56:46 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	SDL_Texture	*create_texture(t_sdl *graph, int count)
{
	SDL_Texture *text;

	if (graph->show_tmp == 0)
		text = SDL_CreateTextureFromSurface(graph->render_sdl,
			graph->surfs[count]);
	else
		text = SDL_CreateTextureFromSurface(graph->render_sdl,
			graph->tmp_surfs[count]);
	return (text);
}

static	void		apply_texture(t_sdl *graph, int count, SDL_Rect dest,
					SDL_Texture *text)
{
	if (text)
	{
		dest.y = (WINDOW_SDL_HEIGHT / NB_THREAD) * count;
		SDL_RenderCopy(graph->render_sdl, text, NULL, &dest);
		SDL_DestroyTexture(text);
	}
	else
	{
		mprintf(1, "Can't create texture to apply on screen: %s",
			SDL_GetError());
		exit(0);
	}
}

void				sdl_draw(t_sdl *graph)
{
	int				count;
	SDL_Rect		dest;

	count = 0;
	dest.x = 0;
	dest.w = graph->surfs[count]->w;
	dest.h = graph->surfs[count]->h;
	while (count < NB_THREAD)
	{
		apply_texture(graph, count, dest, create_texture(graph, count));
		count++;
	}
	SDL_RenderPresent(graph->render_sdl);
}
