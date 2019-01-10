#include "rt.h"
#include "rt_objects.h"

void gui_plan(t_param *param)
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

void gui_cylinder(t_param *param)
{
	t_cylindre *cylindre;

	cylindre = (t_cylindre *)param->graph->current_object->parsed;
	nukl_objects_show_pos(param, &cylindre->org[0]);
	nukl_objects_show_edit_double(param, "Radius:", &cylindre->radius, 0.5);
	nk_layout_row_end(param->graph->ctx);
}

void gui_sphere(t_param *param)
{
	t_sphere *sphere;

	sphere = (t_sphere *)param->graph->current_object->parsed;
	nukl_objects_show_pos(param, &sphere->center[0]);
	nukl_objects_show_edit_double(param, "Radius:", &sphere->radius, 0.5);
	nk_layout_row_end(param->graph->ctx);
}

void gui_object_rotation(t_param *param)
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

void gui_object_translation(t_param *param)
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

void gui_color_effect(t_param *param)
{
	int tmp_color;
	const struct nk_vec2 sizeButton = {
		470.0,
		150.0};
	const char *effects[7] = {
		"None",
		"Chess",
		"Sierpinski",
		"Cloud",
		"Marble",
		"Wood",
		"Texture1"};

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 15, 1);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_label(param->graph->ctx, "Color effect:", NK_TEXT_ALIGN_CENTERED);
	}
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 1);
	nk_layout_row_push(param->graph->ctx, 1.0f);
	tmp_color = nk_combo(param->graph->ctx, effects, 7,
		param->graph->current_object->effects.color, 30, sizeButton);
	if (param->graph->current_object->effects.color != tmp_color)
	{
		param->graph->current_object->effects.color = tmp_color;
		param->up_img.process = TRUE;
	}
	nk_layout_row_end(param->graph->ctx);
}

void gui_normal_effect(t_param *param)
{
	int tmp_normal;
	const struct nk_vec2 sizeButton = {
		470.0,
		150.0};
	const char *effects[2] = {
		"None",
		"Sinus"};

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 15, 6);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_label(param->graph->ctx, "Normal effect:", NK_TEXT_ALIGN_CENTERED);
	}
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 1);
	nk_layout_row_push(param->graph->ctx, 1.0f);
	tmp_normal = nk_combo(param->graph->ctx, effects, 2,
		param->graph->current_object->effects.normal, 30, sizeButton);
	if (param->graph->current_object->effects.normal != tmp_normal)
	{
		param->graph->current_object->effects.normal = tmp_normal;
		param->up_img.process = FALSE;
	}
	nk_layout_row_end(param->graph->ctx);
}

void gui_object_color(t_param *param)
{
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 20, 2);
	{
		nk_layout_row_push(param->graph->ctx, 0.5f);
		nk_label(param->graph->ctx, "Object color:", NK_TEXT_ALIGN_CENTERED);
		nk_layout_row_push(param->graph->ctx, 0.5f);
		nk_property_int(param->graph->ctx, "Color:", INT_MIN,
						   &param->graph->current_object->col,
						   INT_MAX, 1, 1);
	}
}

void nukl_objects(t_param *param)
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
		gui_color_effect(param);
		gui_normal_effect(param);
	}
	nk_tree_pop(param->graph->ctx);
}