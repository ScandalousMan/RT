/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:18:54 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/23 10:34:42 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	i = 0;
	temp1 = (unsigned char*)dest;
	temp2 = (unsigned char*)src;
	while (i < n)
	{
		temp1[i] = temp2[i];
		if (temp2[i] == (unsigned char)c)
			return ((void *)&temp1[i + 1]);
		i++;
	}
	return (NULL);
}
