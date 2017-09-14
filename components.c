/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:53:46 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/29 11:30:12 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_putvec(double *x)
{
	ft_putdbl(x[0]);
	ft_putstr(", ");
	ft_putdbl(x[1]);
	ft_putstr(", ");
	ft_putdbl(x[2]);
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

char	*addr_init(void *img)
{
	char	*addr;
	int		detail[3];

	detail[0] = 4;
	detail[1] = WIDTH * 4;
	detail[2] = 0;
	addr = mlx_get_data_addr(img, &(detail[0]), &(detail[1]), &(detail[2]));
	ft_bzero(addr, HEIGHT * WIDTH * 4);
	return (addr);
}

void	store_pixel(t_param *param, int color)
{
	if (param->i[0] >= 0 && param->i[0] < HEIGHT && param->i[1] >= 0 && param->i[1] < WIDTH)
	{
		param->addr[(param->i[0] * WIDTH + param->i[1]) * 4 + 2] = (color) & 0xFF;
		param->addr[(param->i[0] * WIDTH + param->i[1]) * 4 + 1] = (color >> 8) & 0xFF;
		param->addr[(param->i[0] * WIDTH + param->i[1]) * 4 + 0] = (color >> 16) & 0xFF;
	}
}

void	display_info(t_param *param)
{
	if (param->i[0] == 500 && param->i[1] == 500)
	{
		ft_putstr("current_obj = ");
		if (!param->current_object)
			ft_putnbr(-1);
		else
			ft_putnbr(param->current_object->type);
		ft_putchar('\n');
		ft_putstr("intersect_obj = ");
		if (!param->intersect_object)
			ft_putnbr(-1);
		else
			ft_putnbr(param->intersect_object->type);
		ft_putchar('\n');
		ft_putstr("param->x = ");
		if (!param->x)
			ft_putnbr(-1);
		else
			ft_putvec(param->x);
		ft_putchar('\n');
		ft_putstr("normale = ");
		if (!param->n)
			ft_putnbr(-1);
		else
			ft_putvec(param->n);
		ft_putchar('\n');
	}
}