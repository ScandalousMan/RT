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

int		jobject_contains(t_jobject *obj, t_key key)
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
