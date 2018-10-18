#include "rt.h"
#include "rt_objects.h"

void gui_cone(t_param *param)
{
	t_cone *cone;

	cone = (t_cone *)param->graph->current_object->dim;
	nukl_objects_show_pos(param, &cone->org[0]);
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "u x:", MIN_DOUBLE_OBJECT,
			&cone->u[0], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "u y:", MIN_DOUBLE_OBJECT,
			&cone->u[1], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "u z:", MIN_DOUBLE_OBJECT,
			&cone->u[2], MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
	}
	nk_layout_row_end(param->graph->ctx);
	nukl_objects_show_edit_double(param, "Angle:", &cone->angle, 0.5);
	nk_layout_row_end(param->graph->ctx);
}

void gui_quadric(t_param *param)
{
	t_quadric *quadric;

	quadric = (t_quadric *)param->graph->current_object->dim;
	nukl_objects_show_pos(param, &quadric->center[0]);
}

void gui_tore(t_param *param)
{
	t_tore *tore;

	tore = (t_tore *)param->graph->current_object->dim;
	nukl_objects_show_pos(param, &tore->center[0]);
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 0.5f);
		nk_property_double(param->graph->ctx, "r1:", MIN_DOUBLE_OBJECT,
			&tore->r1, MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.5f);
		nk_property_double(param->graph->ctx, "r2:", MIN_DOUBLE_OBJECT,
			&tore->r2, MAX_DOUBLE_OBJECT, 2.0f, 0.2f);
	}
}
