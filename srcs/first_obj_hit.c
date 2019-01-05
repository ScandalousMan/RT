/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_obj_hit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 16:56:14 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/31 11:57:16 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

void		not_cut_updater(t_param *param, t_object *obj, t_path *path)
{
	if (param->is_cut != 1 && param->tmp_d > 0.0)
	{
		param->intersect_object = obj;
		param->obj_d = param->tmp_d;
		if (!param->is_for_light)
		{
			vec_multiply(param->obj_d - param->epsilon, path->to, path->x);
			pt_translated(path->from, path->x, path->x);
			vec_copy(path->valid_n, path->n);
		}
		else if (param->tmp_light->type != RTSPOT ||
			param->obj_d * param->obj_d < pt_dist_root(path->from,
				param->tmp_light->src))
		{
			param->tmp_light->tmp_col = rgb_ratio(color_absorber(obj->col,
				param->tmp_light->tmp_col), obj->transparency);
		}
	}
}

void		limit_checker(t_param *param, t_object *objs, t_path *path)
{
	t_limit		*limits;

	limits = objs->limits;
	while (limits && param->tmp_d > 0 && param->is_cut)
	{
		if (!is_in_limit(path->valid_x, limits))
		{
			param->tmp_d = plane_distance(path->from, path->to, limits->plane.n,
				limits->plane.ref);
			vec_multiply(param->tmp_d + param->epsilon, path->to,
				path->valid_x);
			pt_translated(path->from, path->valid_x, path->valid_x);
			if (param->tmp_d > 0 &&
				is_inside_object(path->valid_x, objs, limits))
			{
				param->is_cut = 0;
				vec_copy(limits->plane.n, path->valid_n);
			}
			else
				param->is_cut = 1;
		}
		limits = limits->next;
	}
	not_cut_updater(param, objs, path);
}

t_object	*first_obj_hit(t_param *param, double *from, double *to,
	t_path *path)
{
	t_object	*objs;

	param->obj_d = -1.0;
	objs = param->objects;
	while (objs)
	{
		if (!param->is_for_light || objs != path->current_object)
		{
			param->is_cut = -1;
			param->tmp_d = distance_calc(objs, from, to);
			if (param->tmp_d > 0.0 && (param->is_for_light ||
				(param->obj_d < 0.0 || param->tmp_d < param->obj_d)))
			{
				vec_multiply(param->tmp_d + param->epsilon, to, path->valid_x);
				pt_translated(from, path->valid_x, path->valid_x);
				update_normal_vector(objs, path, from);
				vec_copy(from, path->from);
				vec_copy(to, path->to);
				limit_checker(param, objs, path);
			}
		}
		objs = objs->next;
	}
	return (param->intersect_object);
}
