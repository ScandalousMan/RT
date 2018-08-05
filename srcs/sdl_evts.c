/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_evts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 09:46:28 by malexand          #+#    #+#             */
/*   Updated: 2018/03/16 15:29:47 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Function to handle keyboard input
*/
void	handle_keyboard(t_param *param)
{
	if (param->graph->input[SDL_SCANCODE_R] == TRUE) {
		param->graph->show_tmp = 0;
	}
	if (param->graph->input[SDL_SCANCODE_S] == TRUE) {
		param->graph->show_tmp = 1;
		sepia(param);
	}
	if (param->graph->input[SDL_SCANCODE_C] == TRUE) {
		param->graph->show_tmp = 1;
		cartoon(param);
	}
	if (param->graph->input[SDL_SCANCODE_G] == TRUE) {
		param->graph->show_tmp = 1;
		printf("GREYSCALE\n");
		greyscale(param);
	}
	if (param->graph->input[SDL_SCANCODE_B] == TRUE) {
		param->graph->show_tmp = 1;
		blur(param);
	}
	if (param->graph->input[SDL_SCANCODE_H] == TRUE) {
		param->graph->show_tmp = 1;
		stereoscopy(param);
	}
}

/*
** Handle clic input
*/
void	handle_clic(t_param *param, SDL_MouseButtonEvent evt)
{
	int test;
	int type;
	int third;
	int num;

	test = -1;
	type = -1;
	third = -1;
	num = -1;
	if (evt.button == SDL_BUTTON_LEFT) {
		if (param->pxl_infos[evt.y][evt.x]->object) {
			test = param->pxl_infos[evt.y][evt.x]->col;
			type = param->pxl_infos[evt.y][evt.x]->calc_col;
			third = param->pxl_infos[evt.y][evt.x]->object->type;
			num = param->pxl_infos[evt.y][evt.x]->object->num;
		}
		mprintf(1, "Mouse LEFT button pressed at : x=[%d], y=[%d], num=[%d] type=[%d], col=[%d], calc_col=[%d]\n", evt.x, evt.y, num, third, test, type);
	} else if (evt.button == SDL_BUTTON_MIDDLE) {
		ft_putendl("Mouse MIDDLE button pressed");
	} else if (evt.button == SDL_BUTTON_RIGHT) {
		ft_putendl("Mouse RIGHT button pressed");
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
		if (evt.type == SDL_KEYDOWN) {
			param->graph->input[evt.key.keysym.scancode] = TRUE;
			my_key_func(evt.key.keysym.sym, param);
			param->refresh = 1;
		}
		if (evt.type == SDL_KEYUP)
			param->graph->input[evt.key.keysym.scancode] = FALSE;
		if (evt.window.windowID == SDL_GetWindowID(param->graph->win_gl))
			nk_sdl_handle_event(&evt);
		if (evt.window.windowID == SDL_GetWindowID(param->graph->win_sdl) &&
		evt.button.type == SDL_MOUSEBUTTONDOWN)
			handle_clic(param, evt.button);
		if (evt.key.state == SDL_PRESSED)
			handle_keyboard(param);
	}
	nk_input_end(param->graph->ctx);
}
