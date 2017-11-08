/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:05:21 by malexand          #+#    #+#             */
/*   Updated: 2017/11/08 14:31:12 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_param		*param_cpy(t_param *param, int count)
{
	t_param		*param_cpy;

	
	if (!(param_cpy = struct_create()))
			error(0, 0, "Init param for multi thread failed!");
	param_cpy->graph = param->graph;
	param_cpy->current_thread = count;
	ft_memcpy(&(param_cpy->eye), &(param->eye), VEC_SIZE * sizeof(double));
	ft_memcpy(&(param_cpy->look), &(param->look), VEC_SIZE * sizeof(double));
	ft_memcpy(&(param_cpy->align), &(param->align), VEC_SIZE * sizeof(double));
	ft_memcpy(&(param_cpy->third), &(param->third), VEC_SIZE * sizeof(double));
//	param_cpy->eye = vec_dup(param->eye);
//	param_cpy->look = vec_dup(param->look);
//	param_cpy->align = vec_dup(param->align);
//	param_cpy->third = vec_dup(param->third);
	param_cpy->objects = object_copy(param->objects);
	param_cpy->lights = light_copy(param->lights);
	param_cpy->state = param->state;

	return (param_cpy);
}

static int	calc(void *ptr)
{
	t_param		*param;

	param = (t_param*)ptr;
	rt_tracer(param);
  return (0);
}

void		lauch_threads(t_param *param)
{
	int			count;
	int			threadReturnValue;
	char		*name;
	t_param		**params;

	count = 0;
	name = ft_strdup("Thread0");
	if (!(params = (t_param**)malloc(sizeof(t_param*) * NB_THREAD)))
		error(0, 0, "Alloc all thread not work");
	while (count < NB_THREAD)
	{
		params[count] = param_cpy(param, count);
		++count;
	}
	clock_t start = clock();//TODO delete
	count = 0;
	while (count < NB_THREAD)
	{
		name[6] = 48 + count;
	//	params[count] = param_cpy(param, count);
		if (!(param->thread[count] = SDL_CreateThread(calc, name, (void*)params[count])))
			error(0, 0, "Create new thread failed!");
		count++;
	}
	param->end = clock();//TODO delete
	printf("Create threads %.5lf secondes...\n", (double)(param->end - start) / CLOCKS_PER_SEC);
	start = clock();//TODO delete
	count = 0;
	while (count < NB_THREAD)
	{
		SDL_WaitThread(param->thread[count], &threadReturnValue);
		if (threadReturnValue != 0)
			error(0, 0, "Thread wrong return value");
		count++;
	}
	ft_strdel(&name);
	param->end = clock();//TODO delete
	printf("Calculs %.5lf secondes...\n", (double)(param->end - start) / CLOCKS_PER_SEC);
}
