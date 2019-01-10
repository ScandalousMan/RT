/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:43:31 by itsalex           #+#    #+#             */
/*   Updated: 2019/01/12 13:58:36 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

double	distance_to_cone(t_object *tmp, double *from, double *to)
{
	vec_soustraction(from, ((t_cone*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(to) * second_level(cone_first_term(tmp, to),
		cone_second_term(tmp, to, tmp->tmp_vec),
		cone_third_term(tmp, tmp->tmp_vec)));
}

void	update_normal_cone(t_object *tmp, t_path *path)
{
	double	norm;

	vec_soustraction(path->valid_x, ((t_cone*)(tmp->dim))->org, path->valid_n);
	norm = vec_norm(path->valid_n);
	vec_multiply(1.0 / scalar_product(path->valid_n, ((t_cone*)(tmp->dim))->u) *
		norm * norm, ((t_cone*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(path->valid_n, tmp->tmp_vec, path->valid_n);
}

int		is_inside_cone(double *pt, t_object *tmp)
{
	vec_soustraction(pt, ((t_cone*)(tmp->dim))->org, tmp->tmp_vec);
	vec_to_unit_norm(tmp->tmp_vec);
	return (acos(ABS(scalar_product(((t_cone*)(tmp->dim))->u, tmp->tmp_vec))) <
		((t_cone*)(tmp->dim))->angle ? 1 : 0);
}

double	*cone_position(double *pt, t_object *obj)
{
	double	scalar;

	vec_soustraction(((t_cone*)(obj->dim))->org, pt, obj->tmp_vec);
	scalar = scalar_product(obj->tmp_vec, obj->ref.i) / 64.0;
	obj->uv_map[0] = scalar - floor(scalar);
	vec_to_unit_norm(obj->tmp_vec);
	obj->uv_map[1] = 0.5 + atan2(scalar_product(obj->ref.j, obj->tmp_vec),
		scalar_product(obj->ref.k, obj->tmp_vec)) / 2.0 / M_PI;
	return (obj->uv_map);
}

void	update_cone(t_object *obj, t_param *param)
{
	((t_cone*)(obj->dim))->angle = ((t_cone*)(obj->parsed))->angle;
	vec_copy(((t_cone*)(obj->parsed))->u, ((t_cone*)(obj->dim))->u);
	special_ref_updater(((t_cone*)(obj->dim))->u, obj);
	pt_translated(((t_cone*)(obj->parsed))->org, obj->translation,
		((t_cone*)(obj->dim))->org);
	ref_move(obj, param);
	limits_move(((t_cone*)(obj->dim))->org, obj, param);
	matrice_product(param->rot, ((t_cone*)(obj->dim))->u,
		((t_cone*)(obj->dim))->u);
}
