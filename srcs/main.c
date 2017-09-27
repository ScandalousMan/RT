/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2017/09/27 15:06:40 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation.h"
#include "rt.h"

/*utiliser la fonction error pour toute erreur*/

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
	sdl_init(graph);
	lauch_threads(param);
	while (graph->input[SDL_SCANCODE_ESCAPE] == FALSE)
	{
		sdl_pull_evts(graph);
		nukl_gui(graph);
		sdl_draw(graph);
	}
	sdl_quit(graph);
	return (0);
}