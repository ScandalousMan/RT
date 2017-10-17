/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2017/10/16 11:24:36 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation.h"
#include "rt.h"

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
				state[i][j].obj_num = 0;
			j++;
		}
		i++;
	}
	return state;
}

int		main(void)
{
	t_sdl	*graph;
	t_param	*param;

	if (!(param = struct_create()))
		return (-1);
	if ((graph = graph_init()) == NULL)
		error(0, 0, "Can't allocate graph struct");
	param->graph = graph;
	param->current_thread = 0;
	if (!(param->state = state_init()))
		return (-1);
	param->refresh = 1;
	sdl_init(graph);
	rt_parser(param);
	lauch_threads(param);
	while (graph->input[SDL_SCANCODE_ESCAPE] == FALSE)
	{
		sdl_pull_evts(param);
		nukl_gui(graph);
		if (param->refresh == 1)
		{
			sdl_draw(graph);
			param->refresh = 0;
		}
	}
	sdl_quit(graph);
	return (0);
}