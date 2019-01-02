/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:39 by aguemy            #+#    #+#             */
/*   Updated: 2018/08/28 17:04:49 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

void	rotation_axis_matrice(double angle, double *axis, t_param *param)
{
	double	c;
	double	s;

	c = cos(angle * M_PI / 180.0);
	s = sin(angle * M_PI / 180.0);
	param->rot[0][0] = axis[0] * axis[0] * (1.0 - c) + c;
	param->rot[0][1] = axis[0] * axis[1] * (1.0 - c) - axis[2] * s;
	param->rot[0][2] = axis[0] * axis[2] * (1.0 - c) + axis[1] * s;
	param->rot[1][0] = axis[0] * axis[1] * (1.0 - c) + axis[2] * s;
	param->rot[1][1] = axis[1] * axis[1] * (1.0 - c) + c;
	param->rot[1][2] = axis[1] * axis[2] * (1.0 - c) - axis[0] * s;
	param->rot[2][0] = axis[0] * axis[2] * (1.0 - c) - axis[1] * s;
	param->rot[2][1] = axis[1] * axis[2] * (1.0 - c) + axis[0] * s;
	param->rot[2][2] = axis[2] * axis[2] * (1.0 - c) + c;
}

void	rotation_matrice(double a, double b, double c, t_param *param)
{
	a = a * M_PI / 180.0;
	b = b * M_PI / 180.0;
	c = c * M_PI / 180.0;
	param->rot[0][0] = cos(b) * cos(c);
	param->rot[0][1] = -1.0 * cos(b) * sin(c);
	param->rot[0][2] = sin(b);
	param->rot[1][0] = sin(a) * sin(b) * cos(c) + cos(a) * sin(c);
	param->rot[1][1] = cos(a) * cos(c) - sin(a) * sin(b) * sin(c);
	param->rot[1][2] = -1.0 * sin(a) * cos(b);
	param->rot[2][0] = sin(a) * sin(c) - cos(a) * sin(b) * cos(c);
	param->rot[2][1] = cos(a) * sin(b) * sin(c) + sin(a) * cos(c);
	param->rot[2][2] = cos(a) * cos(b);
}

void	eye_rotation(double alpha, double beta, double gamma, t_param *param)
{
	if (alpha)
		rotation_axis_matrice(alpha, param->third, param);
	else if (beta)
		rotation_axis_matrice(beta, param->align, param);
	else
		rotation_axis_matrice(gamma, param->look, param);
	matrice_product(param->rot, param->look, param->look);
	matrice_product(param->rot, param->align, param->align);
	vec_to_unit_norm(vector_product(param->align, param->look, param->third));
}
