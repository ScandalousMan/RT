/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:39 by aguemy            #+#    #+#             */
/*   Updated: 2018/08/28 17:04:49 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

void	free_parsed(t_object *obj)
{
	if (obj->type == RTSPHERE)
		free((t_sphere*)(obj->parsed));
	else if (obj->type == RTPLAN)
		free((t_plane*)(obj->parsed));
	else if (obj->type == RTCONE)
		free((t_cone*)(obj->parsed));
	else if (obj->type == RTCYLINDER)
		free((t_cylindre*)(obj->parsed));
	else if (obj->type == RTQUADRIC)
		free((t_quadric*)(obj->parsed));
	else if (obj->type == RTCUBE)
		free((t_cube*)(obj->parsed));
}

void	free_limits(t_object *obj, char final)
{
	t_limit		*l_tmp;

	while (obj->limits)
	{
		l_tmp = obj->limits->next;
		free(obj->limits);
		obj->limits = l_tmp;
	}
	if (final)
	{
		while (obj->limits_parsed)
		{
			l_tmp = obj->limits_parsed->next;
			free(obj->limits_parsed);
			obj->limits_parsed = l_tmp;
		}
	}
}

void	free_objects(t_param *param, char final)
{
	t_object	*tmp;

	while (param && param->objects)
	{
		tmp = param->objects->next;
		if (param->objects->type == RTSPHERE)
			free((t_sphere*)(param->objects->dim));
		else if (param->objects->type == RTPLAN)
			free((t_plane*)(param->objects->dim));
		else if (param->objects->type == RTCONE)
			free((t_cone*)(param->objects->dim));
		else if (param->objects->type == RTCYLINDER)
			free((t_cylindre*)(param->objects->dim));
		else if (param->objects->type == RTQUADRIC)
			free((t_quadric*)(param->objects->dim));
		else if (param->objects->type == RTCUBE)
			free((t_cube*)(param->objects->dim));
		if (final)
			free_parsed(param->objects);
		free_limits(param->objects, final);
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

void	free_path(t_path *path)
{
	if (path)
	{
		free_path(path->reflected);
		free_path(path->transmitted);
		free(path);
	}
}
