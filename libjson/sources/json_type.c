/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:40:09 by jbouille          #+#    #+#             */
/*   Updated: 2018/03/20 19:05:37 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include <libft.h>

int		ft_isjint(char *json)
{
	int	i;

	i = 0;
	while (json && json[i] != '\0' && json[i] != ','
			&& json[i] != ']' && json[i] != '}')
	{
		if (i == 0 && json[i] == '-')
			;
		else if (ft_isdigit(json[i]) == 0)
			return (0);
		++i;
	}
	if (json && i == 1 && json[0] == '-')
		return (0);
	return (i);
}

int		ft_isjdouble(char *j)
{
	int	i;

	i = 0;
	while (j && j[i] != '\0' && j[i] != '.'
			&& j[i] != ',' && j[i] != ']' && j[i] != '}')
	{
		if (i == 0 && j[i] == '-')
			;
		else if (ft_isdigit(j[i]) == 0)
			return (0);
		++i;
	}
	if (j && i == 1 && j[0] == '-')
		return (0);
	if (j && j[i] == '.')
	{
		++i;
		while (j && j[i] != '\0' && j[i] != ',' && j[i] != ']' && j[i] != '}')
		{
			if (ft_isdigit(j[i]) == 0)
				return (0);
			++i;
		}
	}
	return (i);
}

t_jtype	get_type(char *json)
{
	if (json)
	{
		if (json[0] == '"')
			return (JSTRING);
		else if (json[0] == '[')
			return (JARRAY);
		else if (json[0] == '{')
			return (JOBJECT);
		else if (ft_isjint(json) > 0)
			return (JINT);
		else if (ft_isjdouble(json) > 0)
			return (JDOUBLE);
		else if (ft_strnequ("true", json, 4)
			|| ft_strnequ("false", json, 5))
			return (JBOOL);
		else if (ft_strnequ("null", json, 4))
			return (JNULL);
	}
	return (JUNKNOWN);
}
