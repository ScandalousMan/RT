/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:55:04 by jbouille          #+#    #+#             */
/*   Updated: 2018/04/14 17:21:15 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <parse_key_value.h>

/*
**	Pas de gestion de \u ...
*/

static void	comp_escape_chars(char *s, int i)
{
	if (s[i + 1] == '"')
		s[i] = '"';
	else if (s[i + 1] == '\\')
		s[i] = '\\';
	else if (s[i + 1] == '/')
		s[i] = '/';
	else if (s[i + 1] == 'b')
		s[i] = '\b';
	else if (s[i + 1] == 'f')
		s[i] = '\f';
	else if (s[i + 1] == 'n')
		s[i] = '\n';
	else if (s[i + 1] == 'r')
		s[i] = '\r';
	else if (s[i + 1] == 't')
		s[i] = '\t';
}

char		*escape_chars(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && (s[i + 1] == '"' || s[i + 1] == '\\'
			|| s[i + 1] == '/' || s[i + 1] == 'b' || s[i + 1] == 'f'
			|| s[i + 1] == 'n' || s[i + 1] == 'r' || s[i + 1] == 't'))
		{
			comp_escape_chars(s, i);
			ft_memmove(s + i + 1, s + i + 2, ft_strlen(s + i + 2) + 1);
		}
		else if (s[i] == '\\')
		{
			ft_memmove(s + i, s + i + 1, ft_strlen(s + i + 1) + 1);
			--i;
		}
		++i;
	}
	return (s);
}

char		*parse_jstring(char *json, void **value)
{
	int		i;
	char	tmp;

	i = 1;
	if (json != NULL && json[0] && json[i] != '\0')
	{
		while (json[i] != '\0')
		{
			if (json[i] == '\\' && json[i + 1] == '"')
				++i;
			else if (json[i] == '"')
			{
				tmp = json[i];
				json[i] = '\0';
				*value = extract_string(json + 1);
				json[i] = tmp;
				*value = escape_chars(*value);
				return (json + i + 1);
			}
			++i;
		}
	}
	return (NULL);
}

char		*parse_jbool(char *json, void **value)
{
	t_jbool	*b;

	if (ft_strnequ("true", json, 4) || ft_strnequ("false", json, 5))
	{
		if ((b = (t_jbool*)malloc(sizeof(t_jbool))) == NULL)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
		if (ft_strnequ("true", json, 4))
		{
			*b = JTRUE;
			*value = b;
			return (json + 4);
		}
		if (ft_strnequ("false", json, 5))
		{
			*b = JFALSE;
			*value = b;
			return (json + 5);
		}
	}
	return (NULL);
}

char		*parse_jnull(char *json, void **value)
{
	if (ft_strnequ("null", json, 4))
	{
		*value = NULL;
		return (json + 4);
	}
	return (NULL);
}
