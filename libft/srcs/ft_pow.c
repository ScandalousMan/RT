/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 00:21:57 by alex              #+#    #+#             */
/*   Updated: 2017/11/20 00:22:11 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double	ft_pow(double a, int n)
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