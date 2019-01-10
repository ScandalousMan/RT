/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:04:37 by malexand          #+#    #+#             */
/*   Updated: 2019/01/12 14:23:33 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	nukl_save(t_param *param)
{
	static char		name[16];
	static int		len;
	nk_flags		active;

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 2);
	{
		nk_layout_row_push(param->graph->ctx, 0.5f);
		active = nk_edit_string(param->graph->ctx, NK_EDIT_FIELD
			| NK_EDIT_SIG_ENTER, name, &len, 16, nk_filter_default);
		nk_layout_row_push(param->graph->ctx, 0.5f);
		if (nk_button_label(param->graph->ctx, "SAVE")
		|| (active & NK_EDIT_COMMITED))
		{
			save_img(param, ft_strdup(name));
			ft_strclr(name);
			len = 0;
		}
	}
	nk_layout_row_end(param->graph->ctx);
}

void	nukl_refresh(t_param *param)
{
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 2);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		if (nk_button_label(param->graph->ctx, "UPDATE"))
		{
			param->up_img.process = TRUE;
			param->up_img.post_process = TRUE;
			mprintf(1, "Refresh engaged\n");
		}
	}
	nk_layout_row_end(param->graph->ctx);
}

void	nukl_gui(t_param *param)
{
	if (nk_begin(param->graph->ctx, "RT UI", nk_rect(0, 0, WINDOW_GUI_WIDTH,
	WINDOW_GUI_HEIGHT), NK_WINDOW_SCALE_LEFT))
	{
		if (nk_tree_push(param->graph->ctx, NK_TREE_NODE,
		"Global Settings", NK_MAXIMIZED))
		{
			global_settings_1(param);
			global_settings_2(param);
			global_settings_3(param);
			global_settings_4(param);
			global_settings_filters(param);
			nk_tree_pop(param->graph->ctx);
		}
		nukl_camera(param);
		if (param->graph->current_object)
			nukl_objects(param);
		nukl_save(param);
		nukl_refresh(param);
	}
	nk_end(param->graph->ctx);
	SDL_GL_MakeCurrent(param->graph->win_gl, param->graph->gl_context);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
	SDL_GL_SwapWindow(param->graph->win_gl);
}
