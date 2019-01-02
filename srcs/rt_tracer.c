/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:40:48 by jbouille          #+#    #+#             */
/*   Updated: 2018/08/06 16:03:55 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

double	*ray_direction(t_param *param, int i, int j)
{
	vec_multiply(param->f, param->look, param->path->v);
	vec_multiply(((double)WINDOW_SDL_HEIGHT * param->macro.anti_aliasing / 2.0 - (double)i) * 40.0 /
		(double)WINDOW_SDL_HEIGHT / param->macro.anti_aliasing, param->third, param->tmp_vec);
	pt_translated(param->path->v, param->tmp_vec, param->path->v);
	vec_multiply(((double)j - (double)WINDOW_SDL_WIDTH * param->macro.anti_aliasing / 2.0) * 40.0 /
		(double)WINDOW_SDL_WIDTH / param->macro.anti_aliasing, param->align, param->tmp_vec);
	pt_translated(param->path->v, param->tmp_vec, param->path->v);
	vec_to_unit_norm(param->path->v);
	return (param->path->v);
}

void	tracer_pixel(t_param *param, int pixelisation, int db_antialiasing,
	int *col)
{
	int			x[2];

	x[1] = 0;
	while (x[1] < pixelisation)
	{
		x[0] = 0;
		while (x[0] < pixelisation)
		{
			putpxl(param, param->i[0] + x[0], param->i[1] + x[1],
				rgb_color((unsigned char)(col[0] / db_antialiasing),
					(unsigned char)(col[1] / db_antialiasing),
					(unsigned char)(col[2] / db_antialiasing)));
			++x[0];
		}
	++x[1];
	}
}

void	tracer_color(t_param *param, int *col)
{
	int			tmp_col;
	int 		alias[2];

	alias[0] = 0;
	while (alias[0] < param->macro.anti_aliasing)
	{
		alias[1] = 0;
		while (alias[1] < param->macro.anti_aliasing)
		{
			ray_direction(param,
				param->macro.anti_aliasing * param->i[0] + alias[0],
				param->macro.anti_aliasing * param->i[1] + alias[1]);
			tmp_col = ray_color(param, param->eye, param->path->v, 0, param->path);
			col[0] += (tmp_col >> 16) & 0xFF;
			col[1] += (tmp_col >> 8) & 0xFF;
			col[2] += (tmp_col) & 0xFF;
			alias[1]++;
		}
		alias[0]++;
	}
}

void	rt_tracer(t_param *param)
{
	int			col[3];
	int			pixelisation;
	int			db_antialiasing;

	db_antialiasing = param->macro.anti_aliasing * param->macro.anti_aliasing;
	pixelisation = (param->to_pix) ? PIXELISATION : 1;
	param->i[0] = param->current_thread * WINDOW_SDL_HEIGHT / NB_THREAD;
	while (param->i[0] < (param->current_thread + 1) * WINDOW_SDL_HEIGHT /
		NB_THREAD)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			ft_bzero(col, sizeof(int) * 3);
			tracer_color(param, col);
			tracer_pixel(param, pixelisation, db_antialiasing, col);
			param->i[1] += pixelisation;
		}
		param->i[0] += pixelisation;
	}
}
