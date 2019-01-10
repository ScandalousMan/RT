/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:43:35 by itsalex           #+#    #+#             */
/*   Updated: 2019/01/10 21:59:43 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

double	plane_distance(double *from, double *to, double *n, double *ref)
{
	if (scalar_product(n, to) == 0.0)
	{
		if (n[0] * (ref[0] - from[0]) + n[1] * (ref[1] * from[1]) +
				n[2] * (ref[2] - from[2]) == 0.0)
			return (0.0);
		return (-1.0);
	}
	else
		return ((n[0] * (ref[0] - from[0]) + n[1] * (ref[1] - from[1]) +
			n[2] * (ref[2] - from[2])) / scalar_product(n, to));
}

double	distance_to_plane(t_object *tmp, double *from, double *to)
{
	return (plane_distance(from, to, ((t_plane*)(tmp->dim))->n,
		((t_plane*)(tmp->dim))->ref));
}

void	update_normal_plane(t_object *tmp, t_path *path)
{
	vec_copy(((t_plane*)(tmp->dim))->n, path->valid_n);
	if (scalar_product(path->valid_n, path->v) > 0.0)
		vec_multiply(-1.0, path->valid_n, path->valid_n);
}

double	*plane_position(double *pt, t_object *obj)
{
	double scalar;

	vec_soustraction(pt, ((t_plane*)(obj->dim))->ref, obj->tmp_vec);
	scalar = scalar_product(obj->tmp_vec, obj->ref.i) / 64.0;
	obj->uv_map[0] = scalar - floor(scalar);
	scalar = scalar_product(obj->tmp_vec, obj->ref.j) / 64.0;
	obj->uv_map[1] = scalar - floor(scalar);
	return (obj->uv_map);
}

void	update_plane(t_object *obj, t_param *param)
{
	vec_copy(((t_plane*)(obj->parsed))->n, ((t_plane*)(obj->dim))->n);
	special_ref_updater(((t_plane*)(obj->dim))->n, obj);
	pt_translated(((t_plane*)(obj->parsed))->ref, obj->translation,
		((t_plane*)(obj->dim))->ref);
	ref_move(obj, param);
	limits_move(((t_plane*)(obj->dim))->ref, obj, param);
	matrice_product(param->rot, ((t_plane*)(obj->dim))->n,
		((t_plane*)(obj->dim))->n);
}
