/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:06:38 by malexand          #+#    #+#             */
/*   Updated: 2017/11/20 00:05:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** SDL setup
** then OpenGL setup
*/

static void		init_win_gui(t_sdl *graph)
{
	t_nk_font_atlas *atlas;
	SDL_DisplayMode	dm;
	int pos_x;
	int pos_y;

	glewExperimental = 1;
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	IMG_Init(IMG_INIT_JPG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
		SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
		pos_x = 400;
		pos_y = 400;
	} else {
		pos_x = dm.w / 2 - WINDOW_GUI_WIDTH - WINDOW_SDL_WIDTH / 2;
		pos_y = dm.h / 2 - WINDOW_GUI_HEIGHT / 2;
	}
	graph->win_gl = SDL_CreateWindow("RT GUI", pos_x, pos_y, WINDOW_GUI_WIDTH,
		WINDOW_GUI_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
	graph->gl_context = SDL_GL_CreateContext(graph->win_gl);
	glViewport(0, 0, WINDOW_GUI_WIDTH, WINDOW_GUI_HEIGHT);
	if (glewInit() != GLEW_OK)
		error(0, 0, "Glew init failed!");
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
	SDL_WINDOW_SHOWN, &graph->win_sdl, &graph->render_sdl) < 0)
	{
		printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
		exit(0);
	}
	SDL_SetWindowTitle(graph->win_sdl, "RT");
	graph->ctx->style.button.normal = nk_style_item_color(nk_rgba(0, 0, 0, 0));
	graph->ctx->style.button.hover = nk_style_item_color(nk_rgb(255, 165, 0));
	graph->ctx->style.button.active = nk_style_item_color(nk_rgb(220, 10, 0));
	graph->ctx->style.button.border_color = nk_rgb(255, 165, 0);
	graph->ctx->style.button.text_background = nk_rgb(0, 0, 0);
	graph->ctx->style.button.text_normal = nk_rgb(255, 165, 0);
	graph->ctx->style.button.text_hover = nk_rgb(28, 48, 62);
	graph->ctx->style.button.text_active = nk_rgb(28, 48, 62);
	while (count < NB_THREAD)
	{
		if ((graph->surfs[count] = SDL_CreateRGBSurfaceWithFormat(0,
		WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT / NB_THREAD, 32, SDL_PIXELFORMAT_ARGB8888))
		== NULL)
			error(0, 0, "Can't create all surface");
		if ((graph->tmp_surfs[count] = SDL_CreateRGBSurfaceWithFormat(0,
		WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT / NB_THREAD, 32, SDL_PIXELFORMAT_ARGB8888))
		== NULL)
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
	free(graph);
	IMG_Quit();
	SDL_Quit();
}
