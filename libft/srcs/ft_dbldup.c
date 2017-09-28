/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbldup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 15:12:03 by malexand          #+#    #+#             */
/*   Updated: 2017/09/28 15:12:19 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		*ft_dbldup(const double *src)
{
	double	*new_dbl;

	if (src == NULL)
		return (NULL);
	if (!(new_dbl = (double*)malloc(sizeof(double))))
		return (NULL);
	*new_dbl = *src;
	return (new_dbl);
}
