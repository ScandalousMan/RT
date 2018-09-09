/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacrozet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:04:34 by vacrozet          #+#    #+#             */
/*   Updated: 2018/09/09 16:04:36 by vacrozet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		smoothNoise(double x, double y, t_param *param)
{
	double	fractX;
	double	fractY;
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	double	value;

	fractX = x - floor(x);
	fractY = y - floor(y);
	x1 = ((int)(floor(x) + NOISE_SIZE)) % NOISE_SIZE;
	y1 = ((int)(floor(y) + NOISE_SIZE)) % NOISE_SIZE;
	x2 = (x1 + NOISE_SIZE - 1) % NOISE_SIZE;
	y2 = (y1 + NOISE_SIZE - 1) % NOISE_SIZE;
	value = 0.0;
	value += fractX * fractY * param->perlin_noise[y1][x1];
	value += (1 - fractX) * fractY * param->perlin_noise[y1][x2];
	value += fractX * (1 - fractY) * param->perlin_noise[y2][x1];
	value += (1 - fractX) * (1 - fractY) * param->perlin_noise[y2][x2];
	return (value);
}

double		turbulence(double x, double y, double size, t_param *param)
{
	double	value;
	double	initialSize;

	value = 0.0;
	initialSize = size;
	while (size >= 1)
	{
		value += smoothNoise(x / size, y / size, param) * size;
		size /= 2.0;
	}
	return (128.0 * value / initialSize);
}

double		marble_ratio(double u, double v, double size, t_param *param)
{
	double xPeriod;
	double yPeriod;

	xPeriod = 5.0;
	yPeriod = 10.0;
	return (ft_absdbl(M_PI * (u * xPeriod / (double)NOISE_SIZE +
					v * yPeriod / (double)NOISE_SIZE +
					TURB_POWER * turbulence(u, v, size, param) / 256.0)));
}

char		wood_ratio(double u, double v, double size, t_param *param)
{
	double	sineValue;
	double	xyPeriod;

	xyPeriod = 12.0;
	sineValue = 128.0 * ft_absdbl(sin(2.0 * xyPeriod * sqrt(
					ft_pow((u - NOISE_SIZE / 2) / (double)NOISE_SIZE, 2) +
					ft_pow((v - NOISE_SIZE / 2) / (double)NOISE_SIZE, 2))
					+ TURB_POWER * turbulence(u, v, size, param) / 256.0
					* M_PI));
	return (char)sineValue;
}
