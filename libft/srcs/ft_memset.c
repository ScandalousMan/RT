/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 11:31:13 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/21 12:12:11 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	d;
	unsigned char	*out;
	size_t			i;

	d = (unsigned char)c;
	out = (unsigned char*)str;
	i = 0;
	while (i < n)
	{
		out[i] = d;
		i++;
	}
	return (out);
}
