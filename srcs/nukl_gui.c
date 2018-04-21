/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nukl_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:04:37 by malexand          #+#    #+#             */
/*   Updated: 2017/09/26 17:46:19 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	nukl_gui(t_param *param)
{
	const struct nk_vec2 sizeButton = {
		470.0,
		150.0
	};
	const char *filter[5] = {
		"None",
		"Cartoon",
		"Greyscale",
		"Sepia",
		"Blur"
	};
	
	if (nk_begin(param->graph->ctx, "RT UI", nk_rect(0, 0, WINDOW_GUI_WIDTH,
		WINDOW_GUI_HEIGHT), NK_WINDOW_SCALE_LEFT))
	{
		nk_layout_row_begin(param->graph->ctx, NK_STATIC, 30, 3);
		{
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, "Anti aliasing:", NK_TEXT_RIGHT);
			nk_layout_row_push(param->graph->ctx, 200);
			nk_slider_int(param->graph->ctx, MIN_ANTI_ALIASING, &param->macro.anti_aliasing, MAX_ANTI_ALIASING, STEP_ANTI_ALIASING);
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, ft_itoa(param->macro.anti_aliasing), NK_TEXT_CENTERED);
		}
		nk_layout_row_begin(param->graph->ctx, NK_STATIC, 30, 3);
		{
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, "Recursion:", NK_TEXT_RIGHT);
			nk_layout_row_push(param->graph->ctx, 200);
			nk_slider_int(param->graph->ctx, MIN_RECURSION, &param->macro.recursion, MAX_RECURSION, STEP_RECURSION);
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, ft_itoa(param->macro.recursion), NK_TEXT_CENTERED);
		}
		nk_layout_row_begin(param->graph->ctx, NK_STATIC, 30, 3);
		{
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, "Cartoon factor:", NK_TEXT_RIGHT);
			nk_layout_row_push(param->graph->ctx, 200);
			nk_slider_int(param->graph->ctx, MIN_CARTOON_FACTOR, &param->macro.cartoon_factor, MAX_CARTOON_FACTOR, STEP_CARTOON_FACTOR);
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, ft_itoa(param->macro.cartoon_factor), NK_TEXT_CENTERED);
		}
		nk_layout_row_begin(param->graph->ctx, NK_STATIC, 30, 3);
		{
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, "Blur radius:", NK_TEXT_RIGHT);
			nk_layout_row_push(param->graph->ctx, 200);
			nk_slider_int(param->graph->ctx, MIN_BLUR_RADIUS, &param->macro.blur_radius, MAX_BLUR_RADIUS, STEP_BLUR_RADIUS);
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, ft_itoa(param->macro.blur_radius), NK_TEXT_CENTERED);
		}
		nk_layout_row_begin(param->graph->ctx, NK_STATIC, 30, 3);
		{
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, "Rotation:", NK_TEXT_RIGHT);
			nk_layout_row_push(param->graph->ctx, 200);
			nk_slider_int(param->graph->ctx, MIN_ROTATION_ANGLE, &param->macro.rotation_angle, MAX_ROTATION_ANGLE, STEP_ROTATION_ANGLE);
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, ft_itoa(param->macro.rotation_angle), NK_TEXT_CENTERED);
		}
		nk_layout_row_begin(param->graph->ctx, NK_STATIC, 30, 3);
		{
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, "Specular exp:", NK_TEXT_RIGHT);
			nk_layout_row_push(param->graph->ctx, 200);
			nk_slider_int(param->graph->ctx, MIN_SPECULAR_EXP, &param->macro.specular_exp, MAX_SPECULAR_EXP, STEP_SPECULAR_EXP);
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, ft_itoa(param->macro.specular_exp), NK_TEXT_CENTERED);
		}
		nk_layout_row_begin(param->graph->ctx, NK_STATIC, 30, 3);
		{
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, "K Ambience:", NK_TEXT_RIGHT);
			nk_layout_row_push(param->graph->ctx, 200);
			nk_slider_int(param->graph->ctx, MIN_K_AMBIENCE, &param->macro.k_ambience, MAX_K_AMBIENCE, STEP_K_AMBIENCE);
			nk_layout_row_push(param->graph->ctx, 100);
			nk_label(param->graph->ctx, ft_itoa(param->macro.k_ambience), NK_TEXT_CENTERED);
		}
		nk_layout_row_begin(param->graph->ctx, NK_STATIC, 30, 1);
		{
			nk_layout_row_push(param->graph->ctx, 400);
			param->macro.filter = nk_combo(param->graph->ctx, filter, 5, param->macro.filter, 20, sizeButton);
		}
		nk_layout_space_begin(param->graph->ctx, NK_STATIC, 20, INT_MAX);
		nk_layout_space_push(param->graph->ctx, nk_rect(15, 0, 40, 20));
		if (nk_button_label(param->graph->ctx, "REFRESH"))
			mprintf(1, "Refresh engaged\n");
		nk_layout_space_end(param->graph->ctx);
	}
	nk_end(param->graph->ctx);
	SDL_GL_MakeCurrent(param->graph->win_gl, param->graph->gl_context);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
	SDL_GL_SwapWindow(param->graph->win_gl);
}
