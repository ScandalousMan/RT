/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2018/03/19 18:03:36 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation.h"
#include "rt.h"
#include <rt_parser.h>

int		main(int ac, char **av)
{
	t_param	*param;
	char	*filename;

	if (ac == 2)
		filename = av[1];
	else
		filename = "rtv1.json";
	if (!(param = struct_create()))
		return (-1);
	param->to_pix = 0;//todo change
	param->last_mv = clock();//todo change
	param->start = clock();//TODO delete
	if ((param->graph = graph_init()) == NULL)
		error(0, 0, "Can't allocate graph struct");
	if (!rt_parser(param, filename))
		return (1);
	sdl_init(param->graph);
	launch_threads(param);
	while (param->graph->input[SDL_SCANCODE_ESCAPE] == FALSE)
	{
		sdl_pull_evts(param);
		if (param->to_pix && ((double)(clock() - param->last_mv) / (double)CLOCKS_PER_SEC) > 0.4)
		{
			param->to_pix = 0;
			param->refresh = 1;
		}
		nukl_gui(param);
		if (param->refresh == 1)
		{
			lauch_threads(param);
			sdl_draw(param->graph);
			param->end = clock();//TODO delete
			printf("Render %.5lf secondes...\n", (double)(param->end - param->start) / CLOCKS_PER_SEC);
			param->refresh = 0;
		}
	}
	sdl_quit(param->graph);
	while (1)
	{}
	return (0);
}
