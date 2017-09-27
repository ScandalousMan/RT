#include "rt.h"

void	find_intersection(t_param *param, double *from, double *to, t_path *path)
{
	path->current_object = closest_object(param, from, to, path);
		if (path->current_object)
		{
			vec_multiply(param->obj_d - param->epsilon, path->v, path->x);
			pt_translated(from, path->x, path->x);
			update_normal_vector(path->current_object, path);
		}
}

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
			if (!object_intersection(param, path->x, param->tmp_light->src, path))
			{
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
	find_intersection(param, from, to, path);
	if (index < MAX_RECURSION)
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

void	rt_tracer(t_param *param)
{
	int		col[3];
	int		tmp_col;
	int 	alias[2];

	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		param->i[1] = 1;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			col[0] = 0;
			col[1] = 0;
			col[2] = 0;
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
					col[0] += tmp_col & 0xFF;
					col[1] += (tmp_col >> 8) & 0xFF;
					col[2] += (tmp_col >> 16) & 0xFF;
					alias[1]++;
				}
				alias[0]++;
			}
			store_pixel(param, rgb_color((unsigned char)(col[0] / ANTI_ALIASING / ANTI_ALIASING),
				(unsigned char)(col[1] / ANTI_ALIASING / ANTI_ALIASING),
				(unsigned char)(col[2] / ANTI_ALIASING / ANTI_ALIASING)));
			param->i[1]++;
		}
		param->i[0]++;
	}
}