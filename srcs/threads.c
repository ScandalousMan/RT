/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:05:21 by malexand          #+#    #+#             */
/*   Updated: 2017/09/27 17:26:47 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int calc(void *ptr)
{
    t_param *param;

	param = (t_param*)ptr;

    rt_parser(param);
	rt_tracer(param);
    return (0);
}

void	lauch_threads(t_param *param)
{
	int			count;
	int			threadReturnValue;
	char		*number;
	t_param		**params;

	count = 0;
	if (!(params = (t_param**)malloc(sizeof(*params) * NB_THREAD)))
		error(0, 0, "Alloc all thread not work");
	while (count < NB_THREAD)
	{
		number = ft_strnew(1);
		number[0] = 48 + count;
		if (!(params[count] = struct_create()))
			error(0, 0, "Init param for multi thread failed!");
		params[count]->graph = param->graph;
		params[count]->current_thread = count;
		number[6] = 48 + count;
		if (!(param->thread[count] = SDL_CreateThread(calc, ft_strjoin_free("Thread", number), (void *)NULL)))
			error(0, 0, "Create new thread failed!");
	}
	count = 0;
	while (count < NB_THREAD)
	{
		SDL_WaitThread(param->thread[count], &threadReturnValue);
		if (threadReturnValue != 0)
			error(0, 0, "Thread wrong return value");
	}
}