/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 20:43:35 by malexand          #+#    #+#             */
/*   Updated: 2019/01/12 14:08:28 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_objects.h"

void	gui_plan(t_param *param)
{
	t_plane *plane;

	plane = (t_plane *)param->graph->current_object->parsed;
	nukl_objects_show_pos(param, &plane->ref[0]);
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "n x:", MIN_DOUBLE_OBJECT,
			&plane->n[0], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "n y:", MIN_DOUBLE_OBJECT,
			&plane->n[1], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "n z:", MIN_DOUBLE_OBJECT,
			&plane->n[2], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
	}
	nk_layout_row_end(param->graph->ctx);
}

void	gui_cylinder(t_param *param)
{
	t_cylindre *cylindre;

	cylindre = (t_cylindre *)param->graph->current_object->parsed;
	nukl_objects_show_pos(param, &cylindre->org[0]);
	nukl_objects_show_edit_double(param, "Radius:", &cylindre->radius, 0.5);
	nk_layout_row_end(param->graph->ctx);
}

void	gui_sphere(t_param *param)
{
	t_sphere *sphere;

	sphere = (t_sphere *)param->graph->current_object->parsed;
	nukl_objects_show_pos(param, &sphere->center[0]);
	nukl_objects_show_edit_double(param, "Radius:", &sphere->radius, 0.5);
	nk_layout_row_end(param->graph->ctx);
}

void	gui_object_color(t_param *param)
{
	int r;
	int g;
	int b;

	r = ((param->graph->current_object->col >> 16) & 0xFF);
	g = ((param->graph->current_object->col >> 8) & 0xFF);
	b = ((param->graph->current_object->col) & 0xFF);
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 15, 1);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_label(param->graph->ctx, "Object color:", NK_TEXT_ALIGN_CENTERED);
	}
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 20, 2);
	{
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_int(param->graph->ctx, "Cr:", 0,
			&r, 255, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_int(param->graph->ctx, "Cg:", 0,
			&g, 255, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_int(param->graph->ctx, "Cb:", 0,
			&b, 255, 2.0f, 0.2f);
	}
	param->graph->current_object->col = rgb_color(r, g, b);
}

void	nukl_objects(t_param *param)
{
	if (nk_tree_push(param->graph->ctx, NK_TREE_NODE, "Object", NK_MAXIMIZED))
	{
		gui_object_color(param);
		gui_object_rotation(param);
		gui_object_translation(param);
		if (param->graph->current_object->type == RTSPHERE)
			gui_sphere(param);
		if (param->graph->current_object->type == RTPLAN)
			gui_plan(param);
		if (param->graph->current_object->type == RTCONE)
			gui_cone(param);
		if (param->graph->current_object->type == RTCYLINDER)
			gui_cylinder(param);
		if (param->graph->current_object->type == RTQUADRIC)
			gui_quadric(param);
		if (param->graph->current_object->type == RTCUBE)
			gui_cube(param);
		gui_text_stretcher(param);
		gui_color_effect(param);
		gui_normal_effect(param);
	}
	nk_tree_pop(param->graph->ctx);
}
