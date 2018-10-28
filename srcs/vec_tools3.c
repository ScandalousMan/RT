/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <aguemy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:07:29 by aguemy            #+#    #+#             */
/*   Updated: 2017/10/25 19:55:08 by jbouille         ###   ########.fr       */
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

void	matrice_product(double mat[VEC_SIZE][VEC_SIZE], double *col, double *dest)
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
		return NULL;
	vec_copy(vec, res);
	return res;
}

void 		object_rotation(double mat[VEC_SIZE][VEC_SIZE], t_object *object)
{
	t_limit *tmp;
	//1: appliquer la rotation au référentiel de l'objet
	matrice_product(mat, object->ref.i, object->ref.i);
	matrice_product(mat, object->ref.j, object->ref.j);
	matrice_product(mat, object->ref.k, object->ref.k);
	//2: appliquer la rotation aux limites de l'objet
	tmp = object->limits;
	while (tmp)
	{
		// ajouter typologie de limite (soit absolue, soit relative)
		matrice_product(mat, tmp->plane.n, tmp->plane.n);
		matrice_product(mat, tmp->plane.ref, tmp->plane.ref);	
		tmp = tmp->next;
	}
	//3: appliquer la rotation aux spécificités de l'objet (dans les objets)
	if (object->type != 1)
		printf("not a sphere\n");
}

double	mat_det(t_reference ref)
{
	return (ref.i[0] * ref.j[1] * ref.k[2] +
		ref.i[1] * ref.j[2] * ref.k[0] +
		ref.i[2] * ref.j[0] * ref.k[1] -
		ref.i[2] * ref.j[1] * ref.k[0] -
		ref.i[0] * ref.j[2] * ref.k[1] -
		ref.i[1] * ref.j[0] * ref.k[2]);
}

void		ref_change_back(t_reference ref, double *src, double*dest)
{
	double	det;
	double	x[3];
	double	tmp[VEC_SIZE][VEC_SIZE];

	det = mat_det(ref);
	if (det)
	{
		tmp[0][0] = 1.0f / det * (ref.j[1] * ref.k[2] - ref.j[2] * ref.k[1]);
		tmp[0][1] = 1.0f / det * (ref.i[2] * ref.k[1] - ref.i[1] * ref.k[2]);
		tmp[0][2] = 1.0f / det * (ref.i[1] * ref.j[2] - ref.j[1] * ref.i[2]);
		tmp[1][0] = 1.0f / det * (ref.j[2] * ref.k[0] - ref.j[0] * ref.k[2]);
		tmp[1][1] = 1.0f / det * (ref.i[0] * ref.k[2] - ref.i[2] * ref.k[0]);
		tmp[1][2] = 1.0f / det * (ref.i[2] * ref.j[0] - ref.i[0] * ref.j[2]);
		tmp[2][0] = 1.0f / det * (ref.j[0] * ref.k[1] - ref.k[0] * ref.j[1]);
		tmp[2][1] = 1.0f / det * (ref.i[1] * ref.k[0] - ref.i[0] * ref.k[1]);
		tmp[2][2] = 1.0f / det * (ref.i[0] * ref.j[1] - ref.i[1] * ref.j[0]);
		x[0] = src[0] * tmp[0][0] + src[1] * tmp[0][1] + src[2] * tmp[0][2];
		x[1] = src[0] * tmp[1][0] + src[1] * tmp[1][1] + src[2] * tmp[1][2];
		x[2] = src[0] * tmp[2][0] + src[1] * tmp[2][1] + src[2] * tmp[2][2];
		dest[0] = x[0];
		dest[1] = x[1];
		dest[2] = x[2];
	}
}

void		ref_change(t_reference ref, double *src, double *dest)
{
	double	a;
	double	b;
	double	c;

	a = src[0] * ref.i[0] + src[1] * ref.i[1] + src[2] * ref.i[2];
	b = src[0] * ref.j[0] + src[1] * ref.j[1] + src[2] * ref.j[2];
	c = src[0] * ref.k[0] + src[1] * ref.k[1] + src[2] * ref.k[2];
	dest[0] = a;
	dest[1] = b;
	dest[2] = c;
}
