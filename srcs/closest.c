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
			param->tmp_d = distance_calc(objs, from, to);
			// if (point_display(param))
			// 	printf("\ntype: %d | tmp_d: %f\n", objs->type, param->tmp_d);
			if (param->tmp_d > 0.0 &&
				(param->is_for_light || (param->obj_d < 0.0 || param->tmp_d < param->obj_d)))
			{
				vec_multiply(param->tmp_d + param->epsilon, to, path->valid_x);
				pt_translated(from, path->valid_x, path->valid_x);
				// if (point_display(param))
				// 	printf("(*)valid_x: [%f,%f,%f]\n", path->valid_x[0], path->valid_x[1], path->valid_x[2]);
				update_normal_vector(objs, path);
				// if (point_display(param))
				// 	printf("( )valid_n: [%f,%f,%f]\n", path->valid_n[0], path->valid_n[1], path->valid_n[2]);
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

int			sierpinski_carpet(int u, int v)
{
	int i;

	i = SIERPINSKI;
	while (i > 1)
	{
		if ((u / ((int)ft_pow(3, i - 2))) % 3 == 1 &&
			(v / ((int)ft_pow(3, i - 2))) % 3 == 1)
			return 0;
		i--;
	}
	return 1;
}

void 		object_color_changer(t_object *object, t_param *param)
{
	char 	t;

	if (object->type == RTQUADRIC || object->effects.color == RT_C_NONE)
		param->texture_col = object->col;
	else if (object->effects.color == RT_C_CHESS)
		param->texture_col = (int)(floor(object->uv_map[0] * 8.0) + floor(object->uv_map[1] * 8.0)) % 2 ? object->col : rgb_color(255, 255, 255);
	else if (object->effects.color == RT_C_SIERPINSKI)
		param->texture_col = sierpinski_carpet((int)floor(object->uv_map[0] * ft_pow(3, SIERPINSKI)), (int)floor(object->uv_map[1] * ft_pow(3, SIERPINSKI))) ? object->col : rgb_color(255, 255, 255);
	else if (object->effects.color == RT_C_CLOUD)
	{
		t = turbulence(object->uv_map[0] * 128.0, object->uv_map[1] * 128.0, TURB_SIZE, param);
		param->texture_col = rgb_color((char)t, (char)t, (char)t);
	}
	else if (object->effects.color == RT_C_MARBLE)
	{
		t = (char)(255.0 * marble_ratio(object->uv_map[0] * 128.0, object->uv_map[1] * 128.0, TURB_SIZE, param));
		param->texture_col = rgb_color(t, t, t);
	}
	else if (object->effects.color == RT_C_WOOD)
	{
		t = wood_ratio(object->uv_map[0] * 128.0, object->uv_map[1] * 128.0, TURB_SIZE, param);
		param->texture_col = rgb_color(80 + t, 30 + t, 30);
	}
}

void		object_normal_changer(t_object *object, t_param *param, t_path *path)
{
	if (object->type == RTQUADRIC || object->effects.normal == RT_N_NONE)
		return;
	else if (object->effects.normal == RT_N_SINUS)
	{
		rotation_matrice(0, 0, 45 * sin(object->uv_map[0] * 2.0 * M_PI * 20), param);
		matrice_product(param->rot, path->n, path->n);
	}
}
