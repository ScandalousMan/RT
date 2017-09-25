/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2017/09/25 13:59:47 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation.h"
#include "tool.h"

int     main(int argc, char** argv)
{
	t_sdl	*graph;
    
	(void)argc;
    (void)argv;
	if ((graph = graph_init()) == NULL)
		return (0);
    sdl_init(graph);

    graph->background = nk_rgb(0, 0, 0);
    while (graph->input[SDL_SCANCODE_ESCAPE] == FALSE)
    {
        sdl_pull_evts(graph);
        nukl_gui(graph);
        /* Draw */
        float bg[4];
        nk_color_fv(bg, graph->background);
        SDL_GetWindowSize(graph->win, &graph->win_width, &graph->win_height);
        glViewport(0, 0, graph->win_width, graph->win_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg[0], bg[1], bg[2], bg[3]);
        /* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_sdl_render(NK_ANTI_ALIASING_OFF, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
        SDL_GL_SwapWindow(graph->win);
    }
    sdl_quit(graph);
    return 0;
}
