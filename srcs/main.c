/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2017/09/26 16:37:55 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation.h"
#include "tool.h"

int		main(void)
{
	t_sdl	*graph;

	if ((graph = graph_init()) == NULL)
		return (0);
	sdl_init(graph);
	while (graph->input[SDL_SCANCODE_ESCAPE] == FALSE)
	{
		sdl_pull_evts(graph);
		nukl_gui(graph);
		sdl_draw(graph);
	}
	sdl_quit(graph);
	return (0);
}
