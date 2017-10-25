/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:57:42 by aguemy            #+#    #+#             */
/*   Updated: 2017/10/25 17:22:13 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_path			*path_create(int index)
{
	t_path		*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	if (!(path->from = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(path->v = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(path->x = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(path->n = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(path->l = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(path->r = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(path->t = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	path->current_object = NULL;
	path->reflected = index < MAX_RECURSION ? path_create(index + 1) : NULL;
	path->transmitted = index < MAX_RECURSION ? path_create(index + 1) : NULL;
	return path;
}

t_param			*create_rotation_matrice(t_param *param)
{
	if (!(param->rot = (double**)malloc(sizeof(double*) * 3)))
		return NULL;
	if (!(param->rot[0] = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	if (!(param->rot[1] = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	if (!(param->rot[2] = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	return param;
}

t_param			*struct_create(void)
{
	t_param		*param;

	if (!(param = (t_param*)malloc(sizeof(t_param))))
		return (NULL);
	param->path = path_create(0);
	if (!(param->tmp_vec = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(param->i = (int*)malloc(sizeof(int) * 2)))
		return (NULL);
	if (!(param->thread = (SDL_Thread**)malloc(sizeof(SDL_Thread*) * NB_THREAD)))
		return (NULL);
	param->brightness = 1;
	param->epsilon = EPSILON;
	param->objects = NULL;
	param->lights = NULL;
	param->tmp_object = NULL;
	param->tmp_light = NULL;
	param->intersect_object = NULL;
	param->f = FOCAL_VALUE;
	param->ia = 1.0;
	param->num_lights = 0;
	param->refresh = 1;
	param->current_thread = 0;
	return create_rotation_matrice(param);
}

t_light			*add_light(t_light **lights, double *src, double i, int col)
{
	t_light		*prev;
	t_light		*new;
	int			num;

	if (!src)
		return (NULL);
	new = *lights;
	prev = NULL;
	num = 0;
	while (new)
	{
		num++;
		prev = new;
		new = new->next;
	}
	if (!(new = (t_light*)malloc(sizeof(t_light))))
		return (NULL);
	new->src = src;
	new->i = i;
	new->col = col;
	new->num = num;
	new->next = NULL;
	if (*lights && prev)
		prev->next = new;
	else
		*lights = new;
	return (new);
}

t_object		*object_constructor(t_param *param)
{
	int			num;
	t_object	*prev;

	param->tmp_object = param->objects;
	num = 1;
	prev = NULL;
	while (param->tmp_object)
	{
		num++;
		prev = param->tmp_object;
		param->tmp_object = param->tmp_object->next;
	}
	if (!(param->tmp_object = (t_object*)malloc(sizeof(t_object))))
		return (NULL);
	param->tmp_object->num = num;
	param->tmp_object->transparency = 0.2;
	param->tmp_object->reflection = 0.2;
	param->tmp_object->next = NULL;
	if (param->objects && prev)
		prev->next = param->tmp_object;
	else
		param->objects = param->tmp_object;
	return (param->tmp_object);
}
