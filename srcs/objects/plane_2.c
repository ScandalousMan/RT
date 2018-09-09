/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacrozet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:34:13 by vacrozet          #+#    #+#             */
/*   Updated: 2018/09/09 16:34:16 by vacrozet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

double	plane_distance(double *from, double *to, double *n, double *ref)
{
	if (scalar_product(n, to) == 0.0)
	{
		if (n[0] * (ref[0] - from[0]) + n[1] * (ref[1] * from[1]) +
				n[2] * (ref[2] - from[2]) == 0.0)
			return (0.0);
		return (-1.0);
	}
	else
		return ((n[0] * (ref[0] - from[0]) + n[1] * (ref[1] - from[1]) +
					n[2] * (ref[2] - from[2])) / scalar_product(n, to));
}

double	distance_to_plane(t_object *tmp, double *from, double *to)
{
	return (plane_distance(from, to, ((t_plane*)(tmp->dim))->n,
			((t_plane*)(tmp->dim))->ref));
}
