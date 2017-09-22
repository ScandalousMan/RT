/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_evts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 19:17:40 by alex              #+#    #+#             */
/*   Updated: 2017/09/22 19:30:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

void	pull_evts(t_sdl *graph)
{
	SDL_Event evt;
	nk_input_begin(graph->ctx);
	while (SDL_PollEvent(&evt)) {
		if (evt.type == SDL_QUIT)
			graph->input[SDL_SCANCODE_ESCAPE] = '1';
		if (evt.type == SDL_KEYDOWN)
			graph->input[evt.key.keysym.scancode] = '1';
		if (evt.type == SDL_KEYUP)
			graph->input[evt.key.keysym.scancode] = '0';
		nk_sdl_handle_event(&evt);
	}
	nk_input_end(graph->ctx);
}
