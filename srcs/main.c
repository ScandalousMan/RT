/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2017/10/24 21:49:12 by alex             ###   ########.fr       */
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
				state[i][j].obj_num = NULL;
			j++;
		}
		i++;
	}
	return state;
}

int		main(void)
{
	t_param	*param;

	if (!(param = struct_create()))
		return (-1);
	if ((param->graph = graph_init()) == NULL)
		error(0, 0, "Can't allocate graph struct");
	if (!(param->state = state_init()))
		return (-1);
	rt_parser(param);
	sdl_init(param->graph);
	lauch_threads(param);
	while (param->graph->input[SDL_SCANCODE_ESCAPE] == FALSE)
	{
		sdl_pull_evts(param);
		nukl_gui(param->graph);
		if (param->refresh == 1)
		{
			sdl_draw(param->graph);
			param->refresh = 0;
		}
	}
	sdl_quit(param->graph);
	return (0);
}