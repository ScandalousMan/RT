/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:40:48 by jbouille          #+#    #+#             */
/*   Updated: 2017/11/14 14:31:49 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <json_parse.h>
#include <json_free.h>
#include <rt.h>
int	json_to_objects(t_jobject *obj, t_param* param);
#include <file.h>

#define MY_GLOBALS
#include <rt_objects.h>
int	rt_parser(t_param *param, const char *file)
{
	char		*json;
	t_jobject	*obj;
	int			ret;

	if (!(json = read_file(file)))
		return (0);//error_msg
	obj = NULL;
	ret = json_parse(json, &obj);
	free(json);
	if (!ret)
		printf("json_to_objects: %d\n", json_to_objects(obj, param));
	/* introduire ici le nombre total d'objets dans la variable ret - balls.json */
	param->num_objects = 9;
	free_jobject(obj);
	return (1);
}
