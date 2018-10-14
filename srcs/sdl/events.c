/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 09:46:28 by malexand          #+#    #+#             */
/*   Updated: 2018/09/08 17:10:12 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	handle_clic(t_param *param, SDL_MouseButtonEvent evt)
{
	if (evt.button == SDL_BUTTON_LEFT)
	{
		if (param->pxl_infos[evt.y][evt.x])
		{
		printf("Mouse LEFT button pressed at : x=[%d], y=[%d], num=[%d]\n",
			evt.x, evt.y, param->pxl_infos[evt.y][evt.x]);
		} else {
			printf("Mouse LEFT button pressed at : x=[%d], y=[%d] no object\n", evt.x, evt.y);
		}
	}
	else if (evt.button == SDL_BUTTON_MIDDLE)
		ft_putendl("Mouse MIDDLE button pressed");
	else if (evt.button == SDL_BUTTON_RIGHT)
		ft_putendl("Mouse RIGHT button pressed");
}

static	void	handle_keyboard_events(t_param *param, SDL_Event evt)
{
	printf("Keycode: %d, Charac: %c\n", evt.key.keysym.sym,
		evt.key.keysym.sym);
	if (SDL_GetModState() != KMOD_LSHIFT && SDL_GetModState() != KMOD_RSHIFT &&
	SDL_GetModState() != KMOD_CAPS)
		handle_keyboard(evt.key.keysym.sym, param);
	else
		handle_keyboard_caps(evt.key.keysym.sym, param);
}

void			sdl_pull_evts(t_param *param)
{
	SDL_Event evt;

	nk_input_begin(param->graph->ctx);
	while (SDL_PollEvent(&evt))
	{
		if (evt.window.event == SDL_WINDOWEVENT_CLOSE || evt.type == SDL_QUIT ||
		evt.key.keysym.sym == SDLK_ESCAPE)
			param->quit = TRUE;
		if (evt.window.windowID == SDL_GetWindowID(param->graph->win_gl))
			nk_sdl_handle_event(&evt);
		if (evt.window.windowID == SDL_GetWindowID(param->graph->win_sdl) &&
		evt.button.type == SDL_MOUSEBUTTONDOWN)
			handle_clic(param, evt.button);
		if (evt.type == SDL_KEYDOWN && evt.key.repeat == 0)
			handle_keyboard_events(param, evt);
	}
	nk_input_end(param->graph->ctx);
}
