/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:53:46 by aguemy            #+#    #+#             */
/*   Updated: 2018/03/19 18:05:03 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ft_absdbl(double a)
{
	return a < 0.0 ? -1.0 * a : a;
}

int 		ft_absint(int a)
{
	return a < 0 ? -1 * a : a;
}

void		ft_putvec(double *x)
{
	ft_putdbl(x[0], 4);
	ft_putstr(", ");
	ft_putdbl(x[1], 4);
	ft_putstr(", ");
	ft_putdbl(x[2], 4);
}
