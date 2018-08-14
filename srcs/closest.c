#include "rt_objects.h"

t_object	*closest_object(t_param *param, double *from, double *to, t_path *path)
{
	param->obj_d= -1.0;
	t_object *objs = param->objects;
	t_limit	*limits;

	while (objs)
	{
		if (!param->is_for_light || objs != path->current_object)
		{
			param->is_cut = -1;
			param->tmp_d = distance_calc(objs, param, from, to);
			// if (point_display(param))
			// 	printf("\ntype: %d | tmp_d: %f\n", objs->type, param->tmp_d);
			if (param->tmp_d > 0.0 &&
				(param->is_for_light || (param->obj_d < 0.0 || param->tmp_d < param->obj_d)))
			{
				vec_multiply(param->tmp_d + param->epsilon, to, path->valid_x);
				pt_translated(from, path->valid_x, path->valid_x);
				// if (point_display(param))
				// 	printf("()valid_x: [%f,%f,%f]\n", path->valid_x[0], path->valid_x[1], path->valid_x[2]);
				update_normal_vector(objs, path);
				limits = objs->limits;
				while (limits && param->tmp_d > 0 && param->is_cut)
				{
					if (!is_in_limit(path->valid_x, limits))
					{
						param->tmp_d = plane_distance(from, to, limits->plane.n, limits->plane.ref);
						vec_multiply(param->tmp_d + param->epsilon, to, path->valid_x);
						pt_translated(from, path->valid_x, path->valid_x);
						if (param->tmp_d > 0 && is_inside_object(path->valid_x, objs, limits))
						{
							// if (point_display(param))
							// 	printf("point dans objet\n");
							param->is_cut = 0;
							vec_copy(limits->plane.n, path->valid_n);
						}
						else
							param->is_cut = 1;
					}
					limits = limits->next;
				}
				// if (point_display(param))
				// 	printf("objs final tmp_d: %f\n", param->tmp_d);
				if (param->is_cut != 1 && param->tmp_d > 0.0)
				{
					// if (point_display(param))
					// 	printf("object intersectant type %d\n", objs->type);	
					param->intersect_object = objs;
					param->obj_d = param->tmp_d;
					if (!param->is_for_light)
					{
						vec_multiply(param->obj_d - param->epsilon, to, path->x);
						pt_translated(from, path->x, path->x);
						vec_copy(path->valid_n, path->n);
					}
					else if (param->tmp_light->type != RTSPOT ||
						param->obj_d * param->obj_d < pt_dist_root(from, param->tmp_light->src))
					{
						// update de la couleur temporaire de la lumière.
						param->tmp_light->tmp_col = rgb_ratio(color_absorber(objs->col, param->tmp_light->tmp_col), objs->transparency);
					}
				}
			}
		}
		objs = objs->next;
	}
	return (param->intersect_object);
}

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
	return (0);
}

void		update_normal_vector(t_object *tmp, t_path *path)
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
	if (path->inside_obj)
		vec_multiply(-1.0, path->valid_n, path->valid_n);
	vec_to_unit_norm(path->valid_n);
}
