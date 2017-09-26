/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 16:04:52 by malexand          #+#    #+#             */
/*   Updated: 2017/09/26 16:49:03 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOL_H
# define TOOL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include <assert.h>
# include <math.h>
# include <limits.h>
# include <time.h>

# include <GL/glew.h>
# include <SDL.h>
# include <SDL_opengl.h>

# include "../libft/incs/libft.h"

# define NK_INCLUDE_FIXED_TYPES
# define NK_INCLUDE_STANDARD_IO
# define NK_INCLUDE_STANDARD_VARARGS
# define NK_INCLUDE_DEFAULT_ALLOCATOR
# define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
# define NK_INCLUDE_FONT_BAKING
# define NK_INCLUDE_DEFAULT_FONT

# include "nuklear.h"
# include "nuklear_sdl_gl3.h"

# define WINDOW_GUI_WIDTH 200
# define WINDOW_GUI_HEIGHT 800
# define WINDOW_SDL_WIDTH 1000
# define WINDOW_SDL_HEIGHT 800

# define MAX_VERTEX_MEMORY 512 * 1024
# define MAX_ELEMENT_MEMORY 128 * 1024

# define UNUSED(a) (void)a
# define MIN(a,b) ((a) < (b) ? (a) : (b))
# define MAX(a,b) ((a) < (b) ? (b) : (a))
# define LEN(a) (sizeof(a)/sizeof(a)[0])

# define TRUE '1'
# define FALSE '0'

typedef struct nk_context		t_nk_context;
typedef struct nk_font_atlas	t_nk_font_atlas;

typedef enum nk_anti_aliasing	t_nk_anti_aliasing;

typedef struct					s_sdl
{
	SDL_Window					*win_gl;
	SDL_GLContext				gl_context;

	SDL_Window					*win_sdl;
	SDL_Renderer				*render_sdl;
	SDL_Surface					**surfs;

	char						*input;

	t_nk_context				*ctx;
}								t_sdl;

/*
** NK_API SDL Prototypes
*/

t_nk_context					*nk_sdl_init(SDL_Window *win);
void							nk_sdl_font_stash_begin(struct nk_font_atlas
									**atlas);
void							nk_sdl_font_stash_end(void);
int								nk_sdl_handle_event(SDL_Event *evt);
void							nk_sdl_render(t_nk_anti_aliasing
									nk_anti_aliasing,
									int max_vertex_buffer,
									int max_element_buffer);
void							nk_sdl_shutdown(void);
void							nk_sdl_device_destroy(void);
void							nk_sdl_device_create(void);

/*
** NK_API Prototypes
*/

/*
** Nuklear function
*/

void							nukl_gui(t_sdl *graph);

/*
** SDL2 Prototypes
*/

void							putpixel(SDL_Surface *surface, int x, int y,
									Uint32 pixel);
void							sdl_init(t_sdl *graph);
void							sdl_quit(t_sdl *graph);
void							sdl_pull_evts(t_sdl *graph);
void							sdl_draw(t_sdl *graph);

/*
** Graph prototype
*/

t_sdl							*graph_init(void);

#endif
