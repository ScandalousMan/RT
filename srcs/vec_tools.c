/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:21:40 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/31 10:35:55 by aguemy           ###   ########.fr       */
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

double	*pt_translated(double *pt, double *vec, double *container)
{
	container[0] = pt[0] + vec[0];
	container[1] = pt[1] + vec[1];
	container[2] = pt[2] + vec[2];
	return (container);
}

void	vec_copy(double *src, double *des)
{
	if (src && des)
	{
		des[0] = src[0];
		des[1] = src[1];
		des[2] = src[2];
	}
}

double	*coord_copy(double *des, double x, double y, double z)
{
	if (des)
	{
		des[0] = x;
		des[1] = y;
		des[2] = z;
		return (des);
	}
	return (NULL);
}

double	scalar_product(double *x, double *y)
{
	if (x && y)
		return (x[0] * y[0] + x[1] * y[1] + x[2] * y[2]);
	return (0.0);
}

double	*vector_product(double *x, double *y, double *container)
{
	if (x && y)
	{
		container[0] = x[1] * y[2] - x[2] * y[1];
		container[1] = x[2] * y[0] - x[0] * y[2];
		container[2] = x[0] * y[1] - x[1] * y[0];
	}
	return (container);
}

double	second_level(double a, double b, double c)
{
	double	det;

	if (a < 0.0)
	{
		a = -a;
		b = -b;
		c = -c;
	}
	det = b * b - 4.0 * a * c;
	if (a == 0.0 || det < 0.0 || (b > sqrt(det)))
		return (-1.0);
	det = sqrt(det);
	if ((-b - det) <= 0.0)
		return ((-b + det) / 2.0 / a);
	else
		return ((-b - det) / 2.0 / a);
}

void	matrice_product(double **matrice, double *col, double *dest)
{
	double	a;
	double	b;
	double	c;

	if (matrice && col && dest)
	{
		a = matrice[0][0] * col[0] + matrice[0][1] * col[1] + matrice[0][2] * col[2];
		b = matrice[1][0] * col[0] + matrice[1][1] * col[1] + matrice[1][2] * col[2];
		c = matrice[2][0] * col[0] + matrice[2][1] * col[1] + matrice[2][2] * col[2];
		dest[0] = a;
		dest[1] = b;
		dest[2] = c;
	}
}