/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:05:21 by malexand          #+#    #+#             */
/*   Updated: 2019/01/12 14:02:26 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		perlin_noise_copy(t_param *param1, t_param *param2)
{
	param2->i[0] = 0;
	while (param2->i[0] < NOISE_SIZE)
	{
		param2->i[1] = 0;
		while (param2->i[1] < NOISE_SIZE)
		{
			param2->perlin_noise[param2->i[0]][param2->i[1]] =
				param1->perlin_noise[param2->i[0]][param2->i[1]];
			param2->i[1]++;
		}
		param2->i[0]++;
	}
}

static int	calc(void *ptr)
{
	t_param		*param;

	param = (t_param*)ptr;
	rt_tracer(param);
	return (0);
}

void		threads_loop(t_param *param, t_param *params[NB_THREAD])
{
	int count;

	count = 0;
	while (count < NB_THREAD)
	{
		mprintf(1, "Create thread %d\n", count);
		if (!(param->thread[count] = SDL_CreateThread(calc,
			"", (void *)params[count])))
			error(0, 0, "Create new thread failed!");
		count++;
	}
}

void		free_params(t_param *params[NB_THREAD])
{
	int count;

	count = 0;
	while (count < NB_THREAD)
	{
		mprintf(1, "Free param_cpy %d\n", count);
		free_path(params[count]->path);
		free_lights(params[count]->lights);
		free_objects(params[count], 0);
		free(params[count]);
		++count;
	}
}

void		launch_threads(t_param *param)
{
	int			count;
	int			thread_return_value;
	clock_t		start;
	t_param		*params[NB_THREAD];

	count = 0;
	start = clock();
	ft_putstr("==> Launch thread\n");
	init_params(param, params);
	start = clock();
	threads_loop(param, params);
	param->end = clock();
	while (count < NB_THREAD)
	{
		mprintf(1, "Wait thread %d\n", count);
		SDL_WaitThread(param->thread[count], &thread_return_value);
		if (thread_return_value != 0)
			error(0, 0, "Thread wrong return value");
		count++;
	}
	free_params(params);
	param->end = clock();
}
