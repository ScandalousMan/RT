/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:46:29 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/23 14:08:50 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	filler(char const *s1, char const *s2, char **str)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		(*str)[i] = s1[i];
		i++;
	}
	j = i;
	while (s2[i - j] != '\0')
	{
		(*str)[i] = s2[i - j];
		i++;
	}
	(*str)[i] = '\0';
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	j = i;
	while (s2[i - j] != '\0')
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	filler(s1, s2, &str);
	return (str);
}
