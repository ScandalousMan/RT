#include "rt.h"

t_object	*closest_object(t_param *param, double *from, double *to)
{
	param->obj_d= -1.0;
	param->tmp_object = param->objects;

	while (param->tmp_object)
	{
		if (param->current_object && param->tmp_object->num == param->current_object->num)
			param->tmp_object = param->tmp_object->next;
		if (param->tmp_object)
		{
			param->tmp_d = distance_calc(param->tmp_object, param, from, to);
			if (param->tmp_d > 0.0 && (param->obj_d < 0.0 || param->tmp_d < param->obj_d))
			{
				param->obj_d = param->tmp_d;
					param->intersect_object = param->tmp_object;
			}
			param->tmp_object = param->tmp_object->next;
		}
	}
	return (param->intersect_object);
}

void		update_normal_vector(t_object *tmp, t_param *param)
{
	if (tmp->type == 1)
		vec_soustraction(param->x, ((t_sphere*)(tmp->dim))->center, param->n);
	else if (tmp->type == 2)
	{
		vec_copy(((t_plane*)(tmp->dim))->n, param->n);
		if (scalar_product(param->n, param->v) > 0.0)
			vec_multiply(-1.0, param->n, param->n);
	}
	if (tmp->type == 3)
	{
		vec_soustraction(param->x, ((t_cone*)(tmp->dim))->org, param->n);
		vec_multiply(1.0 / scalar_product(param->n, ((t_cone*)(tmp->dim))->u) * vec_norm(param->n) * vec_norm(param->n), ((t_cone*)(tmp->dim))->u, tmp->tmp_vec);
		vec_soustraction(param->n, tmp->tmp_vec, param->n);
	}
	if (tmp->type == 4)
	{
		vec_soustraction(param->x, ((t_cylindre*)(tmp->dim))->org, param->n);
		vec_multiply(scalar_product(param->n, ((t_cylindre*)(tmp->dim))->u), ((t_cylindre*)(tmp->dim))->u, tmp->tmp_vec);
		vec_soustraction(param->n, tmp->tmp_vec, param->n);
	}
	vec_to_unit_norm(param->n);
}

t_object	*object_intersection(t_param *param, double *from, double *to)
{
	param->intersect_object = NULL;
	if (param->current_object)
	{
		closest_object(param, from, param->l);
		if (param->obj_d > pt_dist(from, param->tmp_light->src))
			param->intersect_object = NULL;
	}
	else
	{
		param->current_object = closest_object(param, from, to);
		if (param->current_object)
		{
			vec_multiply(param->obj_d - param->epsilon, param->v, param->x);
			pt_translated(param->eye, param->x, param->x);
			update_normal_vector(param->current_object, param);
		}
	}
	return (param->intersect_object);
}