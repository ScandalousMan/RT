/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:38:27 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/23 13:57:46 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	i = start;
	if (s == NULL)
		return (NULL);
	if ((str = (char*)malloc(sizeof(char) * (len + 1))))
	{
		while (i < start + len)
		{
			str[i - start] = s[i];
			i++;
		}
		str[i - start] = '\0';
		return (str);
	}
	else
		return (NULL);
}
