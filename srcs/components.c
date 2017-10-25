/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:53:46 by aguemy            #+#    #+#             */
/*   Updated: 2017/10/25 18:51:49 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_putvec(double *x)
{
	ft_putdbl(x[0], 4);
	ft_putstr(", ");
	ft_putdbl(x[1], 4);
	ft_putstr(", ");
	ft_putdbl(x[2], 4);
}

int		rgb_ratio(int color, double a)
{
	int 	r;
	int 	g;
	int 	b;

	r = ft_min((int)trunc(a * ((color) & 0xFF)), 255);
	g = ft_min((int)trunc(a * ((color >> 8) & 0xFF)), 255);
	b = ft_min((int)trunc(a * ((color >> 16) & 0xFF)), 255);
	return (r + g * 256 + b * 256 * 256);
}

int		rgb_color(unsigned char red, unsigned char green, unsigned char blue)
{
	int		rgb;

	rgb = (blue << 16) | (green << 8) | (red);
	return (rgb);
}

int		color_summer(int col1, int col2)
{
	return (ft_min(255, (int)trunc(col1 / 256 / 256) + (int)trunc(col2 / 256 / 256)) +
		ft_min(255, ((int)trunc(col1 / 256) % 256 + (int)trunc(col2 / 256) % 256)) * 256 +
		ft_min(255, col1 % 256 % 256 + col2 % 256 % 256) * 256 * 256);
}

void	store_pixel_thread(t_param *param, int color, int num_surf)
{
	// mprintf(1, "Surface : [%d], x : [%d], y : [%d], color : [%d]\n", num_surf, param->i[1], param->i[0], color);
	if (param->graph->show_tmp == 0) {
		if (param->i[0] >= 0 && param->i[0] - ((num_surf) *
			WINDOW_SDL_HEIGHT / NB_THREAD) < WINDOW_SDL_HEIGHT / NB_THREAD
		&& param->i[1] >= 0 && param->i[1] < WINDOW_SDL_WIDTH)
			putpxl(param->graph->surfs[num_surf],
			param->i[1], param->i[0] - (num_surf) *
			WINDOW_SDL_HEIGHT / NB_THREAD, 
			SDL_MapRGBA(param->graph->surfs[num_surf]->format,
			(color) & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF, 0xFF));
	} else {		
		if (param->i[0] >= 0 && param->i[0] - ((num_surf) *
			WINDOW_SDL_HEIGHT / NB_THREAD) < WINDOW_SDL_HEIGHT / NB_THREAD
		&& param->i[1] >= 0 && param->i[1] < WINDOW_SDL_WIDTH)
			putpxl(param->graph->tmp_surfs[num_surf],
			param->i[1], param->i[0] - (num_surf) *
			WINDOW_SDL_HEIGHT / NB_THREAD, 
			SDL_MapRGBA(param->graph->tmp_surfs[num_surf]->format,
			(color) & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF, 0xFF));
	}
}

void store_pixel_single(t_param *param, int color, int num_surf)
{
	int height;
	
	if (num_surf * (WINDOW_SDL_HEIGHT / NB_THREAD) != 0)
		height = param->i[0] % (num_surf * (WINDOW_SDL_HEIGHT / NB_THREAD));
	else
		height = param->i[0];
	// mprintf(1, "Store = Surface : [%d], x : [%d], y : [%d], color : [%d]\n", num_surf, param->i[1], height, color);
	if (param->graph->show_tmp == 0) {
		if (height >= 0 && height < WINDOW_SDL_HEIGHT / NB_THREAD
		&& param->i[1] >= 0 && param->i[1] < WINDOW_SDL_WIDTH)
			putpxl(param->graph->surfs[num_surf],
			param->i[1], height, 
			SDL_MapRGBA(param->graph->surfs[num_surf]->format,
			(color) & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF, 0xFF));
	} else {		
		if (height >= 0 && height < WINDOW_SDL_HEIGHT / NB_THREAD
			&& param->i[1] >= 0 && param->i[1] < WINDOW_SDL_WIDTH)
			putpxl(param->graph->tmp_surfs[num_surf],
			param->i[1], height, 
			SDL_MapRGBA(param->graph->tmp_surfs[num_surf]->format,
			(color) & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF, 0xFF));
	}
}

void	display_info(t_param *param)
{
	if (param->i[0] == 500 && param->i[1] == 500)
	{
		ft_putstr("current_obj = ");
		if (!param->path->current_object)
			ft_putnbr(-1);
		else
			ft_putnbr(param->path->current_object->type);
		ft_putchar('\n');
		ft_putstr("intersect_obj = ");
		if (!param->intersect_object)
			ft_putnbr(-1);
		else
			ft_putnbr(param->intersect_object->type);
		ft_putchar('\n');
		ft_putstr("param->path->x = ");
//		if (!param->path->x)
//			ft_putnbr(-1);
//		else
			ft_putvec(param->path->x);
		ft_putchar('\n');
		ft_putstr("normale = ");
//		if (!param->path->n)
//			ft_putnbr(-1);
//		else
			ft_putvec(param->path->n);
		ft_putchar('\n');
	}
}
