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

void			fill_quadric_params(t_jobject *jobj, t_quadric *obj)
{
	t_jobject		*tmp;

	fill_vector(&(obj->center),
		(t_jarray*)(get_jobject(jobj, "center")->value));
	tmp = get_jobject(jobj, "a");
	obj->a = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "b");
	obj->b = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "c");
	obj->c = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "d");
	obj->d = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "e");
	obj->e = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "f");
	obj->f = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "g");
	obj->g = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "h");
	obj->h = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "i");
	obj->i = get_double(tmp->type, tmp->value);
	tmp = get_jobject(jobj, "r");
	obj->r = get_double(tmp->type, tmp->value);
}

void			*fill_quadric(t_jobject *jobj, t_object *q_obj)
{
	t_quadric		*obj;
	double			tr[VEC_SIZE];

	tr[0] = 0.0;
	tr[1] = 0.0;
	tr[2] = 0.0;
	if (!(obj = (t_quadric *)malloc(sizeof(t_quadric))))
		return (NULL);
	if (!(q_obj->dim = (void*)malloc(sizeof(t_quadric))))
		return (NULL);
	q_obj->parsed = obj;
	fill_quadric_params(jobj, obj);
	fill_moves(jobj, q_obj);
	return (obj);
}

t_object_def	fill_object_init(t_jobject *jobj, t_object *obj, t_param *param,
	int num)
{
	t_object_def	obj_def;

	obj_def = get_object_def_by_name(get_jobject(jobj, RT_OBJECT_TYPE)->value);
	obj->next = NULL;
	obj->type = obj_def.type;
	obj->num = num;
	obj->tmp_vec[0] = 0;
	obj->tmp_vec[1] = 0;
	obj->tmp_vec[2] = 0;
	obj->phong = param->macro.specular_exp;
	obj->effects.color = RT_C_NONE;
	obj->effects.normal = RT_N_NONE;
	if (obj_def.fill)
		obj_def.fill(jobj, obj);
	else
		obj->parsed = NULL;
	return (obj_def);
}

int				fill_object(t_object *obj, t_jobject *jobj, int num,
	t_param *param)
{
	t_object_def	obj_def;
	t_jobject		*tmp;

	obj_def = fill_object_init(jobj, obj, param, num);
	tmp = get_jobject(jobj, "color");
	obj->col = get_color((t_jarray*)(tmp->value));
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
	tmp = get_jobject(jobj, "limits");
	obj->limits = get_limits(tmp->value);
	tmp = get_jobject(jobj, "texture");
	return (1);
}
