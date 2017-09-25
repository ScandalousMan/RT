/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:06:38 by malexand          #+#    #+#             */
/*   Updated: 2017/09/25 14:58:41 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

/*
** SDL setup
** then OpenGL setup
*/

void	sdl_init(t_sdl *graph)
{
	t_nk_font_atlas *atlas;

	glewExperimental = 1;
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
		SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	graph->win = SDL_CreateWindow("RT",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
		SDL_WINDOW_ALLOW_HIGHDPI);
	graph->gl_context = SDL_GL_CreateContext(graph->win);
	SDL_GetWindowSize(graph->win, &graph->win_width, &graph->win_height);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (glewInit() != GLEW_OK)
		exit(1);
	graph->ctx = nk_sdl_init(graph->win);
	nk_sdl_font_stash_begin(&atlas);
	nk_sdl_font_stash_end();
}

void	sdl_quit(t_sdl *graph)
{
	nk_sdl_shutdown();
	SDL_GL_DeleteContext(graph->gl_context);
	SDL_DestroyWindow(graph->win);
	SDL_Quit();
}
