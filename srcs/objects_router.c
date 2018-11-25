#include "rt_objects.h"

int			is_inside_object(double *pt, t_object *obj, t_limit *limit)
{
	if (!(is_in_limits(pt, obj, limit)))
		return (0);
	if (obj->type == RTSPHERE)
		return is_inside_sphere(pt, obj);
	else if (obj->type == RTPLAN)
		return is_inside_plane(pt, obj);
	else if (obj->type == RTCONE)
		return is_inside_cone(pt, obj);
	else if (obj->type == RTCYLINDER)
		return is_inside_cylindre(pt, obj);
	else if (obj->type == RTQUADRIC)
		return is_inside_quadric(pt, (t_quadric*)(obj->dim));
	else if (obj->type == RTCUBE)
		return is_inside_cube(pt, obj);
	return (0);
}

void		update_normal_vector(t_object *tmp, t_path *path, double *pt)
{
	if (tmp->type == RTSPHERE)
		update_normal_sphere(tmp, path);
	else if (tmp->type == RTPLAN)
		update_normal_plane(tmp, path);
	else if (tmp->type == RTCONE)
		update_normal_cone(tmp, path);
	else if (tmp->type == RTCYLINDER)
		update_normal_cylindre(tmp, path);
	else if (tmp->type == RTQUADRIC)
		update_normal_quadric((t_quadric*)(tmp->dim), path);
	else if (tmp->type == RTCUBE)
		update_normal_cube(tmp, path);
	if (is_inside_object(pt, tmp, NULL))
		vec_multiply(-1.0, path->valid_n, path->valid_n);
	vec_to_unit_norm(path->valid_n);
}

void		object_position(double *pt, t_object *object)
{
	if (object->type == RTSPHERE)
		sphere_position(pt, object);
	else if (object->type == RTPLAN)
		plane_position(pt, object);
	else if (object->type == RTCONE)
		cone_position(pt, object);
	else if (object->type == RTCYLINDER)
		cylindre_position(pt, object);
	else if (object->type == RTQUADRIC)
		quadric_position(pt, object);
	else if (object->type == RTCUBE)
		cube_position(pt, object);
}

void	update_objects(t_param *param)
{
	t_object	*tmp;

	tmp = param->objects;
	while (tmp)
	{
		if (tmp->type == RTSPHERE)
			update_sphere(tmp, param);
		else if (tmp->type == RTPLAN)
			update_plane(tmp, param);
		else if (tmp->type == RTCONE)
			update_cone(tmp, param);
		else if (tmp->type == RTCYLINDER)
			update_cylindre(tmp, param);
		else if (tmp->type == RTQUADRIC)
			update_quadric(tmp, param);
		else if (tmp->type == RTCUBE)
			update_cube(tmp, param);
		tmp = tmp->next;
	}
	display_objects(param);
}

void	default_ref_updater(t_object *obj)
{
	obj->ref.i[0] = 1.0f;
	obj->ref.i[1] = 0.0f;
	obj->ref.i[2] = 0.0f;
	obj->ref.j[0] = 0.0f;
	obj->ref.j[1] = 1.0f;
	obj->ref.j[2] = 0.0f;
	obj->ref.k[0] = 0.0f;
	obj->ref.k[1] = 0.0f;
	obj->ref.k[2] = 1.0f;
}

int		are_colinear(double *a, double *b)
{
	if (!vec_norm(a) || !vec_norm(b))
		return (0);
	if (ft_absdbl(scalar_product(a, b)) == vec_norm(a) * vec_norm(b))
		return (1);
	return (0);
}

void	special_ref_updater(double *vec, t_object *obj)
{
	default_ref_updater(obj);
	vec_copy(vec, obj->ref.k);
	if (are_colinear(vec, obj->ref.i))
	{
		printf("colinear\n");
		vector_product(obj->ref.j, vec, obj->ref.i);
	}
	else
	{
		printf("not colinear\n");
		vector_product(vec, obj->ref.i, obj->ref.j);
		vec_to_unit_norm(obj->ref.j);
		vector_product(obj->ref.j, vec, obj->ref.i);
		vec_to_unit_norm(obj->ref.i);
	}
}
