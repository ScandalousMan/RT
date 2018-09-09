/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:53:46 by aguemy            #+#    #+#             */
/*   Updated: 2018/09/09 17:00:45 by vacrozet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			rgb_ratio(int color, double a)
{
	return ((ft_min((int)trunc(a * ((color >> 16) & 0xFF)), 255) << 16)
			| (ft_min((int)trunc(a * ((color >> 8) & 0xFF)), 255) << 8)
			| ft_min((int)trunc(a * ((color) & 0xFF)), 255));
}

inline int	rgb_color(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}

int			color_summer(int col1, int col2)
{
	return (
			((ft_min(255, (int)trunc((col1 >> 16) & 0xFF)
				+ (int)trunc((col2 >> 16) & 0xFF))) << 16)
			| (ft_min(255, (((int)trunc(col1 >> 8) & 0xFF)
				+ ((int)trunc(col2 >> 8) & 0xFF))) << 8)
			| (ft_min(255, (col1 & 0xFF) + (col2 & 0xFF))));
}

int			color_absorber(int obj_col, int light_col)
{
	return (
			ft_min(255, (int)trunc(((obj_col >> 16) & 0xFF) * ((light_col >> 16)
				& 0xFF) / 255)) << 16 | ft_min(255, (int)trunc(((obj_col >> 8)
				& 0xFF) * ((light_col >> 8) & 0xFF) / 255)) << 8 | ft_min(255,
				(int)trunc((obj_col & 0xFF) * (light_col & 0xFF) / 255)));
}

void		display_info(t_param *param)
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
		ft_putvec(param->path->x);
		ft_putchar('\n');
		ft_putstr("normale = ");
		ft_putvec(param->path->n);
		ft_putchar('\n');
	}
}
