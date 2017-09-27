/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eye_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <aguemy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 10:57:30 by aguemy            #+#    #+#             */
/*   Updated: 2017/09/19 11:04:43 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	**rotation_matrice(double alpha, double beta, double gamma,
		t_param *param)
{
	if (param->rot && param->rot[0] && param->rot[1] && param->rot[2])
	{
		alpha = alpha * M_PI / 180.0;
		beta = beta * M_PI / 180.0;
		gamma = gamma * M_PI / 180.0;
		param->rot[0][0] = cos(beta) * cos(gamma);
		param->rot[0][1] = -1.0 * cos(beta) * sin(gamma);
		param->rot[0][2] = sin(beta);
		param->rot[1][0] = sin(alpha) * sin(beta) * cos(gamma) +
			cos(alpha) * sin(gamma);
		param->rot[1][1] = cos(alpha) * cos(gamma) -
			sin(alpha) * sin(beta) * sin(gamma);
		param->rot[1][2] = -1.0 * sin(alpha) * cos(beta);
		param->rot[2][0] = sin(alpha) * sin(gamma) -
			cos(alpha) * sin(beta) * cos(gamma);
		param->rot[2][1] = cos(alpha) * sin(beta) * sin(gamma) +
			sin(alpha) * cos(gamma);
		param->rot[2][2] = cos(alpha) * cos(beta);
		return (param->rot);
	}
	else
		return (NULL);
}

void	eye_rotation(double alpha, double beta, double gamma, t_param *param)
{
	rotation_matrice(alpha, beta, gamma, param);
	ft_putstr("\n1st line - rot\n");
	ft_putvec(param->rot[0]);
	ft_putstr("\n2nd line - rot\n");
	ft_putvec(param->rot[1]);
	ft_putstr("\n3rd line - rot\n");
	ft_putvec(param->rot[2]);
	ft_putstr("\nlook1:\n");
	ft_putvec(param->look);
	matrice_product(param->rot, param->look, param->look);
	ft_putstr("\nlook2:\n");
	ft_putvec(param->look);
	ft_putstr("\nalign:\n");
	ft_putvec(param->align);
	ft_putchar('\n');
	matrice_product(param->rot, param->align, param->align);
	vec_to_unit_norm(vector_product(param->align, param->look, param->third));
}
