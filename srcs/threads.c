/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:05:21 by malexand          #+#    #+#             */
/*   Updated: 2018/08/29 14:24:53 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			perlin_noise_copy(t_param *param1, t_param *param2)
{
	param2->i[0] = 0;
	while (param2->i[0] < NOISE_SIZE)
	{
		param2->i[1] = 0;
		while (param2->i[1] < NOISE_SIZE)
		{
			param2->perlin_noise[param2->i[0]][param2->i[1]] = param1->perlin_noise[param2->i[0]][param2->i[1]];
			param2->i[1]++;
		}
		param2->i[0]++;
	}
}

t_param		*param_cpy(t_param *param, int count)
{
	t_param		*param_cpy;

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
	ft_memcpy(&(param_cpy->eye), &(param->eye), VEC_SIZE * sizeof(double));
	ft_memcpy(&(param_cpy->look), &(param->look), VEC_SIZE * sizeof(double));
	ft_memcpy(&(param_cpy->align), &(param->align), VEC_SIZE * sizeof(double));
	ft_memcpy(&(param_cpy->third), &(param->third), VEC_SIZE * sizeof(double));
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

static int	calc(void *ptr)
{
	t_param		*param;

	param = (t_param*)ptr;
	rt_tracer(param);
	return (0);
}

void		launch_threads(t_param *param)
{
	int			threadReturnValue;
	int			count;
	t_param		*params[NB_THREAD];

	ft_putstr("==> Launch thread\n");
	count = 0;
	while (count < NB_THREAD)
	{
		mprintf(1, "Create param_cpy %d\n", count);
		params[count] = param_cpy(param, count);
		++count;
	}
	clock_t start = clock();
	count = 0;
	while (count < NB_THREAD)
	{
		mprintf(1, "Create thread %d\n", count);
		if (!(param->thread[count] = SDL_CreateThread(calc, "", (void*)params[count])))
			error(0, 0, "Create new thread failed!");
		count++;
	}
	param->end = clock();// Clock
	printf("Create threads takes %.5lf secondes...\n", (double)(param->end - start) / CLOCKS_PER_SEC);
	start = clock();// Clock
	count = 0;
	while (count < NB_THREAD)
	{
		mprintf(1, "Wait thread %d\n", count);
		SDL_WaitThread(param->thread[count], &threadReturnValue);
		if (threadReturnValue != 0)
			error(0, 0, "Thread wrong return value");
		count++;
	}

	count = 0;
	while (count < NB_THREAD) {
		mprintf(1, "Free param_cpy %d\n", count);
		free_path(params[count]->path);
		free_lights(params[count]->lights);
		free_objects(params[count]);
		free(params[count]);
		++count;
	}
	param->end = clock();// Clock
	printf("Calculs %.5lf secondes...\n", (double)(param->end - start) / CLOCKS_PER_SEC);
}
