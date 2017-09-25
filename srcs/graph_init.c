/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:17:15 by malexand          #+#    #+#             */
/*   Updated: 2017/09/25 15:05:33 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

t_sdl	*graph_init(void)
{
	t_sdl	*graph;
	int		count;

	count = 0;
	if ((graph = (t_sdl*)malloc(sizeof(t_sdl))) == NULL)
		return (NULL);
	if ((graph->input = (char*)malloc(sizeof(char) * SDL_NUM_SCANCODES))
	== NULL)
		return (NULL);
	while (count < SDL_NUM_SCANCODES)
	{
		graph->input[count] = '0';
		count++;
	}
	return (graph);
}
