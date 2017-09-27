/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:53:46 by aguemy            #+#    #+#             */
/*   Updated: 2017/09/27 14:21:46 by malexand         ###   ########.fr       */
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

void	store_pixel(t_param *param, int color)
{
	if (param->i[0] >= 0 && param->i[0] < WINDOW_SDL_WIDTH / NB_THREAD && param->i[1] >= 0 && param->i[1] < WINDOW_SDL_HEIGHT / NB_THREAD)
		putpxl(param->graph->surfs[param->current_thread], param->i[1], param->i[0],
		SDL_MapRGBA(param->graph->surfs[param->current_thread]->format,(color) & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF, 0xFF));
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
		if (!param->path->x)
			ft_putnbr(-1);
		else
			ft_putvec(param->path->x);
		ft_putchar('\n');
		ft_putstr("normale = ");
		if (!param->path->n)
			ft_putnbr(-1);
		else
			ft_putvec(param->path->n);
		ft_putchar('\n');
	}
}