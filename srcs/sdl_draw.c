/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:46:21 by malexand          #+#    #+#             */
/*   Updated: 2017/09/26 16:48:13 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

void	sdl_draw(t_sdl *graph)
{
	int		k;

	k = 0;
	while (k < 4)
	{
		for (int i = 0; i < WINDOW_SDL_HEIGHT / 4; i++) {
			for (int p = 0; p < 200; p++) {
				putpixel(graph->surfs[k], p, i, SDL_MapRGBA(graph->surfs[k]->format, 255, 255, 255, 255));
			}
		}
		SDL_Texture	*text = SDL_CreateTextureFromSurface(graph->render_sdl, graph->surfs[k]); // Préparation du sprite
		if (text)
		{
			SDL_Rect dest = { 0, (WINDOW_SDL_HEIGHT / 4) * k , graph->surfs[k]->w, graph->surfs[k]->h};
			SDL_RenderCopy(graph->render_sdl, text, NULL, &dest); // Copie du sprite grâce au SDL_Renderer
			SDL_DestroyTexture(text); // Libération de la mémoire associée à la texture
		}
		else
			fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
		k++;
	}
	SDL_RenderPresent(graph->render_sdl);
}
