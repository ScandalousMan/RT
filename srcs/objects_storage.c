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

t_custom		*get_custom_ptr(char *name, t_custom *list)
{
	t_custom	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strequ(name, tmp->name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int				get_color(t_jarray *array)
{
	int			rgb[VEC_SIZE];
	int			i;
	t_jarray	*tmp;

	i = 0;
	tmp = array;
	while (tmp && i < VEC_SIZE)
	{
		rgb[i] = *((int*)(tmp->value));
		++i;
		tmp = tmp->next;
	}
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

t_jobject		*get_jobject(t_jobject *obj, const char *key)
{
	t_jobject	*tmp;
	int			i;

	i = 0;
	tmp = obj;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
		++i;
	}
	return (NULL);
}

t_object_def	get_object_def_by_name(const char *name)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_objects) / sizeof(t_object_def))
	{
		if (ft_strequ(name, g_objects[i].name))
			return (g_objects[i]);
		++i;
	}
	return (g_objects[0]);
}

double			get_double(t_jtype type, void *value)
{
	return ((type == JINT) ?
			(double)(*(int*)(value)) : (double)(*((double*)value)));
}
