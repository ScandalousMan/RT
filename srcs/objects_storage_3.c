/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_storage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:43:31 by jbouille          #+#    #+#             */
/*   Updated: 2018/12/04 17:56:23 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects_storage.h>
#include <rt_objects.h>
#include <libft.h>
#include <stdlib.h>
#include <stdint.h>

int				fill_custom_obj(t_custom_obj *custom_obj, t_jobject *jobj,
	t_param *param)
{
	t_jobject	*tmp;
	
	tmp = get_jobject(jobj, "intersection");
	custom_obj->op = ((char*)(tmp->value))[0];
	printf("OP: %c\n", custom_obj->op);
	tmp = get_jobject(jobj, "object");
	if (!(custom_obj->object = (t_object*)malloc(sizeof(t_object))))
		return (0);
	return (fill_object(custom_obj->object, tmp->value, 1, param));
}

t_custom_obj	*get_custom_obj(t_jarray *array, t_param *param,
	t_custom_obj *custom_obj)
{
	if (array == NULL || custom_obj == NULL)
		return (NULL);
	if (!(custom_obj = (t_custom_obj*)malloc(sizeof(t_custom_obj))))
		return (NULL);
	if (fill_custom_obj(custom_obj, array->value, param) == 0)
		return (NULL);
	custom_obj->next = get_custom_obj(array->next, param, custom_obj->next);
	return (custom_obj);
}

int				camera_storage(t_jobject *obj, t_param *param)
{
	t_jobject	*tmp;

	tmp = get_jobject(obj, CAMERA_KEY)->value;
	fill_vector(&(param->eye), (t_jarray*)(get_jobject(tmp, "eye")->value));
	fill_vector(&(param->look), (t_jarray*)(get_jobject(tmp, "look")->value));
	fill_vector(&(param->align), (t_jarray*)(get_jobject(tmp, "align")->value));
	return (1);
}

t_light			*lights_storage(t_jobject *obj)
{
	return (get_light(get_jobject(obj, LIGHTS_KEY)->value, 1));
}

t_object		*objects_storage(t_jobject *obj, t_param *param)
{
	return (get_object(get_jobject(obj, OBJECTS_KEY)->value, 1, param));
}
