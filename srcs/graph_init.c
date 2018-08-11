/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:17:15 by malexand          #+#    #+#             */
/*   Updated: 2017/09/27 12:28:46 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sdl	*graph_init(void)
{
	t_sdl	*graph;
	int		count;

	count = -1;
	if ((graph = (t_sdl*)malloc(sizeof(t_sdl))) == NULL)
		return (NULL);
	graph->show_tmp = 0;
	return (graph);
}
