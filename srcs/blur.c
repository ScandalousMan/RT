/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2018/10/31 21:49:47 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_blurred(t_param *param, int *i, double *j, double *res)
{
	Uint32	col;

	while (i[2] < param->i[0] + i[1] + 1)
	{
		i[0] = param->i[1] - i[1];
		while (i[0] < param->i[1] + i[1] + 1)
		{
			j[2] = (double)((param->i[1] - i[0]) * (i[0] - param->i[1]) +
				(i[2] - param->i[0]) * (param->i[0] - i[2]));
			j[1] = exp(j[2] / (double)(2 * param->macro.blur_radius *
				param->macro.blur_radius)) / M_PI / (double)(2 *
				param->macro.blur_radius * param->macro.blur_radius);
			col = getpxl(param, i[2], i[0]);
			res[0] += (double)((col >> 16) & 0xFF) * j[1];
			res[1] += (double)((col >> 8) & 0xFF) * j[1];
			res[2] += (double)(col & 0xFF) * j[1];
			j[0] += j[1];
			i[0]++;
		}
		i[2]++;
	}
	res[0] = res[0] / j[0];
	res[1] = res[1] / j[0];
	res[2] = res[2] / j[0];
}

void	blur(t_param *param)
{
	double	res[3];
	int		i[3];
	double	j[3];

	i[1] = (int)ceil((double)param->macro.blur_radius * 2.57);
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			res[0] = 0;
			res[1] = 0;
			res[2] = 0;
			j[0] = 0.0;
			i[2] = param->i[0] - i[1];
			get_blurred(param, i, j, res);
			putpxl(param, param->i[0], param->i[1],
				rgb_color((unsigned char)(res[0]), (unsigned char)(res[1]),
					(unsigned char)(res[2])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}
