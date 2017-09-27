/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <aguemy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:06:30 by aguemy            #+#    #+#             */
/*   Updated: 2017/09/19 11:07:15 by aguemy           ###   ########.fr       */
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

double	pt_dist(double *x, double *y)
{
	if (x && y)
	{
		return (sqrt((x[0] - y[0]) * (x[0] - y[0]) + (x[1] - y[1]) *
						(x[1] - y[1]) + (x[2] - y[2]) * (x[2] - y[2])));
	}
	return (0.0);
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
