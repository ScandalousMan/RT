/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 19:16:57 by alex              #+#    #+#             */
/*   Updated: 2017/09/22 19:30:10 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

t_sdl	*init_struct_win()
{
	t_sdl	*graph;
	int		count;

	count = 0;
	if ((graph = (t_sdl*)malloc(sizeof(t_sdl))) == NULL)
		exit(0);
	if ((graph->input = (char*)malloc(sizeof(char) * SDL_NUM_SCANCODES)) == NULL)
		exit(0);
	while (count < SDL_NUM_SCANCODES)
	{
		graph->input[count] = '0';
		count++;
	}
	return(graph);
}
