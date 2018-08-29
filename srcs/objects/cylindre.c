/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:43:25 by itsalex           #+#    #+#             */
/*   Updated: 2018/08/29 14:43:26 by itsalex          ###   ########.fr       */
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
	vec_soustraction(path->valid_x, ((t_cylindre*)(tmp->dim))->org, path->valid_n);
	vec_multiply(scalar_product(path->valid_n, ((t_cylindre*)(tmp->dim))->u), ((t_cylindre*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(path->valid_n, tmp->tmp_vec, path->valid_n);
}

int		is_inside_cylindre(double *pt, t_object *tmp)
{
	vec_soustraction(pt, ((t_cylindre*)(tmp->dim))->org, tmp->tmp_vec);
	vec_multiply(scalar_product(((t_cylindre*)(tmp->dim))->u, tmp->tmp_vec), ((t_cylindre*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(tmp->tmp_vec, pt, tmp->tmp_vec);
	pt_translated(tmp->tmp_vec, ((t_cylindre*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(tmp->tmp_vec) > ((t_cylindre*)(tmp->dim))->radius ? 0 : 1);
}

double *cylindre_position(double *pt, t_object *obj)
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
