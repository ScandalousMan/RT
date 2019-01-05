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

int		fill_light(t_light *light, t_jobject *jobj, int num)
{
	t_jobject	*tmp;

	light->num = num;
	tmp = get_jobject(jobj, "type");
	if (ft_strequ((char*)tmp->value, "spot"))
		light->type = RTSPOT;
	else if (ft_strequ((char*)tmp->value, "parallel"))
		light->type = RTPARALLEL;
	tmp = get_jobject(jobj, "color");
	light->col = get_color((t_jarray*)(tmp->value));
	fill_vector(&(light->src), (t_jarray*)(get_jobject(jobj, "u")->value));
	tmp = get_jobject(jobj, "intensity");
	light->i = get_double(tmp->type, tmp->value);
	return (1);
}

t_light	*get_light(t_jarray *array, int num)
{
	t_light	*new;

	if (array == NULL)
		return (NULL);
	if (!(new = (t_light*)malloc(sizeof(t_light))))
		return (NULL);
	if (fill_light(new, array->value, num) == 0)
		return (NULL);
	new->next = get_light(array->next, num + 1);
	return (new);
}
