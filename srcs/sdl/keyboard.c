/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:46:21 by malexand          #+#    #+#             */
/*   Updated: 2019/01/12 15:42:09 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	handle_keyboard_1(int keycode, t_param *param)
{
	if (keycode == SDLK_KP_MINUS)
		param->eye[1] -= 10;
	else if (keycode == SDLK_a)
		eye_rotation(0.0, 0.0, param->macro.rotation_angle, param);
	else if (keycode == SDLK_q)
		eye_rotation(param->macro.rotation_angle, 0.0, 0.0, param);
	else if (keycode == SDLK_w)
		eye_rotation(-param->macro.rotation_angle, 0.0, 0.0, param);
	else if (keycode == SDLK_s)
		eye_rotation(0.0, 0.0, -param->macro.rotation_angle, param);
	else if (keycode == SDLK_z)
		eye_rotation(0.0, -param->macro.rotation_angle, 0.0, param);
	else if (keycode == SDLK_x)
		eye_rotation(0.0, param->macro.rotation_angle, 0.0, param);
	else if (keycode == SDLK_ESCAPE)
		param->quit = TRUE;
}

void	handle_keyboard(int keycode, t_param *param)
{
	if (keycode == SDLK_a || keycode == SDLK_q || keycode == SDLK_w ||
	keycode == SDLK_s || keycode == SDLK_z || keycode == SDLK_x ||
	keycode == SDLK_RIGHT || keycode == SDLK_LEFT || keycode == SDLK_UP ||
	keycode == SDLK_DOWN || keycode == SDLK_KP_PLUS || keycode == SDLK_KP_MINUS)
	{
		param->to_pix = 1;
		param->up_img.process = TRUE;
		param->up_img.post_process = TRUE;
		param->last_mv = clock();
	}
	if (keycode == SDLK_RIGHT)
		param->eye[0] += 10;
	else if (keycode == SDLK_LEFT)
		param->eye[0] -= 10;
	else if (keycode == SDLK_UP)
		param->eye[2] += 10;
	else if (keycode == SDLK_DOWN)
		param->eye[2] -= 10;
	else if (keycode == SDLK_KP_PLUS)
		param->eye[1] += 10;
	handle_keyboard_1(keycode, param);
}

void	handle_keyboard_caps(int keycode, t_param *param)
{
	if (DEBUG)
		mprintf(1, " /!\\ Handle SHIFT KEY /!\\");
	if (keycode == SDLK_x)
	{
		eye_rotation(0.0, param->macro.rotation_angle, 0.0, param);
	}
}
