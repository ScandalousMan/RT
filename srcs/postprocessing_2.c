/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocessing_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2018/10/31 21:49:47 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		greyscaler(int color)
{
	return (int)(MIN(MIN(color & 0xFF, (color >> 8) & 0xFF),
		(color >> 16) & 0xFF) + MAX(MAX(color & 0xFF, (color >> 8) & 0xFF),
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
			putpxl(param, param->i[0], param->i[1],
				(Uint32)greyscaler(getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

void	stereoscopy(t_param *param)
{
	t_param *stereo_param;
	Uint32	pixel1;
	Uint32	pixel2;

	if ((stereo_param = stereoscopy_cpy(param)))
	{
		launch_threads(stereo_param);
		param->i[0] = 0;
		while (param->i[0] < WINDOW_SDL_HEIGHT)
		{
			param->i[1] = 0;
			while (param->i[1] < WINDOW_SDL_WIDTH)
			{
				pixel1 = getpxl(stereo_param, param->i[0], param->i[1]);
				pixel2 = getpxl(param, param->i[0], param->i[1]);
				putpxl(param, param->i[0], param->i[1],
					rgb_color((unsigned char)((pixel2 >> 16) & 0xFF), 0,
						(unsigned char)(pixel1 & 0xFF)));
				param->i[1]++;
			}
			param->i[0]++;
		}
		stereoscopy_free(stereo_param);
	}
}

int		negativer(int color)
{
	return ((255 - (color & 0xFF)) |
		((255 - ((color >> 8) & 0xFF)) << 8) |
		((255 - ((color >> 16) & 0xFF)) << 16));
}

void	to_negative(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1],
				negativer(getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}
