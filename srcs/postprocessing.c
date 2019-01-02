/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocessing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2018/10/31 21:49:47 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		sepiacer(int color)
{
	return (
		(MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.393 +
			(float)((color >> 8) & 0xFF) * 0.769 + (float)((color) & 0xFF) * 0.189))
		<< 16) | (MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.349 +
			(float)((color >> 8) & 0xFF) * 0.686 + (float)((color) & 0xFF) * 0.168))
		<< 8) | (MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.272 +
			(float)((color >> 8) & 0xFF) * 0.534 + (float)((color) & 0xFF) * 0.131)))
	);
}

void	sepia(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1], sepiacer(getpxl(param,
				param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

int		cartooner(t_param *param, int color)
{
	return (((int)((color & 0xFF) / param->macro.cartoon_factor) *
		param->macro.cartoon_factor) | ((int)(((color >> 8) & 0xFF) /
			param->macro.cartoon_factor) * param->macro.cartoon_factor << 8) |
		((int)(((color >> 16) & 0xFF) / param->macro.cartoon_factor) *
			param->macro.cartoon_factor << 16));
}

void	cartoon(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1],
				cartooner(param, getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}
