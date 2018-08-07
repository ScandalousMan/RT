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

#include "rt_objects.h"

double	distance_calc(t_object *tmp, t_param *param,double *from, double *to)
{
	if (tmp->type == RTSPHERE)
		return (distance_to_sphere(tmp, from, to));
	else if (tmp->type == RTPLAN)
		return (distance_to_plane(tmp, from, to));
	else if (tmp->type == RTCONE)
		return (distance_to_cone(tmp, from, to));
	else if (tmp->type == RTCYLINDER)
		return (distance_to_cylindre(tmp, from, to));
	else if (tmp->type == RTQUADRIC)
		return (distance_to_quadric(tmp, from, to));
	else if (tmp->type == 6)
		return (distance_to_tore(tmp, from, to));
	return (-1.0);
}
