/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_key_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:28:41 by jbouille          #+#    #+#             */
/*   Updated: 2018/03/20 18:55:20 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include <json_type.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <parse_number.h>
#include <parse_string.h>
#include <parse_array_object.h>

const t_func_type		g_func_parse[] = {
	{JSTRING, &parse_jstring},
	{JOBJECT, &parse_jobject},
	{JARRAY, &parse_jarray},
	{JINT, &parse_jint},
	{JDOUBLE, &parse_jdouble},
	{JBOOL, &parse_jbool},
	{JNULL, &parse_jnull}
};

char					*extract_string(char *s)
{
	char	*str;

	if ((str = ft_strdup(s)) == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	return (str);
}

char					*get_key(char *json, t_jstring *key)
{
	char	tmp;
	int		i;

	i = 0;
	if (json != NULL && json[i] == '"')
	{
		++i;
		while (json[i])
		{
			if (json[i] == '\\' && json[i + 1] == '"')
				++i;
			else if (json[i] == '"')
			{
				tmp = json[i];
				json[i] = '\0';
				*key = extract_string(json + 1);
				json[i] = tmp;
				*key = escape_chars(*key);
				return (json + i + 1);
			}
			++i;
		}
	}
	return (NULL);
}

void					debug(char *json, t_jtype *type, void **value)
{
	if (*value)
	{
		if (*type == JSTRING)
			printf("%p\n", *value);
		else if (*type == JINT)
			printf("%i\n", (int)(((int*)(*value))[0]));
		else if (*type == JDOUBLE)
			printf("%f\n", (double)(((double*)(*value))[0]));
		else if (*type == JBOOL)
			printf("%d\n", (t_jbool)(((t_jbool*)(*value))[0]));
		else if (*type == JNULL)
			printf("%p\n", *value);
	}
	printf("%s\n", json);
}

char					*get_value(char *json, t_jtype *type, void **value)
{
	size_t	i;

	if (json == NULL)
		return (NULL);
	*type = get_type(json);
	if (*type == JUNKNOWN)
		return (NULL);
	i = 0;
	while (i < sizeof(g_func_parse) / sizeof(t_func_type))
	{
		if (g_func_parse[i].type == *type)
		{
			json = (g_func_parse[i].f)(json, value);
			// printf("get_value: %s\n", json);//todo delete
			break ;
		}
		++i;
	}
	// debug(json, type, value);//todo delete
	return (json);
}

char					*parse_key_value(char *json, t_jobject **obj)
{
	if (json == NULL)
		return (NULL);
	if ((*obj = (t_jobject*)malloc(sizeof(t_jobject))) == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	(*obj)->next = NULL;
	(*obj)->value = NULL;
	json = get_key(json, &((*obj)->key));
	// printf("%s\n", (char*)((*obj)->key));
	if (json && json[0] == ':')
	{
		json = get_value(json + 1, &((*obj)->type), &((*obj)->value));
		if (json == NULL)
			return (NULL);
		if (json && json[0] == ',')
			json = parse_key_value(json + 1, &((*obj)->next));
	}
	else
		return (NULL);//error
	return (json);
}
