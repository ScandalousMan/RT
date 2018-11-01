/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:43:38 by itsalex           #+#    #+#             */
/*   Updated: 2018/08/29 14:43:41 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	distance_to_quadric(t_object *tmp, double *from, double *to)
{
	return (vec_norm(to) * second_level(quadric_first_term((t_quadric*)(tmp->dim), to),
		quadric_second_term((t_quadric*)(tmp->dim), from, to), quadric_third_term((t_quadric*)(tmp->dim), from)));
}

void	update_normal_quadric(t_quadric *tmp, t_path *path)
{
	path->valid_n[0] = 2.0 * tmp->a * (path->valid_x[0] - tmp->center[0]) +
		(tmp->d + tmp->b) * (path->valid_x[1] - tmp->center[1]) +
		(tmp->g + tmp->c) * (path->valid_x[2] - tmp->center[2]);
	path->valid_n[1] = 2.0 * tmp->e * (path->valid_x[1] - tmp->center[1]) +
		(tmp->d + tmp->b) * (path->valid_x[0] - tmp->center[0]) +
		(tmp->h + tmp->f) * (path->valid_x[2] - tmp->center[2]);
	path->valid_n[2] = 2.0 * tmp->i * (path->valid_x[2] - tmp->center[2]) +
		(tmp->h + tmp->f) * (path->valid_x[1] - tmp->center[1]) +
		(tmp->g + tmp->c) * (path->valid_x[0] - tmp->center[0]);
}

int		is_inside_quadric(double *pt, t_quadric *tmp)
{
	return (
		tmp->a * (pt[0] - tmp->center[0]) * (pt[0] - tmp->center[0]) +
		tmp->d * (pt[0] - tmp->center[0]) * (pt[1] - tmp->center[1]) + 
		tmp->g * (pt[0] - tmp->center[0]) * (pt[2] - tmp->center[2]) +
		tmp->b * (pt[1] - tmp->center[1]) * (pt[0] - tmp->center[0]) +
		tmp->e * (pt[1] - tmp->center[1]) * (pt[1] - tmp->center[1]) +
		tmp->h * (pt[1] - tmp->center[1]) * (pt[2] - tmp->center[2]) +
		tmp->c * (pt[2] - tmp->center[2]) * (pt[0] - tmp->center[0]) +
		tmp->f * (pt[2] - tmp->center[2]) * (pt[1] - tmp->center[1]) +
		tmp->i * (pt[2] - tmp->center[2]) * (pt[2] - tmp->center[2]) - tmp->r * tmp->r <= 0.0 ? 1 : 0);
}

double *quadric_position(double *pt, t_object *obj)
{
	if (pt)
		return (obj->uv_map);
	return (obj->uv_map);
}

void	update_quadric(t_object *obj, t_param *param)
{
	pt_translated(((t_quadric*)(obj->dim))->center, obj->translation, ((t_quadric*)(obj->dim))->center);
	// fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "rotation")->value));
	// rotation_matrice(tr[0], tr[1], tr[2], param);
	//rotation quadrique
	ref_move(obj, param);
	limits_move(((t_plane*)(obj->dim))->ref, obj, param);
	reset_moves(obj);
}
