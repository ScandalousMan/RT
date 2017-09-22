/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2017/09/22 19:21:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

int     main(/*int argc, char** argv*/)
{
	t_sdl	*graph;
    struct	nk_font_atlas *atlas;

	graph = init_struct_win();
	init_sdl2(graph);
    graph->ctx = nk_sdl_init(graph->win);
    nk_sdl_font_stash_begin(&atlas);
    nk_sdl_font_stash_end();

    graph->background = nk_rgb(0, 0, 0);
    while (graph->input[SDL_SCANCODE_ESCAPE] == '0')
    {
		pull_evts(graph);
        /* GUI */
		if (nk_begin(graph->ctx, "RT UI", nk_rect(50, 50, 500, 200),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE|NK_WINDOW_CLOSABLE))
            nk_menubar_begin(graph->ctx);
        {
            nk_layout_row_begin(graph->ctx, NK_STATIC, 25, 2);
            nk_layout_row_push(graph->ctx, 45);
            if (nk_menu_begin_label(graph->ctx, "FILE", NK_TEXT_LEFT, nk_vec2(120, 200))) {
                nk_layout_row_dynamic(graph->ctx, 30, 1);
                nk_menu_item_label(graph->ctx, "OPEN", NK_TEXT_LEFT);
                nk_menu_item_label(graph->ctx, "CLOSE", NK_TEXT_CENTERED);
                nk_menu_end(graph->ctx);
            }
            nk_layout_row_push(graph->ctx, 45);
            if (nk_menu_begin_label(graph->ctx, "EDIT", NK_TEXT_LEFT, nk_vec2(120, 200))) {
                nk_layout_row_dynamic(graph->ctx, 30, 1);
                nk_menu_item_label(graph->ctx, "COPY", NK_TEXT_LEFT);
                nk_menu_item_label(graph->ctx, "CUT", NK_TEXT_LEFT);
                nk_menu_item_label(graph->ctx, "PASTE", NK_TEXT_LEFT);
                nk_menu_end(graph->ctx);
            }
            nk_layout_row_end(graph->ctx);
            nk_menubar_end(graph->ctx);

            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;
            nk_layout_row_static(graph->ctx, 30, 80, 1);
            if (nk_button_label(graph->ctx, "button"))
                fprintf(stdout, "button pressed\n");
            nk_layout_row_dynamic(graph->ctx, 30, 2);
            if (nk_option_label(graph->ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(graph->ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(graph->ctx, 25, 1);
            nk_property_int(graph->ctx, "Compression:", 0, &property, 100, 10, 1);
        }
        nk_end(graph->ctx);

        /* Draw */
        {float bg[4];
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
        nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
        SDL_GL_SwapWindow(graph->win);}
	}
	nk_sdl_shutdown();
	SDL_GL_DeleteContext(graph->gl_context);
	SDL_DestroyWindow(graph->win);
	SDL_Quit();
	return (0);
}
