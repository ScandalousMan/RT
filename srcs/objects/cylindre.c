/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:43:25 by itsalex           #+#    #+#             */
/*   Updated: 2019/01/10 22:36:06 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

double	distance_to_cylindre(t_object *tmp, double *from, double *to)
{
	vec_soustraction(from, ((t_cylindre*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(to) * second_level(cylindre_first_term(tmp, to),
		cylindre_second_term(tmp, to), cylindre_third_term(tmp)));
}

void	update_normal_cylindre(t_object *tmp, t_path *path)
{
	vec_soustraction(path->valid_x, ((t_cylindre*)(tmp->dim))->org,
		path->valid_n);
	vec_multiply(scalar_product(path->valid_n, ((t_cylindre*)(tmp->dim))->u),
		((t_cylindre*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(path->valid_n, tmp->tmp_vec, path->valid_n);
}

int		is_inside_cylindre(double *pt, t_object *tmp)
{
	vec_soustraction(pt, ((t_cylindre*)(tmp->dim))->org, tmp->tmp_vec);
	vec_multiply(scalar_product(((t_cylindre*)(tmp->dim))->u, tmp->tmp_vec),
		((t_cylindre*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(tmp->tmp_vec, pt, tmp->tmp_vec);
	pt_translated(tmp->tmp_vec, ((t_cylindre*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(tmp->tmp_vec) > ((t_cylindre*)(tmp->dim))->radius ? 0 : 1);
}

double	*cylindre_position(double *pt, t_object *obj)
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

void	update_cylindre(t_object *obj, t_param *param)
{
	((t_cylindre*)(obj->dim))->radius = ((t_cylindre*)(obj->parsed))->radius;
	vec_copy(((t_cylindre*)(obj->parsed))->u, ((t_cylindre*)(obj->dim))->u);
	special_ref_updater(((t_cylindre*)(obj->dim))->u, obj);
	pt_translated(((t_cylindre*)(obj->parsed))->org, obj->translation,
		((t_cylindre*)(obj->dim))->org);
	ref_move(obj, param);
	limits_move(((t_cylindre*)(obj->dim))->org, obj, param);
	matrice_product(param->rot, ((t_cylindre*)(obj->dim))->u,
		((t_cylindre*)(obj->dim))->u);
}
