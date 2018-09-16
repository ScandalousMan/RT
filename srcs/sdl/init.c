/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:06:38 by malexand          #+#    #+#             */
/*   Updated: 2018/09/08 17:02:40 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			sdl_init(t_sdl *graph)
{
	int		count;

	count = 0;
	sdl_init_window(graph);
	sdl_init_nuklear(graph);
	if (SDL_CreateWindowAndRenderer(WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT,
	SDL_WINDOW_SHOWN, &graph->win_sdl, &graph->render_sdl) < 0)
	{
		printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
		exit(0);
	}
	while (count < NB_THREAD)
	{
		if ((graph->surfs[count] = SDL_CreateRGBSurfaceWithFormat(0,
				WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT / NB_THREAD, 32,
				SDL_PIXELFORMAT_ARGB8888)) == NULL)
			error(0, 0, "Can't create all surface");
		if ((graph->tmp_surfs[count] = SDL_CreateRGBSurfaceWithFormat(0,
				WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT / NB_THREAD, 32,
				SDL_PIXELFORMAT_ARGB8888)) == NULL)
			error(0, 0, "Can't create all surface");
		count++;
	}
}

void			sdl_quit(t_sdl *graph)
{
	int		count;

	count = 0;
	while (count < NB_THREAD)
	{
		SDL_FreeSurface(graph->surfs[count]);
		SDL_FreeSurface(graph->tmp_surfs[count]);
		count++;
	}
	nk_sdl_shutdown();
	SDL_GL_DeleteContext(graph->gl_context);
	SDL_DestroyWindow(graph->win_gl);
	SDL_DestroyWindow(graph->win_sdl);
	SDL_DestroyRenderer(graph->render_sdl);
	free(graph);
	IMG_Quit();
	SDL_Quit();
}
