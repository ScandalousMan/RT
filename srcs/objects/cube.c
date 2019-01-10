/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 22:18:12 by malexand          #+#    #+#             */
/*   Updated: 2019/01/10 22:18:48 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	distance_to_cube2(t_object *tmp, double *from, double *to, double res)
{
	double	tmp_res;

	tmp_res = -1.0f;
	if ((tmp_res = distance_to_face1(tmp, from, to, -0.5)) >= 0 &&
		(tmp_res < res || res < 0.0f))
	{
		res = tmp_res;
		vec_multiply(-1.0f, tmp->ref.i, ((t_cube*)(tmp->dim))->n);
	}
	if ((tmp_res = distance_to_face2(tmp, from, to, -0.5)) >= 0 &&
		(tmp_res < res || res < 0.0f))
	{
		res = tmp_res;
		vec_multiply(-1.0f, tmp->ref.j, ((t_cube*)(tmp->dim))->n);
	}
	if ((tmp_res = distance_to_face3(tmp, from, to, -0.5)) >= 0 &&
		(tmp_res < res || res < 0.0f))
	{
		res = tmp_res;
		vec_multiply(-1.0f, tmp->ref.k, ((t_cube*)(tmp->dim))->n);
	}
	return (res);
}

double	distance_to_cube(t_object *tmp, double *from, double *to)
{
	double	res[2];

	res[1] = -1.0f;
	if ((res[0] = distance_to_face1(tmp, from, to, 0.5)) >= 0.0f)
		vec_copy(tmp->ref.i, ((t_cube*)(tmp->dim))->n);
	if ((res[1] = distance_to_face2(tmp, from, to, 0.5)) >= 0 &&
		(res[1] < res[0] || res[0] < 0.0f))
	{
		res[0] = res[1];
		vec_copy(tmp->ref.j, ((t_cube*)(tmp->dim))->n);
	}
	if ((res[1] = distance_to_face3(tmp, from, to, 0.5)) >= 0 &&
		(res[1] < res[0] || res[0] < 0.0f))
	{
		res[0] = res[1];
		vec_copy(tmp->ref.k, ((t_cube*)(tmp->dim))->n);
	}
	return (distance_to_cube2(tmp, from, to, res[0]));
}

void	update_normal_cube(t_object *tmp, t_path *path)
{
	vec_copy(((t_cube*)(tmp->dim))->n, path->valid_n);
}

int		is_inside_cube(double *pt, t_object *tmp)
{
	vec_soustraction(pt, ((t_cube*)(tmp->dim))->center, tmp->tmp_vec);
	if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.i)) >
		((t_cube*)(tmp->dim))->h / 2.0f ||
		ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.j)) >
		((t_cube*)(tmp->dim))->h / 2.0f ||
		ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.k)) >
		((t_cube*)(tmp->dim))->h / 2.0f)
		return (0);
	return (1);
}

double	*cube_position(double *pt, t_object *obj)
{
	double s[3];

	vec_soustraction(pt, ((t_cube*)(obj->dim))->center, obj->tmp_vec);
	s[0] = scalar_product(obj->tmp_vec, obj->ref.i);
	s[1] = scalar_product(obj->tmp_vec, obj->ref.j);
	s[2] = scalar_product(obj->tmp_vec, obj->ref.k);
	if (ft_absdbl(s[0]) > ft_absdbl(s[1]) && ft_absdbl(s[0]) > ft_absdbl(s[2]))
	{
		obj->uv_map[0] = (s[1] + ((t_cube*)(obj->dim))->h / 2.0f);
		obj->uv_map[1] = (s[2] + ((t_cube*)(obj->dim))->h / 2.0f);
	}
	else if (ft_absdbl(s[1]) > ft_absdbl(s[0]) &&
		ft_absdbl(s[1]) > ft_absdbl(s[2]))
	{
		obj->uv_map[0] = (s[2] + ((t_cube*)(obj->dim))->h / 2.0f);
		obj->uv_map[1] = (s[0] + ((t_cube*)(obj->dim))->h / 2.0f);
	}
	else
	{
		obj->uv_map[0] = (s[0] + ((t_cube*)(obj->dim))->h / 2.0f);
		obj->uv_map[1] = (s[1] + ((t_cube*)(obj->dim))->h / 2.0f);
	}
	obj->uv_map[0] = obj->uv_map[0] / ((t_cube*)(obj->dim))->h;
	obj->uv_map[1] = obj->uv_map[1] / ((t_cube*)(obj->dim))->h;
	return (obj->uv_map);
}
