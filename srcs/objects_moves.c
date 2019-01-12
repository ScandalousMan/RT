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
	t_limit	*tmp[2];

	tmp[0] = obj->limits_parsed;
	tmp[1] = obj->limits;
	while (tmp[0] && tmp[1])
	{
		if (tmp[0]->type == RT_C_RELATIVE)
		{
			printf("ooooo\n");
			matrice_product(param->rot, tmp[0]->plane.n, tmp[1]->plane.n);
			pt_translated(o, tmp[0]->plane.ref, tmp[1]->plane.ref);
		}
		else
		{
			printf("ooooo\n");
			vec_copy(tmp[0]->plane.ref, tmp[1]->plane.ref);
			vec_copy(tmp[0]->plane.n, tmp[1]->plane.n);
		}
		tmp[0] = tmp[0]->next;
		tmp[1] = tmp[1]->next;
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
