/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <aguemy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:06:30 by aguemy            #+#    #+#             */
/*   Updated: 2017/11/06 14:52:07 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	vec_norm(double *v)
{
	if (v)
		return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
	return (0.0);
}

double	*vec_to_unit_norm(double *v)
{
	if (vec_norm(v) == 0.0)
		return (v);
	return (vec_multiply(1.0 / vec_norm(v), v, v));
}

//TODO delete? replace pt_dist by pt_dist_root: pt_dist_root = pt_dist * pt_dist
/*double	pt_dist(double *x, double *y)
{
	double	tmp[VEC_SIZE];

	tmp[0] = x[0] - y[0];
	tmp[1] = x[1] - y[1];
	tmp[2] = x[2] - y[2];
	return (sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]));
}*/

double	pt_dist_root(double *x, double *y)
{
	double	tmp[VEC_SIZE];

	tmp[0] = x[0] - y[0];
	tmp[1] = x[1] - y[1];
	tmp[2] = x[2] - y[2];
	return (tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
}

double	*vec_multiply(double a, double *vec, double *container)
{
	container[0] = a * vec[0];
	container[1] = a * vec[1];
	container[2] = a * vec[2];
	return (container);
}

double	*vec_soustraction(double *x, double *y, double *container)
{
	if (x && y && container)
	{
		container[0] = x[0] - y[0];
		container[1] = x[1] - y[1];
		container[2] = x[2] - y[2];
		return (container);
	}
	return (NULL);
}
