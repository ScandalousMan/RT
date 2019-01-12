/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2019/01/12 15:23:56 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation.h"
#include "rt.h"
#include <rt_parser.h>

void	end_program(t_param *param)
{
	sdl_quit(param->graph);
	free_objects(param, 1);
	free_lights(param->lights);
	free_path(param->path);
	free_pxl_infos(param->pxl_infos);
	free(param->thread);
	SDL_FreeSurface(param->texture);
	free(param);
}

void	perlin_noise_generator(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < NOISE_SIZE)
	{
		param->i[1] = 0;
		while (param->i[1] < NOISE_SIZE)
		{
			param->perlin_noise[param->i[0]][param->i[1]] =
				(double)(rand() % RAND_MAX) / (double)RAND_MAX;
			param->i[1]++;
		}
		param->i[0]++;
	}
}

void	apply_filters(t_param *param)
{
	if (param->up_img.post_process == TRUE && param->quit == FALSE)
	{
		if (param->macro.filter == 0)
			param->graph->show_tmp = 0;
		else
		{
			param->graph->show_tmp = 1;
			if (param->macro.filter == 1)
				cartoon(param);
			else if (param->macro.filter == 2)
				greyscale(param);
			else if (param->macro.filter == 3)
				sepia(param);
			else if (param->macro.filter == 4)
				blur(param);
			else if (param->macro.filter == 5)
				stereoscopy(param);
			else if (param->macro.filter == 6)
				to_negative(param);
		}
	}
}

void	rt_loop(t_param *param)
{
	sdl_pull_evts(param);
	if (param->to_pix &&
		((double)(clock() - param->last_mv) / (double)CLOCKS_PER_SEC) > 0.12)
	{
		param->to_pix = 0;
		param->up_img.process = TRUE;
		param->up_img.post_process = TRUE;
	}
	nukl_gui(param);
	if (param->up_img.process == TRUE && param->quit == FALSE)
	{
		param->graph->show_tmp = 0;
		update_objects(param);
		launch_threads(param);
		param->end = clock();
	}
	apply_filters(param);
	if (param->up_img.process == TRUE || param->up_img.post_process == TRUE)
	{
		sdl_draw(param->graph);
		param->up_img.process = FALSE;
		param->up_img.post_process = FALSE;
	}
}

int		main(int ac, char **av)
{
	t_param	*param;
	char	*filename;

	if (ac == 2)
		filename = av[1];
	else
		filename = "scenes/rt.json";
	if (!(param = struct_create()))
		return (-1);
	param->texture = IMG_Load("custom_texture.jpeg");
	if (!param->texture)
		mprintf(1, "Can't load texture: %s\n", IMG_GetError());
	perlin_noise_generator(param);
	param->to_pix = 0;
	param->last_mv = clock();
	param->start = clock();
	if ((param->graph = (t_sdl*)malloc(sizeof(t_sdl))) == NULL)
		error(0, 0, "Can't allocate graph struct");
	if (!rt_parser(param, filename))
		return (1);
	sdl_init(param->graph);
	while (param->quit == FALSE)
		rt_loop(param);
	end_program(param);
	return (0);
}
