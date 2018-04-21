#include "rt.h"

t_object	*closest_object(t_param *param, double *from, double *to, t_path *path)
{
	param->obj_d= -1.0;
	t_object *objs = param->objects;

	while (objs)
	{
		if (path->current_object && objs->num == path->current_object->num)
			objs = objs->next;
		if (objs)
		{
			param->tmp_d = distance_calc(objs, param, from, to);
			if (param->tmp_d > 0.0 && (param->obj_d < 0.0 || param->tmp_d < param->obj_d))
			{
				param->obj_d = param->tmp_d;
					param->intersect_object = objs;
			}
			objs = objs->next;
		}
	}
	return (param->intersect_object);
}

void		update_normal_vector(t_object *tmp, t_path *path)
{
	if (tmp->type == 1)
		update_normal_sphere(tmp, path);
	else if (tmp->type == 2)
		update_normal_plane(tmp, path);
	else if (tmp->type == 3)
		update_normal_cone(tmp, path);
	else if (tmp->type == 4)
		update_normal_cylindre(tmp, path);
	vec_to_unit_norm(path->n);
}
#include <rt_objects.h>
t_object	*object_intersection(t_param *param, double *from, double *to,
t_path *path)
{
	param->intersect_object = NULL;
	if (path->current_object)
	{
		closest_object(param, from, path->l, path);
		if (param->tmp_light->type == RTSPOT && param->obj_d * param->obj_d > pt_dist_root(from, param->tmp_light->src))
			param->intersect_object = NULL;
	}
	else
	{
		path->current_object = closest_object(param, from, to, path);
		if (path->current_object)
		{
			vec_multiply(param->obj_d - param->epsilon, path->v, path->x);
			pt_translated(from, path->x, path->x);
			update_normal_vector(path->current_object, path);
		}
	}
	return (param->intersect_object);
}
