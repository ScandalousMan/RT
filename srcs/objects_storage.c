/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_storage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:43:31 by jbouille          #+#    #+#             */
/*   Updated: 2017/11/14 18:30:56 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects_storage.h>
#include <rt_objects.h>
#include <libft.h>
#include <stdlib.h>

t_custom	*get_custom_ptr(char *name, t_custom *list)
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

int	get_color(t_jarray *array)
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

void	*fill_sphere(t_jobject *jobj, t_param *param)
{
	t_sphere	*obj;
	t_jobject	*tmp;
	double		tr[VEC_SIZE];

	if (!(obj = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);//EXIT
	fill_vector((&(obj->center)), (t_jarray*)(get_jobject(jobj, "center")->value));
	tmp = get_jobject(jobj, "radius");
	obj->radius = get_double(tmp->type, tmp->value);
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "translation")->value));
	obj->center[0] += tr[0];
	obj->center[1] += tr[1];
	obj->center[2] += tr[2];
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "rotation")->value));
	rotation_matrice(tr[0], tr[1], tr[2], param);
//	matrice_product(param->rot, obj->n, obj->n);
	return (obj);
}

void	*fill_plane(t_jobject *jobj, t_param *param)
{
	t_plane		*obj;
	double		tr[VEC_SIZE];

	if (!(obj = (t_plane *)malloc(sizeof(t_plane))))
		return (NULL);//EXIT
	fill_vector((&(obj->n)), (t_jarray*)(get_jobject(jobj, "normal")->value));
	fill_vector((&(obj->ref)), (t_jarray*)(get_jobject(jobj, "point")->value));
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "translation")->value));
	obj->ref[0] += tr[0];
	obj->ref[1] += tr[1];
	obj->ref[2] += tr[2];
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "rotation")->value));
	rotation_matrice(tr[0], tr[1], tr[2], param);
	matrice_product(param->rot, obj->n, obj->n);
	return (obj);
}

void	*fill_cone(t_jobject *jobj, t_param *param)
{
	t_cone		*obj;
	t_jobject	*tmp;
	double		tr[VEC_SIZE];

	if (!(obj = (t_cone *)malloc(sizeof(t_cone))))
		return (NULL);//EXIT
	fill_vector(&(obj->org), (t_jarray*)(get_jobject(jobj, "center")->value));
	fill_vector(&(obj->u), (t_jarray*)(get_jobject(jobj, "vector")->value));
	tmp = get_jobject(jobj, "angle");
	obj->angle =  M_PI / 180.0 * get_double(tmp->type, tmp->value);
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "translation")->value));
	obj->org[0] += tr[0];
	obj->org[1] += tr[1];
	obj->org[2] += tr[2];
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "rotation")->value));
	rotation_matrice(tr[0], tr[1], tr[2], param);
	matrice_product(param->rot, obj->u, obj->u);
	return (obj);
}

void	*fill_cylinder(t_jobject *jobj, t_param *param)
{
	t_cylindre	*obj;
	t_jobject	*tmp;
	double		tr[VEC_SIZE];

	if (!(obj = (t_cylindre *)malloc(sizeof(t_cylindre))))
		return (NULL);//EXIT
	fill_vector(&(obj->org), (t_jarray*)(get_jobject(jobj, "center")->value));
	fill_vector(&(obj->u), (t_jarray*)(get_jobject(jobj, "vector")->value));
	tmp = get_jobject(jobj, "radius");
	obj->radius = get_double(tmp->type, tmp->value);
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "translation")->value));
	obj->org[0] += tr[0];
	obj->org[1] += tr[1];
	obj->org[2] += tr[2];
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "rotation")->value));
	rotation_matrice(tr[0], tr[1], tr[2], param);
	matrice_product(param->rot, obj->u, obj->u);
	return (obj);
}

void	*fill_customobject(t_jobject *jobj, t_param *param)
{
	t_custom		*cust;
	t_custom_obj	*obj;
	t_jobject		*tmp;
	double			tr[VEC_SIZE];

	tmp = get_jobject(jobj, "name");
	if (!(cust = get_custom_ptr(tmp->value, param->customs)))
		return (NULL);//ERROR can't find this custom object
	obj = cust->objects;//COPY? TODO
	fill_vector(&(obj->org), (t_jarray*)(get_jobject(jobj, "center")->value));
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "translation")->value));
	obj->org[0] += tr[0];
	obj->org[1] += tr[1];
	obj->org[2] += tr[2];
	fill_vector(&tr, (t_jarray*)(get_jobject(jobj, "rotation")->value));
	rotation_matrice(tr[0], tr[1], tr[2], param);
	matrice_product(param->rot, obj->u, obj->u);
	return (obj);
}

#include <stdint.h>
int	fill_object(t_object *obj, t_jobject *jobj, int num, t_param *param)
{
	const t_object_def obj_def = get_object_def_by_name(get_jobject(jobj, RT_OBJECT_TYPE)->value);

	t_jobject	*tmp;

	obj->next = NULL;
	obj->type = obj_def.type;
	obj->num = num;//REALLY NEED THAT ?
	obj->tmp_vec[0] = 0;//TODO CHANGE THIS BEURK !
	obj->tmp_vec[1] = 0;
	obj->tmp_vec[2] = 0;
	obj->phong = SPECULAR_EXP;//TODO
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
	
	tmp = get_jobject(jobj, "texture");//JSON_OBJECT
//	obj->texture = ;//NOT EXISTS FOR THE MOMENT
	if (obj_def.fill)
		obj->dim = obj_def.fill(jobj, param);
	else
		obj->dim = NULL;//EXIT ??? pas forcement si l'object ne prends pas de param...
	return (1);
}

t_object	*get_object(t_jarray *array, int num, t_param *param)
{
	t_object	*new;

	if (array == NULL)
		return (NULL);
	if (!(new = (t_object*)malloc(sizeof(t_object))))
		return (NULL);//EXIT
	if (fill_object(new, array->value, num, param) == 0)
		return (NULL);
	new->next = get_object(array->next, num + 1, param);
	return (new);
}

int	fill_light(t_light *light, t_jobject *jobj, int num)
{
	t_jobject	*tmp;

	light->num = num;
	tmp = get_jobject(jobj, "color");
	light->col = get_color((t_jarray*)(tmp->value));
	fill_vector(&(light->src), (t_jarray*)(get_jobject(jobj, "center")->value));
	tmp = get_jobject(jobj, "intensity");
	light->i = get_double(tmp->type, tmp->value);
	return (1);
}

t_light		*get_light(t_jarray *array, int num)
{
	t_light	*new;

	if (array == NULL)
		return (NULL);
	if (!(new = (t_light*)malloc(sizeof(t_light))))
		return (NULL);//EXIT
	if (fill_light(new, array->value, num) == 0)
		return (NULL);
	new->next = get_light(array->next, num + 1);
	return (new);
}

int	fill_custom_obj(t_custom_obj *custom_obj, t_jobject *jobj, t_param *param)
{
	t_jobject	*tmp;
	
	tmp = get_jobject(jobj, "intersection");
	custom_obj->op = ((char*)(tmp->value))[0];
	printf("OP: %c\n", custom_obj->op);
	tmp = get_jobject(jobj, "object");
	if (!(custom_obj->object = (t_object*)malloc(sizeof(t_object))))
		return (0);
	return (fill_object(custom_obj->object, tmp->value, 1, param));
}

t_custom_obj	*get_custom_obj(t_jarray *array, t_param *param)
{
	t_custom_obj	*custom_obj;

	if (array == NULL)
		return (NULL);
	if (!(custom_obj = (t_custom_obj*)malloc(sizeof(t_custom_obj))))
		return (NULL);
	if (fill_custom_obj(custom_obj, array->value, param) == 0)
		return (NULL);
	custom_obj->next = get_custom_obj(array->next, param);
	return (custom_obj);
}

int	fill_custom(t_custom *custom, t_jobject *jobj, int num, t_param *param)
{
	t_jobject	*tmp;
	
	custom->id = num;
	tmp = get_jobject(jobj, "name");
	printf("TEST: %s\n", tmp->value);

	custom->name = ft_strdup(tmp->value);
	if (custom->name == NULL)
		return (0);
	tmp = get_jobject(jobj, "objects");
	custom->objects = get_custom_obj(tmp->value, param);
	return (1);
}

t_custom	*get_custom(t_jarray *array, int num, t_param *param)
{
	t_custom	*custom;

	if (array == NULL)
		return (NULL);
	if (!(custom = (t_custom*)malloc(sizeof(t_custom))))
		return (NULL);
	if (fill_custom(custom, array->value, num, param) == 0)
		return (NULL);
	custom->next = get_custom(array->next, num + 1, param);
	return (custom);
}

//TODO CAMERA

int			camera_storage(t_jobject *obj, t_param *param)
{
	t_jobject	*tmp;

	tmp = get_jobject(obj, CAMERA_KEY)->value;
	fill_vector(&(param->eye), (t_jarray*)(get_jobject(tmp, "eye")->value));
	fill_vector(&(param->look), (t_jarray*)(get_jobject(tmp, "look")->value));
	fill_vector(&(param->align), (t_jarray*)(get_jobject(tmp, "align")->value));
	return (1);
}

t_light		*lights_storage(t_jobject *obj)
{
	return (get_light(get_jobject(obj, LIGHTS_KEY)->value, 1));
}

t_object	*objects_storage(t_jobject *obj, t_param *param)
{
	return (get_object(get_jobject(obj, OBJECTS_KEY)->value, 1, param));
}

t_custom	*customs_storage(t_jobject *obj, t_param *param)
{
	return (get_custom(get_jobject(obj, CUSTOMS_KEY)->value, 1, param));
}
