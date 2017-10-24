/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:32:22 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/24 19:03:06 by jbouille         ###   ########.fr       */
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

int	jobject_contains(t_jobject *obj, const char *key)
{
	t_jobject	*tmp;

	tmp = obj;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	jobject_is_type(t_jobject *obj, t_rt_type type)
{
	if (type == RTNULL)
		return (obj->type == JNULL);
	else if (type == RTSTRING)
		return (obj->type == JSTRING);
	else if (type == RTDOUBLE)
		return (obj->type == JDOUBLE || obj->type == JINT);
	else if (type == RTCHAR)
		return (obj->type == JINT && *((int*)obj->value) >= 0 && *((int*)obj->value) <= 255);
	else if (type == RTINT)
		return (obj->type == JINT);
	else if (type == RTARRAY) // check_subtypes
		return (obj->type == JARRAY);
	else if (type == RTOBJECT)
		return (obj->type == JOBJECT); //check_subtypes
	else if (type == RTVECTOR)
		return (obj->type == JARRAY && jarray_len((t_jarray*)(obj->value)) == 3
				); // check_subtypes
	return (1);
}

int	is_object(t_jobject *obj, const t_key *keys, const size_t keys_size, int is_common)
{
	size_t	common_size;
	size_t	i;

	if (is_common)
		common_size = sizeof(g_common_keys) / sizeof(t_key);
	else
		common_size = 0;
	if (keys_size + common_size != jobject_len(obj))
		return (0);
	i = 0;
	while (i < keys_size)
	{
		if (jobject_contains(obj, keys[i].key) == 0)
			return (0);
		if (jobject_is_type(obj, keys[i].type) == 0)
			return (0);
		++i;
	}
	i = 0;
	while (i < common_size)
	{
		if (jobject_contains(obj, g_common_keys[i].key) == 0)
			return (0);
		if (jobject_is_type(obj, g_common_keys[i].type) == 0)
			return (0);
		++i;
	}
	return (1);
}

int	json_to_objects(t_jobject *obj)
{
	const size_t	size = sizeof(g_main_object_keys) / sizeof(t_key);
	if (is_object(obj, g_main_object_keys, size, 0) == 0)
		return (0);
	return (1);
}
