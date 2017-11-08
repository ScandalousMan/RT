/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <aguemy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:21:40 by aguemy            #+#    #+#             */
/*   Updated: 2017/11/06 15:07:51 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	*pt_translated(double *pt, double *vec, double *container)
{
	container[0] = pt[0] + vec[0];
	container[1] = pt[1] + vec[1];
	container[2] = pt[2] + vec[2];
	return (container);
}

void	vec_copy(double *src, double *des)
{
//	if (src && des)
//	{
		des[0] = src[0];
		des[1] = src[1];
		des[2] = src[2];
//	}
}

double	*coord_copy(double *des, double x, double y, double z)
{
//	if (des)
//	{
		des[0] = x;
		des[1] = y;
		des[2] = z;
		return (des);
//	}
//	return (NULL);
}

double	scalar_product(double *x, double *y)
{
//	if (x && y)
		return (x[0] * y[0] + x[1] * y[1] + x[2] * y[2]);
//	return (0.0);
}

double	*vector_product(double *x, double *y, double *container)
{
//	if (x && y)
//	{
		container[0] = x[1] * y[2] - x[2] * y[1];
		container[1] = x[2] * y[0] - x[0] * y[2];
		container[2] = x[0] * y[1] - x[1] * y[0];
//	}
	return (container);
}
