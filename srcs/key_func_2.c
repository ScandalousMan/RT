/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacrozet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 18:10:02 by vacrozet          #+#    #+#             */
/*   Updated: 2018/09/09 18:10:04 by vacrozet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_objects(t_param *param)
{
	t_object	*tmp;
	t_limit		*l_tmp;

	while (param && param->objects)
	{
		tmp = param->objects->next;
		if (param->objects->type == 1)
			free((t_sphere*)(param->objects->dim));
		else if (param->objects->type == 2)
			free((t_plane*)(param->objects->dim));
		else if (param->objects->type == 3)
			free((t_cone*)(param->objects->dim));
		else if (param->objects->type == 4)
			free((t_cylindre*)(param->objects->dim));
		else if (param->objects->type == 5)
			free((t_quadric*)(param->objects->dim));
		while (param->objects->limits)
		{
			l_tmp = param->objects->limits->next;
			free(param->objects->limits);
			param->objects->limits = l_tmp;
		}
		free(param->objects);
		param->objects = tmp;
	}
}

void	free_lights(t_light *lights)
{
	t_light		*tmp;

	while (lights)
	{
		tmp = lights->next;
		free(lights);
		lights = tmp;
	}
	free(lights);
}
