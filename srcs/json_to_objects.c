/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:32:22 by jbouille          #+#    #+#             */
/*   Updated: 2018/03/20 19:27:27 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include <rt_objects.h>
#include <stddef.h>
#include <libft.h>


//FOR PRINTF
#include <stdio.h>

size_t	jobject_len(t_jobject *obj)
{
	size_t		size;
	t_jobject	*tmp;

	tmp = obj;
	size = 0;
	while (tmp)
	{
		++size;
		tmp = tmp->next;
	}
	return (size);
}

size_t	jarray_len(t_jarray *array)
{
	size_t		size;
	t_jarray	*tmp;

	tmp = array;
	size = 0;
	while (tmp)
	{
		++size;
		tmp = tmp->next;
	}
	return (size);
}

int	is_type(void* value, t_jtype jtype, t_rt_type type, t_rt_type subtype);

int	jobject_contains(t_jobject *obj, t_key key)
{
	t_jobject	*tmp;

	tmp = obj;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key.key))
			return (is_type(tmp->value, tmp->type, key.type, key.content_type));
		tmp = tmp->next;
	}
	return (0);
}

const char	*get_string_value(t_jobject *obj, const char *key)
{
	t_jobject	*tmp;

	tmp = obj;
	while (tmp)
	{
		if (obj->type == JSTRING && ft_strequ(tmp->key, key))
			return ((const char*)(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_object(t_jobject *obj, const t_key *keys, const size_t keys_size, int is_common);

int	is_rt_object(t_jobject *obj)
{
	const char		*rt_type = get_string_value(obj, RT_OBJECT_TYPE);
	const size_t	nb_obj = RT_KEYS_SIZE(g_objects);
	size_t			i;

	printf("rt_type_key: %s\n", rt_type);
	i = 0;
	while (i < nb_obj)
	{
//		printf("is_rt_objects: %zu\n", g_objects[i].size);
		if (ft_strequ(g_objects[i].name, rt_type))
			return (is_object(obj, g_objects[i].key, g_objects[i].size, 1));
		++i;
	}
	return (0);
}

int	check_subtypes(t_jarray *array, t_rt_type subtype);

int	is_type(void* value, t_jtype jtype, t_rt_type type, t_rt_type subtype)
{
	if (type == RTNULL)
		return (jtype == JNULL);
	else if (type == RTSTRING)
		return (jtype == JSTRING);
	else if (type == RTDOUBLE)
		return (jtype == JDOUBLE || jtype == JINT);
	else if (type == RTUDOUBLE)
		return ((jtype == JINT && *((int*)value) >= 0) || (jtype == JDOUBLE && *((double*)value) >= 0.0));
	else if (type == RTCHAR)
		return (jtype == JINT && *((int*)value) >= 0 && *((int*)value) <= 255);
	else if (type == RTINT)
		return (jtype == JINT);
	else if (type == RTARRAY)
		return (jtype == JARRAY && check_subtypes((t_jarray*)value, subtype));
	else if (type == RTCAMERA)
		return (jtype == JOBJECT
				&& is_object((t_jobject*)value, g_camera_keys, RT_KEYS_SIZE(g_camera_keys), 0));
	else if (type == RTLIGHT)
		return (jtype == JOBJECT
				&& is_object((t_jobject*)value, g_light_keys, RT_KEYS_SIZE(g_light_keys), 0));
	else if (type == RTOBJECT)
		return (jtype == JOBJECT && is_rt_object((t_jobject*)value));
	else if (type == RTVECTOR)
		return (jtype == JARRAY && jarray_len((t_jarray*)value) == 3
		&& check_subtypes((t_jarray*)value, subtype));
	else if (type == RTCOEF)
		return ((jtype == JINT && *((int*)value) >= 0 && *((int*)value) <= 1)
				|| (jtype == JDOUBLE && *((double*)value) >= 0.0 && *((double*)value) <= 1.0));
	else if (type == RTANGLE)
		return ((jtype == JINT && *((int*)value) >= 0 && *((int*)value) < 90)
				|| (jtype == JDOUBLE && *((double*)value) >= 0.0 && *((double*)value) < 90.0));
	else if (type == RTTEXTURE)
		return (jtype == JOBJECT
				&& is_object((t_jobject*)value, g_texture_keys, RT_KEYS_SIZE(g_texture_keys), 0));
	else if (type == RTN)
		return ((jtype == JINT && *((int*)value) >= 1)
				|| (jtype == JDOUBLE && *((double*)value) >= 1.0));
	else if (type == RTCUSTOM)
		return (jtype == JOBJECT
				&& is_object((t_jobject*)value, g_custom_keys, RT_KEYS_SIZE(g_custom_keys), 0));
	else if (type == RTCUSTOMOBJ)
		return (jtype == JOBJECT
				&& is_object((t_jobject*)value, g_customobj_keys, RT_KEYS_SIZE(g_customobj_keys), 0));
	else if (type == RTSIGN)
		return (jtype == JSTRING && ft_strlen((char*)value) == 1 && (((char*)value)[0] == '-' || ((char*)value)[0] == '+'));
	else if (type == RTLIMIT)
		return (jtype == JOBJECT
				&& is_object((t_jobject*)value, g_plan_keys, RT_KEYS_SIZE(g_plan_keys), 0));
	return (0);
}

int	check_subtypes(t_jarray *array, t_rt_type subtype)
{
	t_jarray	*tmp;

	tmp = array;
	while (tmp)
	{
		if (subtype == RTOBJECT)
			printf("OBJECT ---------->\n");
//		printf("check_subtypes: %d\n", tmp->type);
		if (is_type(tmp->value, tmp->type, subtype, subtype) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	is_object(t_jobject *obj, const t_key *keys, const size_t keys_size, int is_common)
{
	size_t	common_size;
	size_t	i;

	if (is_common)
		common_size = RT_KEYS_SIZE(g_common_keys);
	else
		common_size = 0;
	if (keys_size + common_size != jobject_len(obj))
		return (0);
	i = 0;
	while (i < keys_size)
	{
		printf("is_object: %zu %s %d %d\n", i, keys[i].key, obj->type, keys[i].type);
		if (jobject_contains(obj, keys[i]) == 0)
			return (0);
		++i;
	}
	i = 0;
	while (i < common_size)
	{
		printf("is_object: %zu %s %d %d\n", i, g_common_keys[i].key, obj->type, g_common_keys[i].type);
		if (jobject_contains(obj, g_common_keys[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}

#include <objects_storage.h>
int	json_to_objects(t_jobject *obj, t_param *param)
{
	if (is_object(obj, g_main_object_keys, RT_KEYS_SIZE(g_main_object_keys), 0) == 0)
		return (0);
//	printf("obj_size: %zu\n", jobject_len(((t_jarray*)((t_jobject*)(obj->value))->value)->value));//DEBUG
	if (camera_storage(obj, param) == 0)
		return (0);
	vec_to_unit_norm(vector_product(param->align, param->look, param->third));
	param->customs = customs_storage(obj, param);
	param->lights = lights_storage(obj);
	param->objects = objects_storage(obj, param);
	//ATTENTION AUX RETOURS
	display_lights(param);
	display_objects(param);	
//	if (!(objects_storage(obj, param)))
//		return (0);
	return (1);
}
