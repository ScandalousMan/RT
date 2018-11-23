#include "rt_objects.h"

int		object_color(t_param *param, t_path *path)
{
	if (param && path && path->current_object)
	{
		param->tmp_light = param->lights;
		// A REMPLACER PAR OBJECT POSITION
		object_position(path->x, path->current_object);
		// if (point_display(param))
		// 	printf("u=%f, v=%f\n", path->current_object->uv_map[0], path->current_object->uv_map[1]);
		object_color_changer(path->current_object, param);
		object_normal_changer(path->current_object, param, path);
		param->final_col = rgb_ratio(param->texture_col, (double)param->macro.k_ambience);
		while (param->tmp_light)
		{
			// if (point_display(param))
				// printf("light type in new function: num %d, type %d\n$$$\n", param->tmp_light->num, param->tmp_light->type);
			if (param->tmp_light->type == RTSPOT)
				vec_soustraction(param->tmp_light->src, path->x, path->l);
			else
				vec_multiply(-1.0, param->tmp_light->src, path->l);
			vec_to_unit_norm(path->l);
			vec_multiply(-2.0 * scalar_product(path->n, path->v), path->n, path->r);
			pt_translated(path->r, path->v, path->r);
			vec_to_unit_norm(path->r);
			light_masked(param, path->x, path->l, path);

			// if (!light_masked(param, path->x, path->l, path))
			// {
				if (scalar_product(path->l, path->n) > 0.0){
					// if (point_display(param))
					// 	printf("color: %d, %d, %d\n", (color_absorber(param->tmp_light->col, path->current_object->col) >> 16) & 0xFF, (color_absorber(param->tmp_light->col, path->current_object->col) >> 8) & 0xFF, color_absorber(param->tmp_light->col, path->current_object->col) & 0xFF);
					param->final_col = color_summer(param->final_col,
						rgb_ratio(color_absorber(param->tmp_light->tmp_col, param->texture_col),
							path->current_object->kd * scalar_product(path->l, path->n) * param->tmp_light->i));
				}
				if (param->brightness && ft_pow(scalar_product(path->l, path->r), param->brightness) > 0.0){
					param->final_col = color_summer(param->final_col,
						rgb_ratio(param->tmp_light->tmp_col, path->current_object->ks * ft_pow(scalar_product(path->l, path->r), path->current_object->phong) * param->tmp_light->i));
				}
			// }
			param->tmp_light = param->tmp_light->next;
		}
		return param->final_col;
	}
	return (0);
}

double	*ray_direction(t_param *param, int i, int j)
{
	vec_multiply(param->f, param->look, param->path->v);
	vec_multiply(((double)WINDOW_SDL_HEIGHT * param->macro.anti_aliasing / 2.0 - (double)i) * 40.0 /
		(double)WINDOW_SDL_HEIGHT / param->macro.anti_aliasing, param->third, param->tmp_vec);
	pt_translated(param->path->v, param->tmp_vec, param->path->v);
	vec_multiply(((double)j - (double)WINDOW_SDL_WIDTH * param->macro.anti_aliasing / 2.0) * 40.0 /
		(double)WINDOW_SDL_WIDTH / param->macro.anti_aliasing, param->align, param->tmp_vec);
	pt_translated(param->path->v, param->tmp_vec, param->path->v);
	vec_to_unit_norm(param->path->v);
	return (param->path->v);
}

int		ray_color(t_param *param, double *from, double *to, int index, t_path *path)
{
	// int a;
	// int b;
	// int c;

	// if (point_display(param))
	// 	printf("ray_color] index: %d\n", index);
	path->current_object = NULL;
	param->intersect_object = NULL;
	param->is_for_light = 0;
	path->current_object = closest_object(param, from, to, path);
	if (!path->current_object)
	{
		if (!index)
			param->pxl_infos[param->i[0]][param->i[1]] = 0;
		return 0;
	}
	else
	{
		if (!index)
			param->pxl_infos[param->i[0]][param->i[1]] = path->current_object->num;
		if (!param->to_pix && index < param->macro.recursion)
		{
			// REFLECTED
			path->reflected->inside_obj = path->inside_obj;
			vec_copy(path->r, path->reflected->v);
			vec_copy(path->x, path->reflected->from);
			// TRANSMITTED
			define_refracted_n(path, path->transmitted);
			// if (point_display(param))
			// 	printf("indice from: %f, to: %f\n", get_index_n(path), get_index_n(path->transmitted));
			if ((snell_descartes(get_index_n(path), get_index_n(path->transmitted), path, path->transmitted)))
			{
				// if (point_display(param))
				// 	printf("== snell descartes OK\n");
				// if (point_display(param))
				// 	printf("refraction OK:\n - v1: [%f,%f,%f]\n - v2: [%f,%f,%f]\n - n: [%f,%f,%f]\n\n", path->v[0], path->v[1], path->v[2], path->transmitted->v[0], path->transmitted->v[1], path->transmitted->v[2], path->n[0], path->n[1], path->n[2]);
				vec_copy(path->x, path->transmitted->from);
				vec_multiply(EPSILON, path->v, param->tmp_vec);
				pt_translated(path->transmitted->from, param->tmp_vec, path->transmitted->from);
				vec_multiply(EPSILON, path->transmitted->v, param->tmp_vec);
				pt_translated(path->transmitted->from, param->tmp_vec, path->transmitted->from);

				// if (point_display(param))
				// 	printf("new x:[%f,%f,%f]\n", path->transmitted->from[0], path->transmitted->from[1], path->transmitted->from[2]);
				// a = rgb_ratio(object_color(param, path), (1.0 - path->current_object->transparency - path->current_object->reflection));
				// if (point_display(param))
				// 	printf("\n\n == REFRACTED == \n");
				// b = rgb_ratio(ray_color(param, path->transmitted->from, path->transmitted->v, index + 1, path->transmitted), path->current_object->transparency);
				// if (point_display(param))
				// 	printf("\n == ENDRACTED == \n");
				// c = rgb_ratio(ray_color(param, path->reflected->from, path->reflected->v, index + 1, path->reflected), path->current_object->reflection);
				// if (point_display(param))
				// 	printf("a: %d, b: %d, c: %d\n", a, b, c);
				// return (
				// 	color_summer(
				// 		color_summer(a, color_absorber(b, path->current_object->col)),
				// 		color_absorber(c, path->current_object->col)
				// 	)
				// );
				
				return (
					color_summer(
						color_summer(
							rgb_ratio(object_color(param, path), (1.0 - path->current_object->transparency - path->current_object->reflection)),
							color_absorber(rgb_ratio(ray_color(param, path->transmitted->from, path->transmitted->v, index + 1, path->transmitted), path->current_object->transparency), path->current_object->col)
						),
						color_absorber(rgb_ratio(ray_color(param, path->reflected->from, path->reflected->v, index + 1, path->reflected), path->current_object->reflection), path->current_object->col)
					)
				);
			}
			else
			{
				// if (point_display(param))
				// 	printf("refraction KO:\n - v1: [%f,%f,%f]\n - n: [%f,%f,%f]\n", path->v[0], path->v[1], path->v[2], path->n[0], path->n[1], path->n[2]);
				// a = rgb_ratio(object_color(param, path), (1.0 - path->current_object->transparency - path->current_object->reflection));
				// c = rgb_ratio(ray_color(param, path->reflected->from, path->reflected->v, index + 1, path->reflected), path->current_object->reflection + path->current_object->transparency);
				// if (point_display(param))
				// 	printf("a: %d & c: %d\n", a, c);
				// return (color_summer(a, c));

				return (
					color_summer(
						rgb_ratio(object_color(param, path), (1.0 - path->current_object->transparency - path->current_object->reflection)),
						color_absorber(rgb_ratio(ray_color(param, path->reflected->from, path->reflected->v, index + 1, path->reflected), path->current_object->reflection + path->current_object->transparency), path->current_object->col)
					)
				);
			}
		}
		else
			return (object_color(param, path));
	}
}

void	rt_tracer(t_param *param)
{
	int			col[3];
	int			tmp_col;
	int 		alias[2];

	const int	pixelisation = (param->to_pix) ? PIXELISATION : 1;
	const int	db_antialiasing = param->macro.anti_aliasing * param->macro.anti_aliasing;

	param->i[0] = param->current_thread * WINDOW_SDL_HEIGHT / NB_THREAD;
	while (param->i[0] < (param->current_thread + 1) * WINDOW_SDL_HEIGHT / NB_THREAD)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			ft_bzero(col, sizeof(int) * 3);
			alias[0] = 0;
			while (alias[0] < param->macro.anti_aliasing)
			{
				alias[1] = 0;
				while (alias[1] < param->macro.anti_aliasing)
				{
					ray_direction(param,
						param->macro.anti_aliasing * param->i[0] + alias[0],
						param->macro.anti_aliasing * param->i[1] + alias[1]);
					tmp_col = ray_color(param, param->eye, param->path->v, 0, param->path);
					// if (point_display(param))
					// 	printf("=> tmp_col:%d\n", tmp_col);
					col[0] += (tmp_col >> 16) & 0xFF;
					col[1] += (tmp_col >> 8) & 0xFF;
					col[2] += (tmp_col) & 0xFF;
					alias[1]++;
				}
				alias[0]++;
			}
			int y;
			y = 0;
			while (y < pixelisation)
			{
				int	x;
				x = 0;
				while (x < pixelisation)
				{
					// ! ajout de la couleur en info segfault avec le recalcul du escape
					// param->pxl_infos[param->i[0] + x][param->i[1] + y]->col = rgb_color(
					// 	(unsigned char)(col[0] / db_antialiasing),
					// 	(unsigned char)(col[1] / db_antialiasing),
					// 	(unsigned char)(col[2] / db_antialiasing));

					putpxl(param, param->i[0] + x, param->i[1] + y, rgb_color(
						(unsigned char)(col[0] / db_antialiasing),
						(unsigned char)(col[1] / db_antialiasing),
						(unsigned char)(col[2] / db_antialiasing)));
					++x;
				}
			++y;
			}
			param->i[1] += pixelisation;
		}
		param->i[0] += pixelisation;
	}
}
