/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_evts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 09:46:28 by malexand          #+#    #+#             */
/*   Updated: 2017/10/16 11:15:30 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	evts_handler(t_param *param)
{
	if (param->graph->input[SDL_SCANCODE_SPACE] == TRUE) {
		param->graph->show_tmp = 1;
		greyscale(param);
		param->refresh = 1;
		param->graph->input[SDL_SCANCODE_SPACE] = FALSE;
	}
}

/*
** SDL events handling function
*/
void	sdl_pull_evts(t_param *param)
{
	SDL_Event evt;

	nk_input_begin(param->graph->ctx);
	while (SDL_PollEvent(&evt))
	{
		if (evt.window.event == SDL_WINDOWEVENT_CLOSE || evt.type == SDL_QUIT)
			param->graph->input[SDL_SCANCODE_ESCAPE] = TRUE;
		if (evt.type == SDL_KEYDOWN){
			param->graph->input[evt.key.keysym.scancode] = TRUE;
		}
		if (evt.type == SDL_KEYUP)
			param->graph->input[evt.key.keysym.scancode] = FALSE;
		if (evt.window.windowID == 1)
			nk_sdl_handle_event(&evt);
	}
	evts_handler(param);
	nk_input_end(param->graph->ctx);
}
