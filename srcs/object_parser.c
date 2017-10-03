#include "rt.h"

int 		rt_object_parser(t_param *param, t_parse *config)
{
	if (ft_atoi(config->next->str) == 1 &&
		(config->list_len == 9 || config->list_len == 12))
		return (rt_sphere_parser(param, config->next->next));
	else if (ft_atoi(config->next->str) == 2 &&
		(config->list_len == 11 || config->list_len == 17))
		return (rt_plane_parser(param, config->next->next));
	else if (ft_atoi(config->next->str) == 3 &&
		(config->list_len == 12 || config->list_len == 18))
		return (rt_cone_parser(param, config->next->next));
	else if (ft_atoi(config->next->str) == 4 &&
		(config->list_len == 12 || config->list_len == 18))
		return (rt_cylindre_parser(param, config->next->next));
	else if (ft_atoi(config->next->str) == 5 &&
		(config->list_len == 11 || config->list_len == 17))
		return (rt_ellipsoide_parser(param, config->next->next));
	return (0);
}

t_sphere	*duplicate_sphere(t_sphere *src)
{
	t_sphere	*copy;

	if (!(copy = (t_sphere*)malloc(sizeof(t_sphere))))
		return NULL;
	if (!(copy->center = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	vec_copy(src->center, copy->center);
	copy->radius = src->radius;
	return copy;
}

t_splane	*duplicate_plane(t_plane *src)
{
	t_plane	*copy;

	if (!(copy = (t_plane*)malloc(sizeof(t_plane))))
		return NULL;
	if (!(copy->n = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	if (!(copy->ref = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	vec_copy(src->n, copy->n);
	vec_copy(src->ref, copy->ref);
	return copy;
}

t_cone		*duplicate_cone(t_cone *src)
{
	t_cone	*copy;

	if (!(copy = (t_cone*)malloc(sizeof(t_cone))))
		return NULL;
	if (!(copy->org = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	if (!(copy->u = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	vec_copy(src->org, copy->org);
	vec_copy(src->u, copy->u);
	copy->angle = src->angle;
	return copy;
}

t_cylindre	*duplicate_cylindre(t_cylindre *src)
{
	t_cylindre	*copy;

	if (!(copy = (t_cylindre*)malloc(sizeof(t_cylindre))))
		return NULL;
	if (!(copy->org = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	if (!(copy->u = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	vec_copy(src->org, copy->org);
	vec_copy(src->u, copy->u);
	copy->radius = src->radius;
	return copy;
}

t_ellipsoide	*duplicate_ellipsoide(t_ellipsoide *src)
{
	t_ellipsoide	*copy;

	if (!(copy = (t_ellipsoide*)malloc(sizeof(t_ellipsoide))))
		return NULL;
	if (!(copy->center = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	vec_copy(src->center, copy->center);
	copy->a = src->a;
	copy->b = src->b;
	copy->c = src->c;
	return copy;
}

t_object	*object_copy(t_object *src)
{
	t_object	*copy;

	if (!src)
		return NULL;
	if (!(copy = (t_object*)malloc(sizeof(t_object))))
		return NULL;
	copy->num = src->num;
	copy->type = src->type;
	if (copy->type == 1)
		(t_sphere*)(copy->dim) = duplicate_sphere((t_sphere*)(src->dim));
	else if (copy->type == 2)
		(t_plane*)(copy->dim) = duplicate_plane((t_plane*)(src->dim));
	else if (copy->type == 3)
		(t_cone*)(copy->dim) = duplicate_cone((t_cone*)(src->dim));
	else if (copy->type == 4)
		(t_cylindre*)(copy->dim) = duplicate_cylindre((t_cylindre*)(src->dim));
	else if (copy->type == 5)
		(t_ellipsoide*)(copy->dim) = duplicate_ellipsoide((t_ellipsoide*)(src->dim));
	copy->shadow = src->shadow;
	copy->col = src->col;
	copy->kd = src->kd;
	copy->ks = src->ks;
	copy->transparency = src->transparency;
	copy->reflection = src->reflection;
	copy->thickness = src->thickness;
	copy->index = src->index;
	copy->phong = src->phong;
	if (!(copy->tmp_vec = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	copy->next = object_copy(src->next);
	return (copy);
}