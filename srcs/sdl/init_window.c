/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 16:47:34 by malexand          #+#    #+#             */
/*   Updated: 2018/09/08 17:01:55 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	set_window_pos_center(int *x, int *y)
{
	SDL_DisplayMode dm;

	if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
	{
		*x = 400;
		*y = 400;
	}
	else
	{
		*x = dm.w / 2 - WINDOW_GUI_WIDTH - WINDOW_SDL_WIDTH / 2;
		*y = dm.h / 2 - WINDOW_GUI_HEIGHT / 2;
	}
}

void			sdl_init_window(t_sdl *graph)
{
	int pos_x;
	int pos_y;

	glewExperimental = 1;
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
						SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
						SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	set_window_pos_center(&pos_x, &pos_y);
	graph->win_gl = SDL_CreateWindow("RT GUI", pos_x, pos_y, WINDOW_GUI_WIDTH,
						WINDOW_GUI_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
						| SDL_WINDOW_ALLOW_HIGHDPI);
}

void			sdl_init_nuklear(t_sdl *graph)
{
	t_nk_font_atlas *atlas;

	graph->gl_context = SDL_GL_CreateContext(graph->win_gl);
	glViewport(0, 0, WINDOW_GUI_WIDTH, WINDOW_GUI_HEIGHT);
	if (glewInit() != GLEW_OK)
		error(0, 0, "Glew init failed!");
	graph->ctx = nk_sdl_init(graph->win_gl);
	nk_sdl_font_stash_begin(&atlas);
	nk_sdl_font_stash_end();
}
