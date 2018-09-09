/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <aguemy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:07:29 by aguemy            #+#    #+#             */
/*   Updated: 2018/09/09 17:29:40 by vacrozet         ###   ########.fr       */
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

void	matrice_product(double mat[VEC_SIZE][VEC_SIZE], double *col,
			double *dest)
{
	double	a;
	double	b;
	double	c;

	a = mat[0][0] * col[0] + mat[0][1] * col[1] + mat[0][2] * col[2];
	b = mat[1][0] * col[0] + mat[1][1] * col[1] + mat[1][2] * col[2];
	c = mat[2][0] * col[0] + mat[2][1] * col[1] + mat[2][2] * col[2];
	dest[0] = a;
	dest[1] = b;
	dest[2] = c;
}

double	*vec_dup(double *vec)
{
	double	*res;

	if (!(res = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	vec_copy(vec, res);
	return (res);
}

void	object_rotation(double mat[VEC_SIZE][VEC_SIZE], t_object *object)
{
	t_limit *tmp;

	matrice_product(mat, object->ref.i, object->ref.i);
	matrice_product(mat, object->ref.j, object->ref.j);
	matrice_product(mat, object->ref.k, object->ref.k);
	tmp = object->limits;
	while (tmp)
	{
		matrice_product(mat, tmp->plane.n, tmp->plane.n);
		matrice_product(mat, tmp->plane.ref, tmp->plane.ref);
		tmp = tmp->next;
	}
	if (object->type != 1)
		printf("not a sphere\n");
}
