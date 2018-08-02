#include "rt.h"

t_object	*closest_object(t_param *param, double *from, double *to, t_path *path)
{
	param->obj_d= -1.0;
	t_object *objs = param->objects;
	t_limit	*limits;
	// t_limit *is_cut_limit;

	if (point_display(param))
		printf("- closest -\n");
	while (objs)
	{
		if (!param->is_for_light || objs != path->current_object)
		{
			param->is_cut = 0;
			param->tmp_d = distance_calc(objs, param, from, to);
			if (param->tmp_d > 0.0 && (param->obj_d < 0.0 || param->tmp_d < param->obj_d))
			{
			// // 	param->obj_d = param->tmp_d;
			// // 	if (!param->is_for_light)
			// // 	{
			// // 		vec_multiply(param->tmp_d - param->epsilon, to, path->x);
			// // 		pt_translated(from, path->x, path->x);
			// // 		update_normal_vector(objs, path);		
			// // 	}
			// // 	param->intersect_object = objs;
			// // }
			// // objs = objs->next;

				if (point_display(param))
					printf("objet rencontré type %d\n", objs->type);
				vec_multiply(param->tmp_d + param->epsilon, to, path->valid_x);
				pt_translated(from, path->valid_x, path->valid_x);
				update_normal_vector(objs, path);
				limits = objs->limits;
				while (limits && param->tmp_d > 0)
				{
					if (point_display(param))
						printf("- new limit\n");				
					if (!is_in_limit(path->valid_x, limits))
					{
						if (point_display(param))
							printf("OBJECT CUT\n");
						param->tmp_d = plane_distance(from, to, limits->plane.n, limits->plane.ref);
						vec_multiply(param->tmp_d + param->epsilon, to, path->valid_x);
						pt_translated(from, path->valid_x, path->valid_x);
						if (point_display(param))
							printf("is inside obj ? %d \n", is_inside_object(objs, path));
						if (param->tmp_d > 0 && is_inside_object(objs, path))
						{
							if (point_display(param))
								printf("NEW INTERSECTION IN OBJECT\n");
							param->is_cut = 1;
							vec_copy(limits->plane.n, path->valid_n);
						}
						else
							param->tmp_d = -1;
					}
					else
						if (point_display(param))
							printf("NON CUTTING OBJECT\n");
					limits = limits->next;
				}
				if (param->is_cut)
				{
					limits = objs->limits;
					while (limits && param->tmp_d > 0)
					{
						if (!is_in_limit(path->valid_x, limits))
							param->tmp_d = -1;
						limits = limits->next;
					}
				}
				if (param->tmp_d > 0.0)
				{
					param->intersect_object = objs;
					param->obj_d = param->tmp_d;
					if (!param->is_for_light)
					{
						vec_multiply(param->obj_d - param->epsilon, to, path->x);
						pt_translated(from, path->x, path->x);
						vec_copy(path->valid_n, path->n);
					}
				}
				else
					if (point_display(param))
						printf("object ignored because CUT\n");


			// 	limits = objs->limits;
			// 	vec_multiply(param->tmp_d, to, path->tmp_x);
			// 	pt_translated(from, path->tmp_x, path->tmp_x);
			// 	while (limits && param->tmp_d > 0)
			// 	{
			// 		if (!is_in_limit(path->tmp_x, limits))
			// 			param->tmp_d = -1;				
			// 		limits = limits->next;
			// 	}
			// 	if (param->tmp_d < 0)
			// 	{
			// 		limits = objs->limits;
			// 		while (limits)
			// 		{
			// 			//point d'intersection avec la limite
			// 			param->tmp_d_cut = plane_distance(from, to, limits->plane.n, limits->plane.ref);
			// 			vec_multiply(param->tmp_d_cut - param->epsilon, to, path->tmp_x);
			// 			pt_translated(from, path->tmp_x, path->tmp_x);
			// 			is_cut_limit = objs->limits;
			// 			while (is_cut_limit && param->tmp_d_cut > 0)
			// 			{
			// 				if (is_cut_limit != limits && !is_in_limit(path->tmp_x, is_cut_limit))
			// 					param->tmp_d_cut = -1;
			// 				is_cut_limit = is_cut_limit->next;
			// 			}
			// 			if (param->tmp_d_cut > 0 && is_inside_object(path->tmp_x, objs) && (param->tmp_d < 0 || param->tmp_d_cut < param->tmp_d))
			// 			{
			// 				param->is_cut = 1;
			// 				vec_copy(path->tmp_x, path->final_x);
			// 				vec_copy(limits->plane.n, path->final_n);
			// 				param->tmp_d = param->tmp_d_cut;
			// 			}
			// 			limits = limits->next;
			// 		}
			// 	}
			// 	if (param->tmp_d > 0.0 && (param->obj_d < 0.0 || param->tmp_d < param->obj_d))
			// 	{
			// 		param->obj_d = param->tmp_d;
			// 		param->intersect_object = objs;
			// 		if (!param->is_for_light)
			// 		{
			// 			if (param->is_cut)
			// 			{
			// 				vec_copy(path->final_x, path->x);
			// 				vec_copy(path->final_n, path->n);
			// 			}
			// 			else
			// 			{
			// 				vec_multiply(param->tmp_d - param->epsilon, to, path->x);
			// 				pt_translated(from, path->x, path->x);
			// 				update_normal_vector(objs, path);
			// 			}
			// 		}
			// 	}
			}	
		}
		objs = objs->next;
	}
	// if (param->intersect_object)
	// {
	// 	param->obj_d -= param->epsilon;
	// 	vec_multiply(param->obj_d, to, path->x);
	// 	pt_translated(from, path->x, path->x);
	// }
	return (param->intersect_object);
}

int			is_inside_object(t_object *obj, t_path *path)
{
	if (obj->type == 1)
		return is_inside_sphere(obj, path);
	else if (obj->type == 2)
		return is_inside_plane(obj, path);
	else if (obj->type == 3)
		return is_inside_cone(obj, path);
	else if (obj->type == 4)
		return is_inside_cylindre(obj, path);
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
	vec_to_unit_norm(path->valid_n);
}
