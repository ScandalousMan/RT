/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_storage_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:43:31 by jbouille          #+#    #+#             */
/*   Updated: 2019/01/12 15:56:25 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects_storage.h>
#include <rt_objects.h>
#include <libft.h>
#include <stdlib.h>
#include <stdint.h>

t_jobject	*get_limit_obj(t_jarray *tmp, t_limit *new)
{
	t_jobject	*obj;

	obj = get_jobject(tmp->value, "normal");
	fill_vector(&new->plane.n, obj->value);
	obj = get_jobject(tmp->value, "point");
	fill_vector(&new->plane.ref, obj->value);
	vec_to_unit_norm(new->plane.n);
	obj = get_jobject(tmp->value, "type");
	if (ft_strequ(obj->value, "absolute"))
		new->type = RT_C_ABSOLUTE;
	else
		new->type = RT_C_RELATIVE;
	return (obj);
}

t_limit		*get_limits(t_jarray *array)
{
	t_limit		*limits;
	t_limit		*new;
	t_jarray	*tmp;
	t_jobject	*obj;

	limits = NULL;
	tmp = array;
	while (tmp)
	{
		if (!(new = (t_limit*)malloc(sizeof(t_limit))))
			return (NULL);
		obj = get_limit_obj(tmp, new);
		new->next = limits;
		limits = new;
		tmp = tmp->next;
	}
	return (limits);
}

void		fill_vector(double vector[1][VEC_SIZE], t_jarray *array)
{
	int			i;
	t_jarray	*tmp;

	if (array == NULL)
		return ;
	tmp = array;
	i = 0;
	while (i < VEC_SIZE && tmp)
	{
		vector[0][i] = get_double(tmp->type, tmp->value);
		tmp = tmp->next;
		++i;
	}
}

void		fill_moves(t_jobject *jobj, t_object *obj)
{
	double		tr[VEC_SIZE];

	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "translation")->value));
	vec_copy(tr, obj->translation);
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "rotation")->value));
	vec_copy(tr, obj->rotation);
}

t_object	*get_object(t_jarray *array, int num, t_param *param)
{
	t_object	*new;

	if (array == NULL)
		return (NULL);
	if (!(new = (t_object*)malloc(sizeof(t_object))))
		return (NULL);
	if (fill_object(new, array->value, num) == 0)
		return (NULL);
	param->num_objects++;
	if (param->num_objects >= 256)
	{
		ft_putendl_fd("Warning: 256 objects maximum.", STDERR_FILENO);
		return (new);
	}
	new->next = get_object(array->next, num + 1, param);
	return (new);
}
