#include "rt.h"

t_object	*closest_object(t_param *param, double *from, double *to, t_path *path)
{
	param->obj_d= -1.0;
	t_object *objs = param->objects;
	t_limit	*limits;
	t_limit *is_cut_limit;

	while (objs)
	{
		param->is_cut = 0;
		param->tmp_d_cut = -1.0;
		param->tmp_d = distance_calc(objs, param, from, to);
		// on compute ici la distance en prenant en compte le plan de coupe
		if (param->tmp_d > 0.0 && (param->obj_d < 0.0 || param->tmp_d < param->obj_d))
		{
			/* on parcourt les limites */
			limits = objs->limits;
			while (limits && param->tmp_d > 0.0)
			{
				param->tmp_d_cut = plane_distance(from, to, limits->plane.n, limits->plane.ref);
				if ((param->tmp_d_cut - param->tmp_d) * scalar_product(to, limits->plane.n) < 0.0)
				{
					vec_multiply(param->tmp_d_cut - param->epsilon, to, path->tmp_x);
					pt_translated(from, path->tmp_x, path->tmp_x);
					if (is_inside_object(path->tmp_x, objs))
					{
						param->is_cut = 1;
						is_cut_limit = limits;
						param->tmp_d = param->tmp_d_cut;
						if (!param->is_for_light)
						{
							vec_copy(path->tmp_x, path->final_x);
							vec_copy(limits->plane.n, path->final_n);
						}
					}
					else
					{
						param->tmp_d = -1.0;
					}
				}
				limits = limits->next;
			}
			if (param->tmp_d > 0.0 && (param->obj_d < 0.0 || param->tmp_d < param->obj_d))
			{
				if (!param->is_cut && !param->is_for_light)
				{
					vec_multiply(param->tmp_d - param->epsilon, to, path->x);
					pt_translated(from, path->x, path->x);
					update_normal_vector(objs, path);
				} else if (!param->is_for_light) {
					limits = objs->limits;
					while (limits && param->tmp_d > 0)
					{
						vec_soustraction(path->final_x, limits->plane.ref, path->tmp_x);
						if (limits != is_cut_limit && scalar_product(path->tmp_x, limits->plane.n) > 0)
						{
							param->tmp_d = -1.0;
						}
						limits = limits->next;
					}
					if (param->tmp_d > 0)
					{
						vec_copy(path->final_x, path->x);
						vec_copy(path->final_n, path->n);	
					}
				}
				if (param->tmp_d > 0)
				{
					param->obj_d = param->tmp_d;
						param->intersect_object = objs;
				}
			}
		}
		objs = objs->next;
	}
	return (param->intersect_object);
}

int			is_inside_object(double *pt, t_object *obj)
{
	if (obj->type == 1)
		return is_inside_sphere(pt, obj);
	else if (obj->type == 2)
		return is_inside_plane(pt, obj);
	else if (obj->type == 3)
		return is_inside_cone(pt, obj);
	else if (obj->type == 4)
		return is_inside_cylindre(pt, obj);
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
	vec_to_unit_norm(path->n);
}
