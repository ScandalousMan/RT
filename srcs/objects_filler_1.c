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

void	*fill_sphere(t_jobject *jobj, t_object *s_obj)
{
	t_sphere	*obj;
	t_jobject	*tmp;
	double		tr[VEC_SIZE];

	tr[0] = 0.0;
	tr[1] = 0.0;
	tr[2] = 0.0;
	if (!(obj = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);
	if (!(s_obj->dim = (void*)malloc(sizeof(t_sphere))))
		return (NULL);
	s_obj->parsed = obj;
	fill_vector((&(obj->center)),
		(t_jarray*)(get_jobject(jobj, "center")->value));
	tmp = get_jobject(jobj, "radius");
	obj->radius = get_double(tmp->type, tmp->value);
	fill_moves(jobj, s_obj);
	return (obj);
}

void	*fill_plane(t_jobject *jobj, t_object *p_obj)
{
	t_plane		*obj;
	double		tr[VEC_SIZE];

	tr[0] = 0.0;
	tr[1] = 0.0;
	tr[2] = 0.0;
	if (!(obj = (t_plane *)malloc(sizeof(t_plane))))
		return (NULL);
	if (!(p_obj->dim = (void*)malloc(sizeof(t_plane))))
		return (NULL);
	p_obj->parsed = obj;
	fill_vector((&(obj->n)), (t_jarray*)(get_jobject(jobj, "normal")->value));
	fill_vector((&(obj->ref)), (t_jarray*)(get_jobject(jobj, "point")->value));
	vec_to_unit_norm(obj->n);
	fill_moves(jobj, p_obj);
	return (obj);
}

void	*fill_cone(t_jobject *jobj, t_object *c_obj)
{
	t_cone		*obj;
	t_jobject	*tmp;
	double		tr[VEC_SIZE];

	tr[0] = 0.0;
	tr[1] = 0.0;
	tr[2] = 0.0;
	if (!(obj = (t_cone *)malloc(sizeof(t_cone))))
		return (NULL);
	if (!(c_obj->dim = (void*)malloc(sizeof(t_cone))))
		return (NULL);
	c_obj->parsed = obj;
	fill_vector(&(obj->org), (t_jarray*)(get_jobject(jobj, "center")->value));
	fill_vector(&(obj->u), (t_jarray*)(get_jobject(jobj, "vector")->value));
	tmp = get_jobject(jobj, "angle");
	obj->angle =  M_PI / 180.0 * get_double(tmp->type, tmp->value);
	vec_to_unit_norm(obj->u);
	fill_moves(jobj, c_obj);
	return (obj);
}

void	*fill_cylinder(t_jobject *jobj, t_object *c_obj)
{
	t_cylindre	*obj;
	t_jobject	*tmp;
	double		tr[VEC_SIZE];

	tr[0] = 0.0;
	tr[1] = 0.0;
	tr[2] = 0.0;
	if (!(obj = (t_cylindre *)malloc(sizeof(t_cylindre))))
		return (NULL);
	if (!(c_obj->dim = (void*)malloc(sizeof(t_cylindre))))
		return (NULL);
	c_obj->parsed = obj;
	fill_vector(&(obj->org), (t_jarray*)(get_jobject(jobj, "center")->value));
	fill_vector(&(obj->u), (t_jarray*)(get_jobject(jobj, "vector")->value));
	tmp = get_jobject(jobj, "radius");
	obj->radius = get_double(tmp->type, tmp->value);
	vec_to_unit_norm(obj->u);
	fill_moves(jobj, c_obj);
	return (obj);
}

void	*fill_cube(t_jobject *jobj, t_object *c_obj)
{
	t_cube		*obj;
	t_jobject	*tmp;
	double		tr[VEC_SIZE];

	tr[0] = 0.0;
	tr[1] = 0.0;
	tr[2] = 0.0;
	if (!(obj = (t_cube*)malloc(sizeof(t_cube))))
		return (NULL);
	if (!(c_obj->dim = (void*)malloc(sizeof(t_cube))))
		return (NULL);
	c_obj->parsed = obj;
	fill_vector(&(obj->center), (t_jarray*)(get_jobject(jobj, "center")->value));
	tmp = get_jobject(jobj, "h");
	obj->h = get_double(tmp->type, tmp->value);
	fill_moves(jobj, c_obj);
	return (obj);
}

