/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocessing_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacrozet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 15:31:29 by vacrozet          #+#    #+#             */
/*   Updated: 2018/09/09 15:32:05 by vacrozet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		greyscaler(int color)
{
	return (int)(MIN(MIN(color & 0xFF, (color >> 8) & 0xFF), (color >> 16)
				& 0xFF) + MAX(MAX(color & 0xFF, (color >> 8) & 0xFF),
				(color >> 16) & 0xFF)) / 2 * (1 + 256 + 256 * 256);
}

void	greyscale(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1], (Uint32)greyscaler(
				getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

int		sepiacer(int color)
{
	return (
			(MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.393 +
				(float)((color >> 8) & 0xFF) * 0.769 + (float)((color)
				& 0xFF) * 0.189)) << 16) |
			(MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.349 +
				(float)((color >> 8) & 0xFF) * 0.686 + (float)((color)
				& 0xFF) * 0.168)) << 8) |
			(MIN((int)255, (int)((float)((color >> 16) & 0xFF) * 0.272 +
				(float)((color >> 8) & 0xFF) * 0.534 + (float)((color)
				& 0xFF) * 0.131))));
}
