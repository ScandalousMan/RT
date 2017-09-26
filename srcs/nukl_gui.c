/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nukl_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:04:37 by malexand          #+#    #+#             */
/*   Updated: 2017/09/26 16:51:51 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

void	nukl_gui(t_sdl *graph)
{
	if (nk_begin(graph->ctx, "RT UI", nk_rect(0, 0, WINDOW_GUI_WIDTH,
		WINDOW_GUI_HEIGHT), NK_WINDOW_SCALE_LEFT))
	{
		nk_layout_space_begin(graph->ctx, NK_STATIC, 20, INT_MAX);
		nk_layout_space_push(graph->ctx, nk_rect(15, 0, 160, 20));
		if (nk_button_label(graph->ctx, "REFRESH"))
			mprintf(1, "Refresh engaged\n");
		nk_layout_space_end(graph->ctx);
	}
	nk_end(graph->ctx);
	SDL_GL_MakeCurrent(graph->win_gl, graph->gl_context);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
	SDL_GL_SwapWindow(graph->win_gl);
}
