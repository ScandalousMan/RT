/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:39:31 by aguemy            #+#    #+#             */
/*   Updated: 2017/03/13 14:47:48 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

void	ft_putdbl(double d, int index)
{
	int	i;

	i = 0;
	if (d < 0.0 && d > -1.0)
		ft_putchar('-');
	ft_putnbr(trunc(d));
	d -= trunc(d);
	if (d < 0.0)
		d = -d;
	if (d != 0.0)
		ft_putchar('.');
	while (d != 0.0 && i < index)
	{
		d = d * 10;
		ft_putnbr(trunc(d));
		d -= trunc(d);
		i++;
	}
}