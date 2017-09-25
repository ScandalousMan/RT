/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_evts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 09:46:28 by malexand          #+#    #+#             */
/*   Updated: 2017/09/25 11:42:32 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

/*
** SDL events handling function
*/

void	sdl_pull_evts(t_sdl *graph)
{
	SDL_Event evt;

	nk_input_begin(graph->ctx);
	while (SDL_PollEvent(&evt))
	{
		if (evt.type == SDL_QUIT)
			graph->input[SDL_SCANCODE_ESCAPE] = TRUE;
		if (evt.type == SDL_KEYDOWN)
			graph->input[evt.key.keysym.scancode] = TRUE;
		if (evt.type == SDL_KEYUP)
			graph->input[evt.key.keysym.scancode] = FALSE;
		nk_sdl_handle_event(&evt);
	}
	nk_input_end(graph->ctx);
}
