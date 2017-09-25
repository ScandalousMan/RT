/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:46:21 by malexand          #+#    #+#             */
/*   Updated: 2017/09/25 14:50:29 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

/*
** IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
** with blending, scissor, face culling, depth test and viewport and
** defaults everything back into a default state.
** Make sure to either a.) save and restore or b.) reset your own state after
** rendering the UI.
*/

void	sdl_draw(t_sdl *graph)
{
	float bg[4];

	nk_color_fv(bg, graph->background);
	SDL_GetWindowSize(graph->win, &graph->win_width, &graph->win_height);
	glViewport(0, 0, graph->win_width, graph->win_height);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(bg[0], bg[1], bg[2], bg[3]);
	nk_sdl_render(NK_ANTI_ALIASING_OFF, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
	SDL_GL_SwapWindow(graph->win);
}
