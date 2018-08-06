#include "rt.h"

t_object	*closest_object(t_param *param, double *from, double *to, t_path *path)
{
	param->obj_d= -1.0;
	t_object *objs = param->objects;
	t_limit	*limits;

	while (objs)
	{
		if (!param->is_for_light || objs != path->current_object)
		{
			param->is_cut = 0;
			param->tmp_d = distance_calc(objs, param, from, to);
			if (param->tmp_d > 0.0 && (param->obj_d < 0.0 || param->tmp_d < param->obj_d))
			{
				vec_multiply(param->tmp_d + param->epsilon, to, path->valid_x);
				pt_translated(from, path->valid_x, path->valid_x);
				update_normal_vector(objs, path);
				limits = objs->limits;
				while (limits && param->tmp_d > 0)
				{			
					if (!is_in_limit(path->valid_x, limits))
					{
						param->tmp_d = plane_distance(from, to, limits->plane.n, limits->plane.ref);
						vec_multiply(param->tmp_d + param->epsilon, to, path->valid_x);
						pt_translated(from, path->valid_x, path->valid_x);
						if (param->tmp_d > 0 && is_inside_object(objs, path))
						{
							param->is_cut = 1;
							vec_copy(limits->plane.n, path->valid_n);
						}
						else
							param->tmp_d = -1;
					}
					limits = limits->next;
				}
				if (param->is_cut)
				{
					limits = objs->limits;
					while (limits && param->tmp_d > 0)
					{
						if (!is_in_limit(path->valid_x, limits))
							param->tmp_d = -1;
						limits = limits->next;
					}
				}
				if (param->tmp_d > 0.0)
				{
					param->intersect_object = objs;
					param->obj_d = param->tmp_d;
					if (!param->is_for_light)
					{
						vec_multiply(param->obj_d - param->epsilon, to, path->x);
						pt_translated(from, path->x, path->x);
						vec_copy(path->valid_n, path->n);
					}
				}
			}
		}
		objs = objs->next;
	}
	return (param->intersect_object);
}

int			is_inside_object(t_object *obj, t_path *path)
{
	if (obj->type == 1)
		return is_inside_sphere(obj, path);
	else if (obj->type == 2)
		return is_inside_plane(obj, path);
	else if (obj->type == 3)
		return is_inside_cone(obj, path);
	else if (obj->type == 4)
		return is_inside_cylindre(obj, path);
	else if (obj->type == 5)
		return is_inside_quadric(obj, path);
	return 0;
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
	else if (tmp->type == 5)
		update_normal_quadric((t_quadric*)(tmp->dim), path);
	vec_to_unit_norm(path->valid_n);
}
