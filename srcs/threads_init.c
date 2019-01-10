/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:05:21 by malexand          #+#    #+#             */
/*   Updated: 2019/01/10 22:28:59 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_param	*param_cpy2(t_param *param, int count, t_param *param_cpy)
{
	param_cpy->macro.anti_aliasing = param->macro.anti_aliasing;
	param_cpy->macro.recursion = param->macro.recursion;
	param_cpy->macro.cartoon_factor = param->macro.cartoon_factor;
	param_cpy->macro.blur_radius = param->macro.blur_radius;
	param_cpy->macro.specular_exp = param->macro.specular_exp;
	param_cpy->macro.rotation_angle = param->macro.rotation_angle;
	param_cpy->macro.k_ambience = param->macro.k_ambience;
	param_cpy->macro.filter = param->macro.filter;
	param_cpy->to_pix = param->to_pix;
	param_cpy->last_mv = param->last_mv;
	param_cpy->graph = param->graph;
	param_cpy->current_thread = count;
	ft_memcpy(&(param_cpy->eye), &(param->eye), 3 * sizeof(double));
	ft_memcpy(&(param_cpy->look), &(param->look), 3 * sizeof(double));
	ft_memcpy(&(param_cpy->align), &(param->align), 3 * sizeof(double));
	ft_memcpy(&(param_cpy->third), &(param->third), 3 * sizeof(double));
	param_cpy->objects = object_copy(param->objects);
	param_cpy->lights = light_copy(param->lights);
	param_cpy->num_objects = param->num_objects;
	param_cpy->pxl_infos = param->pxl_infos;
	if (!(param_cpy->path = path_create(param_cpy, 0)))
		return (NULL);
	param_cpy->path->inside_obj = param->path->inside_obj;
	perlin_noise_copy(param, param_cpy);
	return (param_cpy);
}

t_param			*param_cpy(t_param *param, int count)
{
	t_param *param_cpy;

	if (!(param_cpy = (t_param *)malloc(sizeof(t_param))))
		return (NULL);
	param_cpy->brightness = 1;
	param_cpy->quit = FALSE;
	param_cpy->epsilon = EPSILON;
	param_cpy->customs = NULL;
	param_cpy->objects = NULL;
	param_cpy->lights = NULL;
	param_cpy->tmp_light = NULL;
	param_cpy->intersect_object = NULL;
	param_cpy->f = FOCAL_VALUE;
	param_cpy->ia = 1.0;
	param_cpy->num_lights = 0;
	param_cpy->num_objects = 0;
	param_cpy->up_img.process = param->up_img.process;
	param_cpy->up_img.post_process = param->up_img.post_process;
	param_cpy->current_thread = 0;
	param_cpy->texture = param->texture;
	if (!(param_cpy2(param, count, param_cpy)))
		return (NULL);
	return (param_cpy);
}

void			init_params(t_param *param, t_param *params[NB_THREAD])
{
	int count;

	count = 0;
	while (count < NB_THREAD)
	{
		mprintf(1, "Create param_cpy %d\n", count);
		if (!(params[count] = param_cpy(param, count)))
			error(1, 0, "failed to copy param in thread\n");
		++count;
	}
}
