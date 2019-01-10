/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 21:42:37 by malexand          #+#    #+#             */
/*   Updated: 2019/01/12 14:22:13 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_objects.h"

/*
** This functions take a pointer on the first double of array and use
** pointer arithmetic to increment it and find the two other
*/

void	nukl_objects_show_pos(t_param *param, double *pos)
{
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 15, 6);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_label(param->graph->ctx, "Position:", NK_TEXT_ALIGN_CENTERED);
	}
	nk_layout_row_end(param->graph->ctx);
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "x:", MIN_DOUBLE_OBJECT, pos,
			MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		pos++;
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "y:", MIN_DOUBLE_OBJECT, pos,
			MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		pos++;
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "z:", MIN_DOUBLE_OBJECT, pos,
			MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
	}
	nk_layout_row_end(param->graph->ctx);
}

void	nukl_objects_show_edit_double(t_param *param, char *name,
double *dbl, double step)
{
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_property_double(param->graph->ctx, name, MIN_DOUBLE_OBJECT, dbl,
			MAX_DOUBLE_OBJECT, step, 0.2f);
	}
	nk_layout_row_end(param->graph->ctx);
}

void	gui_normal_effect(t_param *param)
{
	int						tmp_normal;
	const char				*effects[2] = {"None", "Sinus"};
	const struct nk_vec2	size_button = {470.0, 150.0};

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 15, 1);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_label(param->graph->ctx, "Normal effect:", NK_TEXT_ALIGN_CENTERED);
	}
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 1);
	nk_layout_row_push(param->graph->ctx, 1.0f);
	tmp_normal = nk_combo(param->graph->ctx, effects, 2,
		param->graph->current_object->effects.normal, 30, size_button);
	if (param->graph->current_object->effects.normal != tmp_normal)
	{
		param->graph->current_object->effects.normal = tmp_normal;
		param->up_img.process = FALSE;
	}
	nk_layout_row_end(param->graph->ctx);
}

void	gui_text_stretcher(t_param *param)
{
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 20, 2);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_property_double(param->graph->ctx, "Texture stretch:", 0.2f,
			&param->graph->current_object->texture_stretch,
			10.0f, 0.2f, 0.2f);
	}
	nk_layout_row_end(param->graph->ctx);
}
