/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2017/11/08 18:37:30 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation.h"
#include "rt.h"
#include <rt_parser.h>

/*utiliser la fonction error pour toute erreur*/

t_state	**state_init()
{
	t_state **state;
	int 	i;
	int 	j;

	i = 0;
	if (!(state = (t_state**)malloc(sizeof(t_state*) * WINDOW_SDL_HEIGHT)))
		return NULL;
	while (i < WINDOW_SDL_HEIGHT)
	{
		j = 0;
		if (!(state[i] = (t_state*)malloc(sizeof(t_state) * WINDOW_SDL_WIDTH)))
			return NULL;
		while (j < WINDOW_SDL_WIDTH)
		{
				state[i][j].d = 0;
				state[i][j].obj_num = NULL;
			j++;
		}
		i++;
	}
	return state;
}

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
	param->start = clock();//TODO delete
	if ((param->graph = graph_init()) == NULL)
		error(0, 0, "Can't allocate graph struct");
	if (!(param->state = state_init()))
		return (-1);
	if (!rt_parser(param, filename))
		return (1);
	sdl_init(param->graph);
	lauch_threads(param);
	while (param->graph->input[SDL_SCANCODE_ESCAPE] == FALSE)
	{
		sdl_pull_evts(param);
		nukl_gui(param->graph);
		if (param->refresh == 1)
		{
			sdl_draw(param->graph);
			param->end = clock();//TODO delete
			printf("Render %.5lf secondes...\n", (double)(param->end - param->start) / CLOCKS_PER_SEC);
			param->refresh = 0;
		}
	}
	sdl_quit(param->graph);
	return (0);
}
