/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 22:31:21 by malexand          #+#    #+#             */
/*   Updated: 2019/01/10 22:32:01 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	distance_to_face1(t_object *tmp, double *from, double *to, double face)
{
	double	res;

	vec_multiply(face * ((t_cube*)(tmp->dim))->h, tmp->ref.i, tmp->tmp_vec);
	pt_translated(((t_cube*)(tmp->dim))->center, tmp->tmp_vec, tmp->tmp_vec);
	res = plane_distance(from, to, tmp->ref.i, tmp->tmp_vec);
	if (res >= 0)
	{
		vec_multiply(res, to, tmp->tmp_vec);
		pt_translated(from, tmp->tmp_vec, tmp->tmp_vec);
		vec_soustraction(tmp->tmp_vec, ((t_cube*)(tmp->dim))->center,
			tmp->tmp_vec);
		if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.j)) >
			((t_cube*)(tmp->dim))->h / 2.0f ||
			ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.k)) >
			((t_cube*)(tmp->dim))->h / 2.0f)
			res = -1.0f;
	}
	return (res);
}

double	distance_to_face2(t_object *tmp, double *from, double *to, double face)
{
	double	res;

	vec_multiply(face * ((t_cube*)(tmp->dim))->h, tmp->ref.j, tmp->tmp_vec);
	pt_translated(((t_cube*)(tmp->dim))->center, tmp->tmp_vec, tmp->tmp_vec);
	res = plane_distance(from, to, tmp->ref.j, tmp->tmp_vec);
	if (res >= 0)
	{
		vec_multiply(res, to, tmp->tmp_vec);
		pt_translated(from, tmp->tmp_vec, tmp->tmp_vec);
		vec_soustraction(tmp->tmp_vec, ((t_cube*)(tmp->dim))->center,
			tmp->tmp_vec);
		if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.i)) >
			((t_cube*)(tmp->dim))->h / 2.0f ||
			ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.k)) >
			((t_cube*)(tmp->dim))->h / 2.0f)
			res = -1.0f;
	}
	return (res);
}

double	distance_to_face3(t_object *tmp, double *from, double *to, double face)
{
	double	res;

	vec_multiply(face * ((t_cube*)(tmp->dim))->h, tmp->ref.k, tmp->tmp_vec);
	pt_translated(((t_cube*)(tmp->dim))->center, tmp->tmp_vec, tmp->tmp_vec);
	res = plane_distance(from, to, tmp->ref.k, tmp->tmp_vec);
	if (res >= 0)
	{
		vec_multiply(res, to, tmp->tmp_vec);
		pt_translated(from, tmp->tmp_vec, tmp->tmp_vec);
		vec_soustraction(tmp->tmp_vec, ((t_cube*)(tmp->dim))->center,
			tmp->tmp_vec);
		if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.j)) >
			((t_cube*)(tmp->dim))->h / 2.0f ||
			ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.i)) >
			((t_cube*)(tmp->dim))->h / 2.0f)
			res = -1.0f;
	}
	return (res);
}

void	update_cube(t_object *obj, t_param *param)
{
	default_ref_updater(obj);
	((t_cube*)(obj->dim))->h = ((t_cube*)(obj->parsed))->h;
	pt_translated(((t_cube*)(obj->parsed))->center, obj->translation,
		((t_cube*)(obj->dim))->center);
	ref_move(obj, param);
	limits_move(((t_cube*)(obj->dim))->center, obj, param);
}

void	display_cube(t_object *objs)
{
	ft_putstr("** new cube **\n");
	ft_putstr("h: ");
	ft_putnbr(((t_cube*)(objs->parsed))->h);
	ft_putchar('\n');
	ft_putstr("centre: ");
	ft_putvec(((t_cube*)(objs->parsed))->center);
	ft_putchar('\n');
}
