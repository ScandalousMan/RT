/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocessing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacrozet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 15:22:28 by vacrozet          #+#    #+#             */
/*   Updated: 2018/09/09 15:27:14 by vacrozet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	return (((int)((color & 0xFF) / param->macro.cartoon_factor)
				* param->macro.cartoon_factor) | ((int)(((color >> 8) & 0xFF)
				/ param->macro.cartoon_factor) * param->macro.cartoon_factor
				<< 8)
			| ((int)(((color >> 16) & 0xFF) / param->macro.cartoon_factor)
				* param->macro.cartoon_factor << 16));
}

void	cartoon(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			putpxl(param, param->i[0], param->i[1], cartooner(param,
						getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

void	blur(t_param *param)
{
	double	res[3];
	int		rs;
	double	wsum;
	double	wght;
	double	dsq;
	Uint32	col;
	int		x;
	int		y;
	int		ix;
	int		iy;

	rs = (int)ceil((double)param->macro.blur_radius * 2.57);
	printf("value of rs: %d\n", rs);
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			res[0] = 0;
			res[1] = 0;
			res[2] = 0;
			wsum = 0.0;
			iy = param->i[0] - rs;
			while (iy < param->i[0] + rs + 1)
			{
				ix = param->i[1] - rs;
				while (ix < param->i[1] + rs + 1)
				{
					x = ft_min(WINDOW_SDL_WIDTH - 1, ft_max(0, ix));
					y = ft_min(WINDOW_SDL_HEIGHT - 1, ft_max(0, iy));
					dsq = (double)((param->i[1] - ix) * (ix - param->i[1])
							+ (iy - param->i[0]) * (param->i[0] - iy));
					wght = exp(dsq / (double)(2 * param->macro.blur_radius
						* param->macro.blur_radius)) / M_PI / (double)(2
						* param->macro.blur_radius * param->macro.blur_radius);
					col = getpxl(param, iy, ix);
					res[0] += (double)((col >> 16) & 0xFF) * wght;
					res[1] += (double)((col >> 8) & 0xFF) * wght;
					res[2] += (double)(col & 0xFF) * wght;
					wsum += wght;
					ix++;
				}
				iy++;
			}
			res[0] = res[0] / wsum;
			res[1] = res[1] / wsum;
			res[2] = res[2] / wsum;
			putpxl(param, param->i[0], param->i[1],
					rgb_color((unsigned char)(res[0]), (unsigned char)(res[1]),
						(unsigned char)(res[2])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

void	blur(t_param *param)
{
	double 	res[3];
	int			rs;
	double	wsum;
	double	wght;
	double	dsq;
	Uint32	col;
	// int			x;
	// int			y;
	int 		ix;
	int 		iy;

	rs = (int)ceil((double)param->macro.blur_radius * 2.57);
	printf("value of rs: %d\n", rs);
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
	param->i[1] = 0;
	while (param->i[1] < WINDOW_SDL_WIDTH)
	{
		res[0] = 0;
		res[1] = 0;
		res[2] = 0;
		wsum = 0.0;
		iy = param->i[0] - rs;
		while (iy < param->i[0] + rs + 1)
		{
			ix = param->i[1] - rs;
			while (ix < param->i[1] + rs + 1)
			{
				// x = ft_min(WINDOW_SDL_WIDTH - 1, ft_max(0, ix));
				// y = ft_min(WINDOW_SDL_HEIGHT - 1, ft_max(0, iy));
				dsq = (double)((param->i[1] - ix) * (ix - param->i[1]) + (iy - param->i[0]) * (param->i[0] - iy));
				wght = exp(dsq / (double)(2 * param->macro.blur_radius * param->macro.blur_radius)) / M_PI / (double)(2 * param->macro.blur_radius * param->macro.blur_radius);
				col = getpxl(param, iy, ix);
				res[0] += (double)((col >> 16) & 0xFF) * wght;
				res[1] += (double)((col >> 8) & 0xFF) * wght;
				res[2] += (double)(col & 0xFF) * wght;
				wsum += wght;
				ix++;
			}
			iy++;
		}
		res[0] = res[0] / wsum;
		res[1] = res[1] / wsum;
		res[2] = res[2] / wsum;
			putpxl(param, param->i[0], param->i[1], 
				rgb_color((unsigned char)(res[0]), (unsigned char)(res[1]), (unsigned char)(res[2])));
		param->i[1]++;
	}
	param->i[0]++;
	}
}

void	stereoscopy(t_param *param)
{
	t_param		*stereo_param;
	Uint32		pixel1;
	Uint32		pixel2;

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
			putpxl(param, param->i[0], param->i[1], negativer(getpxl(param, param->i[0], param->i[1])));
			param->i[1]++;
		}
		param->i[0]++;
	}
}

