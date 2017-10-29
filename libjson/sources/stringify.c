/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:07:42 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/29 18:16:54 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

char	*stringify(char *s)
{
	int		i;
	size_t	c;
	int		in_str;

	if (s == NULL)
		return (NULL);
	in_str = 0;
	i = 0;
	c = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] == '"')
			++i;
		else if (s[i] == '"')
		{
			ft_memmove(s + i - c, s + i, ft_strlen(s + i) + 1);
			i -= c;
			c = 0;
			in_str = (in_str + 1) % 2;
		}
		else if (ft_isspace(s[i]) && in_str == 0)
			c++;
		else
		{
			ft_memmove(s + i - c, s + i, ft_strlen(s + i) + 1);
			i -= c;
			c = 0;
		}
		++i;
	}
	s[i - c] = '\0';
	return (s);
}
