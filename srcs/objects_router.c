/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_router.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2018/10/31 21:49:47 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

int		is_inside_object(double *pt, t_object *obj, t_limit *limit)
{
	if (!(is_in_limits(pt, obj, limit)))
		return (0);
	if (obj->type == RTSPHERE)
		return (is_inside_sphere(pt, obj));
	else if (obj->type == RTPLAN)
		return (is_inside_plane(pt, obj));
	else if (obj->type == RTCONE)
		return (is_inside_cone(pt, obj));
	else if (obj->type == RTCYLINDER)
		return (is_inside_cylindre(pt, obj));
	else if (obj->type == RTQUADRIC)
		return (is_inside_quadric(pt, (t_quadric*)(obj->dim)));
	else if (obj->type == RTCUBE)
		return (is_inside_cube(pt, obj));
	return (0);
}

void	update_normal_vector(t_object *tmp, t_path *path, double *pt)
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

void	object_position(double *pt, t_object *object)
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
