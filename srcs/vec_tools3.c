/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <aguemy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:07:29 by aguemy            #+#    #+#             */
/*   Updated: 2017/09/19 11:08:38 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		a = matrice[0][0] * col[0] + matrice[0][1] * col[1] +
			matrice[0][2] * col[2];
		b = matrice[1][0] * col[0] + matrice[1][1] * col[1] +
			matrice[1][2] * col[2];
		c = matrice[2][0] * col[0] + matrice[2][1] * col[1] +
			matrice[2][2] * col[2];
		dest[0] = a;
		dest[1] = b;
		dest[2] = c;
	}
}

double	*vec_dup(double *vec)
{
	double	*res;

	if (!(res = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	vec_copy(vec, res);
	return res;
}
