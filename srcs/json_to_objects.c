/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:32:22 by jbouille          #+#    #+#             */
/*   Updated: 2018/12/04 17:59:14 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include <rt_objects.h>
#include <stddef.h>
#include <libft.h>
#include <objects_storage.h>

const char	*get_string_value(t_jobject *obj, const char *key)
{
	t_jobject		*tmp;

	tmp = obj;
	while (tmp)
	{
		if (obj->type == JSTRING && ft_strequ(tmp->key, key))
			return ((const char*)(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int			is_rt_object(t_jobject *obj)
{
	const char		*rt_type = get_string_value(obj, RT_OBJECT_TYPE);
	const size_t	nb_obj = RT_KEYS_SIZE(g_objects);
	size_t			i;

	i = 0;
	while (i < nb_obj)
	{
		if (ft_strequ(g_objects[i].name, rt_type))
			return (is_object(obj, g_objects[i].key, g_objects[i].size, 1));
		++i;
	}
	return (0);
}

int			check_subtypes(t_jarray *array, t_rt_type subtype)
{
	t_jarray		*tmp;

	tmp = array;
	while (tmp)
	{
		if (is_type(tmp->value, tmp->type, subtype, subtype) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int			is_object(t_jobject *obj, const t_key *keys, const size_t keys_size,
	int is_common)
{
	size_t			common_size;
	size_t			i;

	common_size = (is_common) ? RT_KEYS_SIZE(g_common_keys) : 0;
	if (keys_size + common_size != jobject_len(obj))
		return (0);
	i = 0;
	while (i < keys_size)
	{
		if (jobject_contains(obj, keys[i]) == 0)
			return (0);
		++i;
	}
	i = 0;
	while (i < common_size)
	{
		if (jobject_contains(obj, g_common_keys[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}

int	json_to_objects(t_jobject *obj, t_param *param)
{
	if (is_object(obj, g_main_object_keys,
		RT_KEYS_SIZE(g_main_object_keys), 0) == 0)
		return (0);
	if (camera_storage(obj, param) == 0)
		return (0);
	vec_to_unit_norm(vector_product(param->align, param->look, param->third));
	param->lights = lights_storage(obj);
	param->objects = objects_storage(obj, param);
	display_lights(param);
	return (1);
}
