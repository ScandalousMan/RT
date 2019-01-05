/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2018/10/31 21:49:47 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	smoothNoise(double x, double y, t_param *param)
{
	double	fractX;
	double	fractY;
	int		i[4];
	double	value;

	fractX = x - floor(x);
	fractY = y - floor(y);
	i[0] = ((int)(floor(x) + NOISE_SIZE)) % NOISE_SIZE;
	i[2] = ((int)(floor(y) + NOISE_SIZE)) % NOISE_SIZE;
	i[1] = (i[0] + NOISE_SIZE - 1) % NOISE_SIZE;
	i[3] = (i[2] + NOISE_SIZE - 1) % NOISE_SIZE;
	value = 0.0;
	value += fractX     * fractY     * param->perlin_noise[i[2]][i[0]];
	value += (1 - fractX) * fractY     * param->perlin_noise[i[2]][i[1]];
	value += fractX     * (1 - fractY) * param->perlin_noise[i[3]][i[0]];
	value += (1 - fractX) * (1 - fractY) * param->perlin_noise[i[3]][i[1]];
	return (value);
}

double	turbulence(double x, double y, double size, t_param *param)
{
	double	value = 0.0;
	double	initialSize;

	initialSize = size;
	while (size >= 1)
	{
		value += smoothNoise(x / size, y / size, param) * size;
		size /= 2.0;
	}
	return(128.0 * value / initialSize);
}

double	marble_ratio(double u, double v, double size, t_param *param)
{
	double x_period;
	double y_period;

	x_period = 5.0;
	y_period = 10.0;
	return ft_absdbl(M_PI * (u * x_period / (double)NOISE_SIZE +
		v * y_period / (double)NOISE_SIZE +
		TURB_POWER * turbulence(u, v, size, param) / 256.0));
}

char	wood_ratio(double u, double v, double size, t_param *param)
{
	double sineValue;
	double xy_period;

	xy_period = 12.0;
	sineValue = 128.0 * ft_absdbl(sin(2.0 * xy_period * sqrt(
			ft_pow((u - NOISE_SIZE / 2) / (double)NOISE_SIZE, 2) +
			ft_pow((v - NOISE_SIZE / 2) / (double)NOISE_SIZE, 2)
		) + TURB_POWER * turbulence(u, v, size, param) / 256.0 * M_PI));
	return ((char)sineValue);
}
