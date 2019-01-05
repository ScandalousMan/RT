/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2018/10/31 21:49:47 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

void	limits_move(double *o, t_object *obj, t_param *param)
{
	t_limit	*tmp;

	tmp = obj->limits;
	while (tmp)
	{
		if (tmp->type == RT_C_RELATIVE)
		{
			matrice_product(param->rot, tmp->plane.n, tmp->plane.n);
			pt_translated(o, tmp->plane.ref, tmp->plane.ref);
		}
		tmp = tmp->next;
	}
}

void	ref_move(t_object *obj, t_param *param)
{
	rotation_matrice(obj->rotation[0], obj->rotation[1], obj->rotation[2],
		param);
	matrice_product(param->rot, obj->ref.i, obj->ref.i);
	matrice_product(param->rot, obj->ref.j, obj->ref.j);
	matrice_product(param->rot, obj->ref.k, obj->ref.k);
}
