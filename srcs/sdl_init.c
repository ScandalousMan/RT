/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:06:38 by malexand          #+#    #+#             */
/*   Updated: 2017/09/26 17:45:33 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

/*
** SDL setup
** then OpenGL setup
*/

static void		init_win_gui(t_sdl *graph)
{
	t_nk_font_atlas *atlas;

	glewExperimental = 1;
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
		SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	graph->win_gl = SDL_CreateWindow("RT GUI", 400, 400, WINDOW_GUI_WIDTH,
		WINDOW_GUI_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
		SDL_WINDOW_ALLOW_HIGHDPI);
	graph->gl_context = SDL_GL_CreateContext(graph->win_gl);
	glViewport(0, 0, WINDOW_GUI_WIDTH, WINDOW_GUI_HEIGHT);
	if (glewInit() != GLEW_OK)
		exit(1);
	graph->ctx = nk_sdl_init(graph->win_gl);
	nk_sdl_font_stash_begin(&atlas);
	nk_sdl_font_stash_end();
}

void			sdl_init(t_sdl *graph)
{
	int		count;

	count = 0;
	init_win_gui(graph);
	if (SDL_CreateWindowAndRenderer(WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT,
	SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI, &graph->win_sdl,
	&graph->render_sdl) < 0)
	{
		printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
		exit(0);
	}
	if ((graph->surfs = (SDL_Surface**)malloc(sizeof(SDL_Surface) * 4))
	== NULL)
	{
		printf("Erreur when malloc four surfaces");
		exit(0);
	}
	while (count < 4)
	{
		if ((graph->surfs[count] = SDL_CreateRGBSurfaceWithFormat(0,
		WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT / 4, 32, SDL_PIXELFORMAT_RGBA32))
		== NULL)
			exit(0);
		count++;
	}
}

void			sdl_quit(t_sdl *graph)
{
	SDL_FreeSurface(graph->surfs[0]);
	SDL_FreeSurface(graph->surfs[1]);
	SDL_FreeSurface(graph->surfs[2]);
	SDL_FreeSurface(graph->surfs[3]);
	ft_strdel(&graph->input);
	nk_sdl_shutdown();
	SDL_GL_DeleteContext(graph->gl_context);
	SDL_DestroyWindow(graph->win_gl);
	SDL_DestroyWindow(graph->win_sdl);
	free(graph);
	SDL_Quit();
}
