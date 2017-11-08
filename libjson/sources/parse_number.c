/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:49:27 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/26 00:54:40 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include <json_type.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

char	*parse_jint(char *json, void **value)
{
	char	tmp;
	size_t	size;
	t_jint	*number;

	if (json == NULL)
		return (NULL);
	if ((number = (t_jint*)malloc(sizeof(t_jint))) == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	size = ft_isjint(json);
	tmp = json[size];
	json[size] = '\0';
	*number = ft_atoi(json);
	*value = (void*)(number);
	json[size] = tmp;
	return (json + size);
}

char	*parse_jdouble(char *json, void **value)
{
	char		tmp;
	size_t		size;
	t_jdouble	*number;

	if (json == NULL)
		return (NULL);
	if ((number = (t_jdouble*)malloc(sizeof(t_jdouble))) == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	size = ft_isjdouble(json);
	tmp = json[size];
	json[size] = '\0';
	*number = ft_atod(json);
	*value = (void*)(number);
	json[size] = tmp;
	return (json + size);
}
