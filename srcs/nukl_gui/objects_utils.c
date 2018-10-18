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

void	nukl_objects_show_edit_double(t_param *param, char *name, double *dbl, double step)
{
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 1.0f);
		nk_property_double(param->graph->ctx, name, MIN_DOUBLE_OBJECT, dbl, MAX_DOUBLE_OBJECT, step, 0.2f);
	}
	nk_layout_row_end(param->graph->ctx);
}
