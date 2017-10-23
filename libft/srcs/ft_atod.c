/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <aguemy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:15:41 by aguemy            #+#    #+#             */
/*   Updated: 2017/10/23 19:05:08 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_pow(double a, int n)
{
	if (n == 0)
		return (1);
	else if (n < 0 && a == 0)
		return (0);
	else if (n < 0 && n != -2147483648)
		return (ft_pow(1.0 / a, -1 * n));
	else
		return (a * ft_pow(a, n - 1));
}

static double	ft_normed_atod(double final, const char *str, int i, int flag)
{
	int		j;

	j = i + 1;
	if (str[i] == '.')
	{
		j = i + 1;
		while (str[j] < 58 && str[j] > 47 && j < PARSING_PRECISION)
		{
			final += flag * (str[j] - 48) * ft_pow(0.1, j - i);
			j++;
		}
	}
	return (final);
}

double			ft_atod(const char *str)
{
	int		i;
	int		flag;
	double	final;

	i = 0;
	flag = 1;
	final = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			flag = -1;
		i++;
	}
	while (str[i] < 58 && str[i] > 47)
	{
		final = final * 10.0 + (double)(flag * (str[i] - 48));
		i++;
	}
	return (ft_normed_atod(final, str, i, flag));
}
