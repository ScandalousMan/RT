/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:40:48 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/27 17:11:12 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <json_parse.h>
#include <rt.h>
int	json_to_objects(t_jobject *obj, t_param* param);
#include <file.h>

#define MY_GLOBALS
#include <rt_objects.h>
t_param *rt_parser(t_param *param)
{
	char		*json;
	t_jobject	*obj;
	int			ret;

	if (!(json = read_file("../rtv1.json")))
		return (param);
//		return (EXIT_FAILURE);
	obj = NULL;
	ret = json_parse(json, &obj);
	free(json);
	if (!ret)
		printf("json_to_objects: %d\n", json_to_objects(obj, param));
	return (param);
}
