/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:07:42 by jbouille          #+#    #+#             */
/*   Updated: 2018/03/20 18:48:01 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

static void	init_stringify(int *in_str, int *i, size_t *c)
{
	*in_str = 0;
	*i = 0;
	*c = 0;
}

char		*stringify(char *s)
{
	int		i;
	size_t	c;
	int		in_str;

	if (s == NULL)
		return (NULL);
	init_stringify(&in_str, &i, &c);
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] == '"')
			++i;
		else if (ft_isspace(s[i]) && in_str == 0)
			++c;
		else
		{
			ft_memmove(s + i - c, s + i, ft_strlen(s + i) + 1);
			i -= c;
			c = 0;
			if (s[i] == '"')
				in_str = (in_str + 1) % 2;
		}
		++i;
	}
	s[i - c] = '\0';
	return (s);
}
