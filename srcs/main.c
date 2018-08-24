/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2018/08/29 14:52:51 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation.h"
#include "rt.h"
#include <rt_parser.h>

void	perlin_noise_generator(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < NOISE_SIZE)
	{
		param->i[1] = 0;
		while (param->i[1] < NOISE_SIZE)
		{
			param->perlin_noise[param->i[0]][param->i[1]] = (double)(rand() % RAND_MAX) / (double)RAND_MAX;
			param->i[1]++;
		}
		param->i[0]++;
	}
}

int		main(int ac, char **av)
{
	t_param	*param;
	char	*filename;
	
	if (ac == 2)
		filename = av[1];
	else
		filename = "scenes/rtv1.json";
	printf("=> creating program structure\n");
	if (!(param = struct_create()))
		return (-1);
	param->texture = IMG_Load("rouge.jpg");
	printf("=> creating random noise map\n");
	perlin_noise_generator(param);
	param->to_pix = 0; // Rasterization
	param->last_mv = clock(); // Clock
	param->start = clock(); // Clock
	printf("=> creating graph structure\n");
	if ((param->graph = graph_init()) == NULL)
		error(0, 0, "Can't allocate graph struct");
	if (ac == 2)
		filename = av[1];
	else
		filename = "rtv1.json";
	if (!rt_parser(param, filename))
		return (1);
	sdl_init(param->graph);
	param->refresh = 1;
	while (param->quit == FALSE)
	{
		sdl_pull_evts(param);
		if (param->to_pix && ((double)(clock() - param->last_mv) / (double)CLOCKS_PER_SEC) > 0.4) // Rasterization
		{
			param->to_pix = 0;
			param->refresh = 1;
		}
		nukl_gui(param);
		if (param->refresh == 1 && param->quit == FALSE)
		{
			launch_threads(param);
			sdl_draw(param->graph);
			param->end = clock(); // Clock
			printf("Render %.5lf secondes...\n", (double)(param->end - param->start) / CLOCKS_PER_SEC);
			param->refresh = 0;
		}
	}
	sdl_quit(param->graph);
	end_program(param);
	return (0);
}
