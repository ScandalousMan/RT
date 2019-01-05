/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:46:08 by itsalex           #+#    #+#             */
/*   Updated: 2018/08/29 14:46:09 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

t_light		*light_copy(t_light *src)
{
	t_light	*copy;

	if (!src)
		return (NULL);
	if (!(copy = duplicate(src, sizeof(t_light))))
		return (NULL);
	if (src->next)
	{
		if (!(copy->next = light_copy(src->next)))
			return (NULL);
	}
	return (copy);
}

t_object	*light_masked(t_param *param, double *from, double *to,
	t_path *path)
{
	param->intersect_object = NULL;
	param->is_for_light = 1;
	param->tmp_light->tmp_col = param->tmp_light->col;
	first_obj_hit(param, from, to, path);
	return (param->intersect_object);
}
