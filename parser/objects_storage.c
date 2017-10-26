/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_storage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:43:31 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/26 20:23:58 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects_storage.h>
#include <rt_objects.h>
#include <libft.h>
#include <stdlib.h>

t_jobject	*get_jobject(t_jobject *obj, const char *key)
{
	t_jobject	*tmp;

	int i = 0;
	tmp = obj;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
		++i;
	}
	return (NULL);//EXIT error dans le check des objets
}

const	t_object_def	get_object_def_by_name(const char *name)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_objects) / sizeof(t_object_def))
	{
		if (ft_strequ(name, g_objects[i].name))
			return (g_objects[i]);
		++i;
	}
	return (g_objects[0]);//EXIT big fail -> segfault direct
}

double	get_double(t_jtype type, void *value)
{
	return ((type == JINT) ?
			(double)(*(int*)(value)) : (double)(*((double*)value)));
}

void	fill_vector(double vector[1][VEC_SIZE], t_jarray *array)
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

void	*fill_sphere(t_jobject *jobj)
{
	t_sphere	*obj;
	t_jobject	*tmp;

	if (!(obj = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);//EXIT
	fill_vector((&(obj->center)), (t_jarray*)(get_jobject(jobj, "center")->value));
	tmp = get_jobject(jobj, "radius");
	obj->radius = get_double(tmp->type, tmp->value);
	return (obj);
}

void	*fill_plane(t_jobject *jobj)
{
	t_plane	*obj;

	if (!(obj = (t_plane *)malloc(sizeof(t_plane))))
		return (NULL);//EXIT
	fill_vector((&(obj->n)), (t_jarray*)(get_jobject(jobj, "normal")->value));
	fill_vector((&(obj->ref)), (t_jarray*)(get_jobject(jobj, "point")->value));
	return (obj);
}

void	*fill_cone(t_jobject *jobj)
{
	t_cone		*obj;
	t_jobject	*tmp;

	if (!(obj = (t_cone *)malloc(sizeof(t_cone))))
		return (NULL);//EXIT
	fill_vector(&(obj->org), (t_jarray*)(get_jobject(jobj, "center")->value));
	fill_vector(&(obj->u), (t_jarray*)(get_jobject(jobj, "vector")->value));
	tmp = get_jobject(jobj, "angle");
	obj->angle = get_double(tmp->type, tmp->value);
	return (obj);
}

void	*fill_cylinder(t_jobject *jobj)
{
	t_cylindre	*obj;
	t_jobject	*tmp;

	if (!(obj = (t_cylindre *)malloc(sizeof(t_cylindre))))
		return (NULL);//EXIT
	fill_vector(&(obj->org), (t_jarray*)(get_jobject(jobj, "center")->value));
	fill_vector(&(obj->u), (t_jarray*)(get_jobject(jobj, "vector")->value));
	tmp = get_jobject(jobj, "radius");
	obj->radius = get_double(tmp->type, tmp->value);
	return (obj);
}
#include <stdint.h>
int	fill_object(t_object *obj, t_jobject *jobj, int num)
{
	const t_object_def obj_def = get_object_def_by_name(get_jobject(jobj, RT_OBJECT_TYPE)->value);

	t_jobject	*tmp;
	obj->type = obj_def.type;
	obj->num = num;//REALLY NEED THAT ?
	obj->tmp_vec[0] = 0;//TODO CHANGE THIS BEURK !
	obj->tmp_vec[1] = 0;
	obj->tmp_vec[2] = 0;
	obj->phong = SPECULAR_EXP;//TODO
	tmp = get_jobject(jobj, "color");
//	obj->col = *(int*)(((t_jarray*)tmp->value)->value) << 2 * sizeof(uint8_t); //TODO
//	obj->col += *(int*)(((t_jarray*)tmp->value)->next->value) << 1 * sizeof(uint8_t); //TODO
//	obj->col += *(int*)(((t_jarray*)tmp->value)->next->next->value) << 0 * sizeof(uint8_t); //TODO
	tmp = get_jobject(jobj, "kd");
	obj->kd = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "ks");
	obj->ks = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "transparency");
	obj->transparency = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "reflection");
	obj->reflection = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "n");
	obj->index = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "thickness");
	obj->thickness = get_double(tmp->type, tmp->value);
	
	tmp = get_jobject(jobj, "texture");//JSON_OBJECT
//	obj->texture = ;//NOT EXISTS FOR THE MOMENT
	if (obj_def.fill)
		obj->dim = obj_def.fill(jobj);
	else
		obj->dim = NULL;//EXIT ??? pas forcement si l'object ne prends pas de param...
	return (1);
}

t_object	*get_object(t_jarray *array, int num)
{
	t_object	*new;

	if (array == NULL)
		return (NULL);
	if (!(new = (t_object*)malloc(sizeof(t_object))))
		return (NULL);//EXIT
	if (fill_object(new, array->value, num) == 0)
		return (NULL);
	new->next = get_object(array->next, num + 1);
	return (new);
}

t_object	*objects_storage(t_jobject *obj)
{
	return (get_object(get_jobject(obj, OBJECTS_KEY)->value, 1));
	return (NULL);
}
