#include "rt.h"

int		object_color(t_param *param, t_path *path)
{
	if (param && path && path->current_object)
	{
		param->bright = 0.0;
		param->diffuse = 0.0;
		param->tmp_light = param->lights;
		while (param->tmp_light)
		{
			vec_soustraction(param->tmp_light->src, path->x, path->l);
			vec_to_unit_norm(path->l);
			vec_multiply(-2.0 * scalar_product(path->n, path->v), path->n, path->r);
			pt_translated(path->r, path->v, path->r);
			vec_to_unit_norm(path->r);
			if (point_display(param))
			{
				printf("== light #%d avec n=[%f,%f,%f] et l=[%f,%f,%f]\n", param->tmp_light->num, path->n[0], path->n[1], path->n[2], path->l[0], path->l[1], path->l[2]);
			}
			if (!light_masked(param, path->x, param->tmp_light->src, path))
			{
				if (point_display(param))
				{
					printf(">> illuminated avec n=[%f,%f,%f] et l=[%f,%f,%f]\n", path->n[0], path->n[1], path->n[2], path->l[0], path->l[1], path->l[2]);
				}
				if (scalar_product(path->l, path->n) * param->tmp_light->i > 0.0)
					param->diffuse += scalar_product(path->l, path->n) * param->tmp_light->i;
				if (param->brightness && ft_pow(scalar_product(path->l, path->r), param->brightness) * param->tmp_light->i > 0.0)
					param->bright += ft_pow(scalar_product(path->l, path->r), path->current_object->phong) * param->tmp_light->i;
			}
			param->tmp_light = param->tmp_light->next;
		}
		return color_summer(rgb_ratio(path->current_object->col, 0.2 + path->current_object->kd * param->diffuse),
			rgb_ratio(16777215, path->current_object->ks * (param->bright > 1.0 ? 1.0 : param->bright)));
	}
	return (0);
}

double	*ray_direction(t_param *param, int i, int j)
{
	vec_multiply(param->f, param->look, param->path->v);
	vec_multiply(((double)WINDOW_SDL_HEIGHT * ANTI_ALIASING / 2.0 - (double)i) * 40.0 /
		(double)WINDOW_SDL_HEIGHT / ANTI_ALIASING, param->third, param->tmp_vec);
	pt_translated(param->path->v, param->tmp_vec, param->path->v);
	vec_multiply(((double)j - (double)WINDOW_SDL_WIDTH * ANTI_ALIASING / 2.0) * 40.0 /
		(double)WINDOW_SDL_WIDTH / ANTI_ALIASING, param->align, param->tmp_vec);
	pt_translated(param->path->v, param->tmp_vec, param->path->v);
	vec_to_unit_norm(param->path->v);
	return (param->path->v);
}

int		ray_color(t_param *param, double *from, double *to, int index, t_path *path)
{
	path->current_object = NULL;
	param->is_for_light = 0;
	path->current_object = closest_object(param, from, to, path);
	if (!path->current_object)
	{
		if (!param->pxl_infos[param->i[0]][param->i[1]]->object)
			param->pxl_infos[param->i[0]][param->i[1]]->object = NULL;
		return 0;
	}
	else
	{
		if (point_display(param))
		{
			printf("#%d avec n=[%f,%f,%f] et x=[%f,%f,%f] et O=[%f,%f,%f]\n", path->current_object->num, path->n[0], path->n[1], path->n[2], path->x[0], path->x[1], path->x[2], path->current_object->tmp_vec[0], path->current_object->tmp_vec[1], path->current_object->tmp_vec[2]);
		}
		if (!index)
			param->pxl_infos[param->i[0]][param->i[1]]->object = path->current_object;
		if (index < RECURSION)
		{
			vec_copy(path->v, path->transmitted->v);
			vec_copy(path->x, path->transmitted->from);
			vec_copy(path->r, path->reflected->v);
			vec_copy(path->x, path->reflected->from);
			vec_multiply(2 * EPSILON, path->v, param->tmp_vec);
			pt_translated(path->transmitted->from, param->tmp_vec, path->transmitted->from);
			return (rgb_ratio(object_color(param, path),
				(1.0 - path->current_object->transparency - path->current_object->reflection)) +
				rgb_ratio(ray_color(param, path->transmitted->from, path->transmitted->v, index + 1, path->transmitted),
				path->current_object->transparency) +
				rgb_ratio(ray_color(param, path->reflected->from, path->reflected->v, index + 1, path->reflected),
				path->current_object->reflection));
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
	const int	db_antialiasing = 2 * ANTI_ALIASING;

	param->i[0] = param->current_thread * WINDOW_SDL_HEIGHT / NB_THREAD;
	while (param->i[0] < (param->current_thread + 1) * WINDOW_SDL_HEIGHT / NB_THREAD)
	{
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			ft_bzero(col, sizeof(int) * 3);
			alias[0] = 0;
			while (alias[0] < ANTI_ALIASING)
			{
				alias[1] = 0;
				while (alias[1] < ANTI_ALIASING)
				{
					ray_direction(param,
						ANTI_ALIASING * param->i[0] + alias[0],
						ANTI_ALIASING * param->i[1] + alias[1]);
					tmp_col = ray_color(param, param->eye, param->path->v, 0, param->path);
					col[0] += (tmp_col >> 16) & 0xFF;
					col[1] += (tmp_col >> 8) & 0xFF;
					col[2] += (tmp_col) & 0xFF;
					++alias[1];
				}
				++alias[0];
			}
			int y;
			y = 0;
			while (y < pixelisation)
			{
				int	x;
				x = 0;
				while (x < pixelisation)
				{
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
