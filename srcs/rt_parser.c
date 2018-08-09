/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:40:48 by jbouille          #+#    #+#             */
/*   Updated: 2018/08/06 16:03:55 by jbouille         ###   ########.fr       */
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
int	rt_parser(t_param *param, char *file)
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
	printf("num_objects: %i\n", param->num_objects);
	free_jobject(obj);
	free(file);
	return (1);
}
