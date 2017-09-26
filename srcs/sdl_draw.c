/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:46:21 by malexand          #+#    #+#             */
/*   Updated: 2017/09/26 17:42:24 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

void	sdl_draw(t_sdl *graph)
{
	SDL_Rect		dest;
	SDL_Texture		*text;
	int				count;

	count = 0;
	dest.x = 0;
	dest.w = graph->surfs[count]->w;
	dest.h = graph->surfs[count]->h;
	while (count < 4)
	{
		text = SDL_CreateTextureFromSurface(graph->render_sdl,
		graph->surfs[count]);
		if (text)
		{
			dest.y = (WINDOW_SDL_HEIGHT / 4) * count;
			SDL_RenderCopy(graph->render_sdl, text, NULL, &dest);
			SDL_DestroyTexture(text);
		}
		else
			exit(0);
		count++;
	}
	SDL_RenderPresent(graph->render_sdl);
}
