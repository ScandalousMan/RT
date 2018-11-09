#include "rt.h"
#include "rt_objects.h"

void gui_plan(t_param *param)
{
	t_plane *plane;

	plane = (t_plane *)param->graph->current_object->dim;
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

void gui_cylinder(t_param *param)
{
	t_cylindre *cylindre;

	cylindre = (t_cylindre *)param->graph->current_object->dim;
	nukl_objects_show_pos(param, &cylindre->org[0]);
	nukl_objects_show_edit_double(param, "Radius:", &cylindre->radius, 0.5);
	nk_layout_row_end(param->graph->ctx);
}

void gui_sphere(t_param *param)
{
	t_sphere *sphere;

	sphere = (t_sphere *)param->graph->current_object->dim;
	nukl_objects_show_pos(param, &sphere->center[0]);
	nukl_objects_show_edit_double(param, "Radius:", &sphere->radius, 0.5);
	nk_layout_row_end(param->graph->ctx);
}

void nukl_objects(t_param *param)
{
	if (nk_tree_push(param->graph->ctx, NK_TREE_NODE, "Object", NK_MAXIMIZED))
	{
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
		nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
		{
			nk_layout_row_push(param->graph->ctx, 0.33f);
			nk_property_double(param->graph->ctx, "rot x:", MIN_DOUBLE_OBJECT,
							   &param->graph->current_object->ref.i[0], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
			nk_layout_row_push(param->graph->ctx, 0.33f);
			nk_property_double(param->graph->ctx, "rot y:", MIN_DOUBLE_OBJECT,
							   &param->graph->current_object->ref.i[1], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
			nk_layout_row_push(param->graph->ctx, 0.33f);
			nk_property_double(param->graph->ctx, "rot z:", MIN_DOUBLE_OBJECT,
							   &param->graph->current_object->ref.i[2], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		}
		nk_layout_row_end(param->graph->ctx);
		nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
		{
			nk_layout_row_push(param->graph->ctx, 0.33f);
			nk_property_double(param->graph->ctx, "rot x:", MIN_DOUBLE_OBJECT,
							   &param->graph->current_object->ref.j[0], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
			nk_layout_row_push(param->graph->ctx, 0.33f);
			nk_property_double(param->graph->ctx, "rot y:", MIN_DOUBLE_OBJECT,
							   &param->graph->current_object->ref.j[1], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
			nk_layout_row_push(param->graph->ctx, 0.33f);
			nk_property_double(param->graph->ctx, "rot z:", MIN_DOUBLE_OBJECT,
							   &param->graph->current_object->ref.j[2], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		}
		nk_layout_row_end(param->graph->ctx);
		nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
		{
			nk_layout_row_push(param->graph->ctx, 0.33f);
			nk_property_double(param->graph->ctx, "rot x:", MIN_DOUBLE_OBJECT,
							   &param->graph->current_object->ref.k[0], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
			nk_layout_row_push(param->graph->ctx, 0.33f);
			nk_property_double(param->graph->ctx, "rot y:", MIN_DOUBLE_OBJECT,
							   &param->graph->current_object->ref.k[1], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
			nk_layout_row_push(param->graph->ctx, 0.33f);
			nk_property_double(param->graph->ctx, "rot z:", MIN_DOUBLE_OBJECT,
							   &param->graph->current_object->ref.k[2], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		}
		nk_layout_row_end(param->graph->ctx);
	}
	nk_tree_pop(param->graph->ctx);
}