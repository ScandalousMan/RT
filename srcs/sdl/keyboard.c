/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:46:21 by malexand          #+#    #+#             */
/*   Updated: 2018/08/12 18:56:30 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	handle_keyboard(int keycode, t_param *param)
{
	if (keycode == SDLK_RIGHT) //droite
	{
		param->eye[0] += 10;
	}
	else if (keycode == SDLK_LEFT) //gauche
	{
		param->eye[0] -= 10;
	}
	else if (keycode == SDLK_UP) //haut
	{
		param->eye[2] += 10;
	}
	else if (keycode == SDLK_DOWN) //bas
	{
		param->eye[2] -= 10;
	}
	else if (keycode == SDLK_KP_PLUS) //zoom in
	{
		param->eye[1] += 10;
	}
	else if (keycode == SDLK_KP_MINUS) //zoom out
	{
		param->eye[1] -= 10;
	}
	else if (keycode == SDLK_a)
	{
		eye_rotation(0.0, 0.0, param->macro.rotation_angle, param);
	}
	else if (keycode == SDLK_q)
	{
		eye_rotation(param->macro.rotation_angle, 0.0, 0.0, param);
	}
	else if (keycode == SDLK_w)
	{
		eye_rotation(-param->macro.rotation_angle, 0.0, 0.0, param);
	}
	else if (keycode == SDLK_s)
	{
		eye_rotation(0.0, 0.0, -param->macro.rotation_angle, param);
	}
	else if (keycode == SDLK_z)
	{
		eye_rotation(0.0, -param->macro.rotation_angle, 0.0, param);
	}
	else if (keycode == SDLK_x)
	{
		eye_rotation(0.0, param->macro.rotation_angle, 0.0, param);
	}
}

void	handle_keyboard_caps(int keycode, t_param *param)
{
	printf(" /!\\ Handle SHIFT KEY /!\\");
	if (keycode == SDLK_x)
	{
		eye_rotation(0.0, param->macro.rotation_angle, 0.0, param);
	}
}