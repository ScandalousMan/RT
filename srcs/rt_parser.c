/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:40:48 by jbouille          #+#    #+#             */
/*   Updated: 2019/01/12 15:32:27 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <json_parse.h>
#include <json_free.h>
#include <rt.h>
#include <file.h>

void	update_eye_n(t_param *param)
{
	t_object	*obj;

	obj = param->objects;
	while (obj)
	{
		if (is_inside_object(param->eye, obj, NULL))
			param->path->inside_obj = obj;
		obj = obj->next;
	}
}

int		rt_parser(t_param *param, char *file)
{
	char		*json;
	t_jobject	*obj;
	int			ret;

	if (!(json = read_file(file)))
		return (1);
	obj = NULL;
	ret = json_parse(json, &obj);
	free(json);
	if (!ret)
		json_to_objects(obj, param);
	update_eye_n(param);
	if (param->num_objects == 0)
		error(0, 0, "No objects found in scene");
	free_jobject(obj);
	return (0);
}
