/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 15:03:27 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/23 14:51:30 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	limiter(char const *s, int *i, int *j, int *k)
{
	(*i) = 0;
	(*j) = 0;
	if (s != NULL)
	{
		while ((s[*i] == ' ' || s[*i] == '\n' || s[*i] == '\t') &&
				s[*i] != '\0')
			(*i)++;
		while (s[*j] != '\0')
			(*j)++;
		if ((*j) != 0)
		{
			(*j)--;
			while ((*j) > 0 && (s[*j] == ' ' || s[*j] == '\n' || s[*j] == '\t'))
				(*j)--;
		}
	}
	*k = *i;
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	limiter(s, &i, &j, &k);
	if (s == NULL)
		return (NULL);
	if (j == 0)
	{
		if (!(str = (char*)malloc(sizeof(char) * 1)))
			return (NULL);
	}
	else
	{
		if (!(str = (char*)malloc(sizeof(char) * (j - i + 2))))
			return (NULL);
		while (i < j + 1)
		{
			str[i - k] = s[i];
			i++;
		}
	}
	str[i - k] = '\0';
	return (str);
}
