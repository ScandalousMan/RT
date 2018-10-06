/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 16:56:14 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/31 11:57:16 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	distance_calc(t_object *tmp, t_param *param, double *from, double *to)
{
	if (tmp->type == 1 && param)
		return (distance_to_sphere(tmp, from, to));
	else if (tmp->type == 2)
		return (distance_to_plane(tmp, from, to));
	else if (tmp->type == 3)
		return (distance_to_cone(tmp, from, to));
	else if (tmp->type == 4)
		return (distance_to_cylindre(tmp, from, to));
	else if (tmp->type == 5)
		return (distance_to_quadric(tmp, from, to));
	return (-1.0);
}
