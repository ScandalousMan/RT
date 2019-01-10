/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 21:42:37 by malexand          #+#    #+#             */
/*   Updated: 2019/01/12 14:16:11 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_objects.h"

void	gui_object_rotation(t_param *param)
{
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 15, 6);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_label(param->graph->ctx, "Rotation:", NK_TEXT_ALIGN_CENTERED);
	}
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "Rx:", MIN_DOUBLE_OBJECT,
			&param->graph->current_object->rotation[0],
			MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "Ry:", MIN_DOUBLE_OBJECT,
			&param->graph->current_object->rotation[1],
			MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "Rz:", MIN_DOUBLE_OBJECT,
			&param->graph->current_object->rotation[2],
			MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
	}
	nk_layout_row_end(param->graph->ctx);
}

void	gui_object_translation(t_param *param)
{
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 15, 6);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_label(param->graph->ctx, "Translation:", NK_TEXT_ALIGN_CENTERED);
	}
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "Tx:", MIN_DOUBLE_OBJECT,
			&param->graph->current_object->translation[0],
			MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "Ty:", MIN_DOUBLE_OBJECT,
			&param->graph->current_object->translation[1],
			MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "Tz:", MIN_DOUBLE_OBJECT,
			&param->graph->current_object->translation[2],
			MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
	}
	nk_layout_row_end(param->graph->ctx);
}

void	gui_color_effect(t_param *param)
{
	int						tmp_color;
	const struct nk_vec2	size_button = {470.0, 150.0};
	const char				*effects[7] = {"None", "Chess",
		"Sierpinski", "Cloud", "Marble", "Wood", "Texture1"};

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 15, 1);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_label(param->graph->ctx, "Color effect:", NK_TEXT_ALIGN_CENTERED);
	}
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 1);
	nk_layout_row_push(param->graph->ctx, 1.0f);
	tmp_color = nk_combo(param->graph->ctx, effects, 7,
		param->graph->current_object->effects.color, 30, size_button);
	if (param->graph->current_object->effects.color != tmp_color)
	{
		param->graph->current_object->effects.color = tmp_color;
		param->up_img.process = TRUE;
	}
	nk_layout_row_end(param->graph->ctx);
}
