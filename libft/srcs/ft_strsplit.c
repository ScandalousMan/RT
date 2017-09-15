/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:51:19 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/23 17:16:32 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_w(char const *s, char c)
{
	int		flag;
	int		count;
	int		i;

	flag = 0;
	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		if (s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static void		tab_init(int **tab, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		(*tab)[i] = 1;
		i++;
	}
}

static int		*len_w(char const *s, char c, int count)
{
	int		*tab;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!(tab = (int*)malloc(sizeof(int) * count)))
		return (NULL);
	tab_init(&tab, count);
	count = -1;
	while (s[i] != '\0')
	{
		if (s[i] != c && flag == 1)
			(tab[count])++;
		else if (s[i] != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (tab);
}

static void		tab_filler(char ***out, char const *s, char c, int *tab)
{
	int		i[4];

	i[2] = 0;
	i[0] = -1;
	i[3] = 0;
	while (s[i[2]] != '\0')
	{
		if (s[i[2]] != c)
		{
			if (i[3] == 0)
			{
				i[3] = 1;
				i[0]++;
				i[1] = 0;
			}
			else
				i[1]++;
			(*out)[i[0]][i[1]] = s[i[2]];
			if (i[1] == tab[i[0]] - 1)
				(*out)[i[0]][i[1] + 1] = '\0';
		}
		else
			i[3] = 0;
		i[2]++;
	}
}

char			**ft_strsplit(char const *s, char c)
{
	char	**out;
	int		*tab;
	int		i;
	int		count;

	i = 0;
	if (s == NULL)
		return (NULL);
	count = count_w(s, c);
	if (!(tab = len_w(s, c, count)))
		return (NULL);
	if (!(out = (char**)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		if (!(out[i] = (char*)malloc(tab[i] + 1)))
			return (NULL);
		i++;
	}
	out[i] = NULL;
	tab_filler(&out, s, c, tab);
	return (out);
}
