/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:55:04 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/26 00:57:36 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

char	*parse_jstring(char *json, void **value)
{
	int	i;

	i = 1;
	if (json != NULL && json[i] != '\0')
	{
		++i;
		while (json[i])
		{
			if (json[i] == '"' && json[i - 1] != '\\')
			{
				json[i] = '\0';
				if ((*value = ft_strdup(json + 1)) == NULL)
				{
					perror(NULL);
					exit(EXIT_FAILURE);
				}
				return (json + i + 1) ;
			}
			++i;
		}
	}
	return (NULL);
}

char	*parse_jbool(char *json, void **value)
{
	t_jbool	*b;

	if (ft_strnequ("true", json, 4) || ft_strnequ("false", json, 5))
	{
		if ((b = (t_jbool*)malloc(sizeof(t_jbool))) == NULL)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	if (ft_strnequ("true", json, 4))
	{
		*b = TRUE;
		*value = b;
		return (json + 4);
	}
	if (ft_strnequ("false", json, 5))
	{
		*b = FALSE;
		*value = b;
		return (json + 5);
	}
	return (NULL);
}

char	*parse_jnull(char *json, void **value)
{
	if (ft_strnequ("null", json, 4))
	{
		*value = NULL;
		return (json + 4);
	}
	return (NULL);
}
