/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 16:04:52 by malexand          #+#    #+#             */
/*   Updated: 2017/09/23 14:41:12 by alex             ###   ########.fr       */
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
# define NK_IMPLEMENTATION
# define NK_SDL_GL3_IMPLEMENTATION

# include "nuklear.h"
# include "nuklear_sdl_gl3.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

# define MAX_VERTEX_MEMORY 512 * 1024
# define MAX_ELEMENT_MEMORY 128 * 1024

# define UNUSED(a) (void)a
# define MIN(a, b) ((a) < (b) ? (a) : (b))
# define MAX(a, b) ((a) < (b) ? (b) : (a))
# define LEN(a) (sizeof(a)/sizeof(a)[0])

# define TRUE '1'
# define FALSE '0'

typedef struct nk_context	t_nk_context;

typedef struct		s_sdl
{
	SDL_Window		*win;
	t_nk_context 	*ctx;
	SDL_GLContext	gl_context;
	struct nk_color	background;
	int				win_width;
	int				win_height;

	char			*input;
}					t_sdl;

/*
** SDL2 prototypes functions
*/

void	init_sdl2(t_sdl *graph);
void	pull_evts(t_sdl *graph);

/*
** Graph prototypes functions
*/

t_sdl	*init_struct_win();

#endif
