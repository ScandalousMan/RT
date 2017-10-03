/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:05:21 by malexand          #+#    #+#             */
/*   Updated: 2017/09/28 15:13:12 by malexand         ###   ########.fr       */
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
	return (param_cpy);
}

static int	calc(void *ptr)
{
	t_param		*param;

	param = (t_param*)ptr;
	rt_parser(param);
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
		name[6] = 48 + count;
		params[count] = param_cpy(param, count);
		if (!(param->thread[count] = SDL_CreateThread(calc, name, (void*)params[count])))
			error(0, 0, "Create new thread failed!");
		count++;
	}
	count = 0;
	while (count < NB_THREAD)
	{
		SDL_WaitThread(param->thread[count], &threadReturnValue);
		if (threadReturnValue != 0)
			error(0, 0, "Thread wrong return value");
		count++;
	}
	param->refresh = 0;
}