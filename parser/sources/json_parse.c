/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:04:36 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/26 01:08:37 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include <parse_key_value.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

char		*parse_jobject(char *json, void **value)
{
	t_jobject	*obj;

	if (json == NULL)
		return (NULL);
	obj = NULL;
	if (ft_strlen(json) >= 2)
	{
		if ((obj = (t_jobject*)malloc(sizeof(t_jobject))) == NULL)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
		if (json[0] != '{')
			return (NULL);//ERROR
		if (json[1] != '}')
			json = parse_key_value(json + 1, &obj);
		else
			json = json + 1;
		if (json == NULL || (json && json[0] != '}'))
			return (NULL);
	}
	*value = obj;
	return (json + 1);//ERROR
}

static char	*parse_jarray_value(char *json, t_jarray **array)
{
	if (json == NULL)
		return (NULL);
	if ((*array = (t_jarray*)malloc(sizeof(t_jarray))) == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	(*array)->next = NULL;
	(*array)->value = NULL;
	json = get_value(json, &((*array)->type), &((*array)->value));
	printf("array_value: %d\n", *(int*)((*array)->value));
	if (json && json[0] == ',' && json[1] != ']')
		json = parse_jarray_value(json + 1, &((*array)->next));
	return (json);
}

char		*parse_jarray(char *json, void **value)
{
	t_jarray	*array;

	array = NULL;
	if (json == NULL)
		return (NULL);
	if (json[0] != '[')
		return (NULL);//ERROR
	if (json[1] != ']')
		json = parse_jarray_value(json + 1, &array);
	else
		json = json + 1;
	*value = array;
	if (json == NULL)
		return (NULL);
	if (json && json[0] != ']')
		return (NULL);//ERROR
	return (json + 1);
}

int			json_parse(char *json, t_jobject **obj)
{
	if (json && ft_strlen(json) >= 2)
	{
		if (json[0] != '{')
			return (EXIT_FAILURE);//ERROR
		json = parse_key_value(json + 1, obj);
		if (json == NULL || (json && (ft_strlen(json) != 1 || json[0] != '}')))
			return (EXIT_FAILURE);//ERROR
	}
	return (EXIT_SUCCESS);
}
