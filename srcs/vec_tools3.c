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

void		sim_matrice_rotation(double *a, double * b, t_param *param)
{
	if (a && b)
	{
		param->rot[0][0] = 0.0;
		param->rot[0][1] = 1.0;
		param->rot[0][2] = 0.0;
		param->rot[1][0] = 0.0;
		param->rot[1][1] = 0.0;
		param->rot[1][2] = 1.0;
		param->rot[2][0] = 1.0;
		param->rot[2][1] = 0.0;
		param->rot[2][2] = 0.0;
	}
	// double	c;
	// double	v[VEC_SIZE];

	// vector_product(a, b, v);
	// c = scalar_product(a, b);
	// if (c == -1.0)
	// {
	// 	param->rot[0][0] = -1.0;
	// 	param->rot[0][1] = 0.0;
	// 	param->rot[0][2] = 0.0;
	// 	param->rot[1][0] = 0.0;
	// 	param->rot[1][1] = -1.0;
	// 	param->rot[1][2] = 0.0;
	// 	param->rot[2][0] = 0.0;
	// 	param->rot[2][1] = 0.0;
	// 	param->rot[2][2] = -1.0;
	// }
	// else
	// {
	// 	param->rot[0][0] = 1.0 - (v[1] * v[1] + v[2] * v[2]) / (1.0 + c);
	// 	param->rot[0][1] = -v[2] + v[0] * v[1] / (1.0 + c);
	// 	param->rot[0][2] = v[1] + v[0] * v[2] / (1.0 + c);
	// 	param->rot[1][0] = v[2] + v[0] * v[1] / (1.0 + c);
	// 	param->rot[1][1] = 1.0 - (v[0] * v[0] + v[2] * v[2]) / (1.0 + c);
	// 	param->rot[1][2] = -v[0] + v[1] * v[2] / (1.0 + c);
	// 	param->rot[2][0] = -v[1] + v[0] * v[2] / (1.0 + c);
	// 	param->rot[2][1] = v[0] + v[1] * v[2] / (1.0 + c);
	// 	param->rot[2][2] = 1.0 - (v[0] * v[0] + v[1] * v[1]) / (1.0 + c);
	// }
}
