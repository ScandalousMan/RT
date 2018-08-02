#include "rt.h"

t_object	*closest_object(t_param *param, double *from, double *to, t_path *path)
{
	param->obj_d= -1.0;
	t_object *objs = param->objects;
	t_limit	*limits;
	t_limit *is_cut_limit;

	if (point_display(param))
		printf("- closest -\n");
	while (objs)
	{
		// param->is_cut = 0;
		param->tmp_d = distance_calc(objs, param, from, to);
		if (param->tmp_d > 0.0 && (param->obj_d < 0.0 || param->tmp_d < param->obj_d))
		{
			param->obj_d = param->tmp_d;
			param->intersect_object = objs;
			if (!param->is_for_light) {
				vec_multiply(param->tmp_d - param->epsilon, to, path->tmp_x);
				pt_translated(from, path->tmp_x, path->tmp_x);
				vec_copy(path->tmp_x, path->x);
				update_normal_vector(objs, path);
				if (point_display(param))
					printf("x= [%f, %f, %f] || normal= [%f, %f, %f]\n", path->x[0], path->x[1], path->x[2], path->n[0], path->n[1], path->n[2]);
			}

			// limits = objs->limits;
			// vec_multiply(param->tmp_d, to, path->tmp_x);
			// pt_translated(from, path->tmp_x, path->tmp_x);
			// while (limits && param->tmp_d > 0)
			// {
			// 	if (!is_in_limit(path->tmp_x, limits))
			// 		param->tmp_d = -1;				
			// 	limits = limits->next;
			// }
			// if (param->tmp_d < 0)
			// {
			// 	if (point_display(param))
			// 	{
			// 		printf("object cut #%d\n", objs->num);
			// 	}
			// 	limits = objs->limits;
			// 	while (limits)
			// 	{
			// 		//point d'intersection avec la limite
			// 		param->tmp_d_cut = plane_distance(from, to, limits->plane.n, limits->plane.ref);
			// 		vec_multiply(param->tmp_d_cut - param->epsilon, to, path->tmp_x);
			// 		pt_translated(from, path->tmp_x, path->tmp_x);
			// 		is_cut_limit = objs->limits;
			// 		while (is_cut_limit && param->tmp_d_cut > 0)
			// 		{
			// 			if (is_cut_limit != limits && !is_in_limit(path->tmp_x, is_cut_limit))
			// 				param->tmp_d_cut = -1;
			// 			is_cut_limit = is_cut_limit->next;
			// 		}
			// 		if (point_display(param) && param->tmp_d_cut > 0)
			// 		{
			// 			printf("cut included dans toutes les limites\n");
			// 		}
			// 		if (param->tmp_d_cut > 0 && is_inside_object(path->tmp_x, objs) && (param->tmp_d < 0 || param->tmp_d_cut < param->tmp_d))
			// 		{
			// 			param->is_cut = 1;
			// 			vec_copy(path->tmp_x, path->final_x);
			// 			vec_copy(limits->plane.n, path->final_n);
			// 			param->tmp_d = param->tmp_d_cut;
			// 			if (point_display(param))
			// 			{
			// 				printf("cut considéré comme final\n");
			// 			}
			// 		}
			// 		limits = limits->next;
			// 	}
			// }
			// if (param->tmp_d > 0.0 && (param->obj_d < 0.0 || param->tmp_d < param->obj_d))
			// {
			// 	param->obj_d = param->tmp_d;
			// 	param->intersect_object = objs;
			// 	if (!param->is_for_light)
			// 	{
			// 		if (param->is_cut)
			// 		{
			// 			vec_copy(path->final_x, path->x);
			// 			vec_copy(path->final_n, path->n);	
			// 		}
			// 		else
			// 		{
			// 			vec_multiply(param->tmp_d - param->epsilon, to, path->x);
			// 			pt_translated(from, path->x, path->x);
			// 			update_normal_vector(objs, path);
			// 		}
			// 	}
			// }
		}
		objs = objs->next;
	}
	return (param->intersect_object);
}

int			is_inside_object(double *pt, t_object *obj)
{
	if (obj->type == 1)
		return is_inside_sphere(pt, obj);
	else if (obj->type == 2)
		return is_inside_plane(pt, obj);
	else if (obj->type == 3)
		return is_inside_cone(pt, obj);
	else if (obj->type == 4)
		return is_inside_cylindre(pt, obj);
	return 0;
}

void		update_normal_vector(t_object *tmp, t_path *path)
{
	if (tmp->type == 1)
		update_normal_sphere(tmp, path);
	else if (tmp->type == 2)
		update_normal_plane(tmp, path);
	else if (tmp->type == 3)
		update_normal_cone(tmp, path);
	else if (tmp->type == 4)
		update_normal_cylindre(tmp, path);
	vec_to_unit_norm(path->n);
}
