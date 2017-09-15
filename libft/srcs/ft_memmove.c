/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:32:57 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/23 10:35:03 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				i;
	unsigned char	*csrc;
	unsigned char	*cdst;

	i = 0;
	csrc = (unsigned char*)src;
	cdst = (unsigned char*)dst;
	if (len == 0)
		return (dst);
	if (csrc > cdst)
		while (i < (int)len)
		{
			cdst[i] = csrc[i];
			i++;
		}
	else
	{
		i = (int)(len - 1);
		while (i >= 0)
		{
			cdst[i] = csrc[i];
			i--;
		}
	}
	return ((void*)(cdst));
}
