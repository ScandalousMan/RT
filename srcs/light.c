#include "rt_objects.h"

t_light	*light_copy(t_light *src)
{
	t_light	*copy;

	if (!src)
		return (NULL);
	if (!(copy = duplicate(src, sizeof(t_light))))
		return (NULL);
	if (src->next)
	{
		if (!(copy->next = light_copy(src->next)))
			return (NULL);
	}
	return (copy);
}

t_object	*light_masked(t_param *param, double *from, double *to, t_path *path)
{
	// if (point_display(param))
	// 	printf("----- LIGHTS -----\n");
	param->intersect_object = NULL;
	param->is_for_light = 1;
	closest_object(param, from, to, path);
	// if (point_display(param))
	// 	printf("light type: %d\n", param->tmp_light->type);
	if (param->tmp_light->type == RTSPOT && param->obj_d > 0.0 && param->obj_d * param->obj_d > pt_dist_root(from, param->tmp_light->src))
		param->intersect_object = NULL;
	return (param->intersect_object);
}
