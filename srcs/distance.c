/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 16:56:14 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/31 11:57:16 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	distance_to_sphere(t_object *tmp, double *from, double *to)
{
	double	a;
	double	d;

	d = -1.0;
	if ((a = second_level(vec_norm(to) * vec_norm(to),
			2.0 * (to[0] * (from[0] - ((t_sphere*)(tmp->dim))->center[0]) +
			to[1] * (from[1] - ((t_sphere*)(tmp->dim))->center[1]) +
			to[2] * (from[2] - ((t_sphere*)(tmp->dim))->center[2])),
			(from[0] - ((t_sphere*)(tmp->dim))->center[0]) * (from[0] -
			((t_sphere*)(tmp->dim))->center[0]) +
			(from[1] - ((t_sphere*)(tmp->dim))->center[1]) * (from[1] -
			((t_sphere*)(tmp->dim))->center[1]) + (from[2] -
			((t_sphere*)(tmp->dim))->center[2]) * (from[2] -
			((t_sphere*)(tmp->dim))->center[2]) -
			((t_sphere*)(tmp->dim))->radius * ((t_sphere*)(tmp->dim))->radius))
			>= 0)
		d = a * vec_norm(to);
	return (d);
}

double	distance_to_plane(t_object *tmp, double *from, double *to, double *ref)
{
	if (scalar_product(((t_plane*)(tmp->dim))->n, to) == 0.0)
	{
		if (((t_plane*)(tmp->dim))->n[0] * (ref[0] - from[0]) + ((t_plane*)(tmp->dim))->n[1] * (ref[1] * from[1]) +
				((t_plane*)(tmp->dim))->n[2] * (ref[2] - from[2]) == 0.0)
			return (0.0);
		return (-1.0);
	}
	else
		return ((((t_plane*)(tmp->dim))->n[0] * (ref[0] - from[0]) + ((t_plane*)(tmp->dim))->n[1] *
					(ref[1] - from[1]) + ((t_plane*)(tmp->dim))->n[2] *
					(ref[2] - from[2])) / scalar_product(((t_plane*)(tmp->dim))->n, to));
}

double	distance_to_cone(t_object *tmp, double *from, double *to)
{
	vec_soustraction(from, ((t_cone*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(to) * second_level(cone_first_term(tmp, to),
		cone_second_term(tmp, to, tmp->tmp_vec),
		cone_third_term(tmp, tmp->tmp_vec)));
}

double	distance_to_cylindre(t_object *tmp, double *from, double *to)
{
	vec_soustraction(from, ((t_cylindre*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(to) * second_level(cylindre_first_term(tmp, to),
		cylindre_second_term(tmp, to), cylindre_third_term(tmp)));
}

double	distance_calc(t_object *tmp, t_param *param,double *from, double *to)
{
	if (tmp->type == 1 && param)
		return (distance_to_sphere(tmp, from, to));
	else if (tmp->type == 2)
		return (distance_to_plane(tmp, from, to, ((t_plane*)(tmp->dim))->ref));
	else if (tmp->type == 3)
		return (distance_to_cone(tmp, from, to));
	else if (tmp->type == 4)
		return (distance_to_cylindre(tmp, from, to));
	return (-1.0);
}
