#include "rt.h"

void	find_intersection(t_param *param, double *from, double *to)
{
	param->current_object = closest_object(param, from, to);
		if (param->current_object)
		{
			vec_multiply(param->obj_d - param->epsilon, param->v, param->x);
			pt_translated(param->eye, param->x, param->x);
			update_normal_vector(param->current_object, param);
		}
}

int		object_color(t_param *param)
{
	double	bright;
	double	diffuse;

	if (param && param->current_object)
	{
		bright = 0.0;
		diffuse = 0.0;
		param->tmp_light = param->lights;
		while (param->tmp_light)
		{
			vec_soustraction(param->tmp_light->src, param->x, param->l);
			vec_to_unit_norm(param->l);
			vec_multiply(-2.0 * scalar_product(param->n, param->v), param->n, param->r);
			pt_translated(param->r, param->v, param->r);
			vec_to_unit_norm(param->r);
			if (!object_intersection(param, param->x, param->tmp_light->src))
			{
				if (scalar_product(param->l, param->n) * param->tmp_light->i > 0.0)
					diffuse += scalar_product(param->l, param->n) * param->tmp_light->i;
				if (param->bright && ft_pow(scalar_product(param->l, param->r), param->bright) * param->tmp_light->i > 0.0)
					bright += ft_pow(scalar_product(param->l, param->r), param->current_object->phong) * param->tmp_light->i;
			}
			param->tmp_light = param->tmp_light->next;
		}
		return color_summer(rgb_ratio(param->current_object->col, 0.2 + param->current_object->kd * diffuse),
			rgb_ratio(16777215, param->current_object->ks * (bright > 1.0 ? 1.0 : bright)));
	}
	return (0);
}

double	*ray_direction(t_param *param, int i, int j)
{
	vec_multiply(param->f, param->look, param->v);
	vec_multiply(((double)HEIGHT * ANTI_ALIASING / 2.0 - (double)i) * 40.0 /
		(double)HEIGHT / ANTI_ALIASING, param->third, param->tmp_vec);
	pt_translated(param->v, param->tmp_vec, param->v);
	vec_multiply(((double)j - (double)WIDTH * ANTI_ALIASING / 2.0) * 40.0 /
		(double)WIDTH / ANTI_ALIASING, param->align, param->tmp_vec);
	pt_translated(param->v, param->tmp_vec, param->v);
	vec_to_unit_norm(param->v);
	return (param->v);
}

int		ray_color(t_param *param, double *from, double *to, int index)
{
	find_intersection(param, from, to);//stocke dans param->current_object
	if (index < MAX_RECURSION)
		return (0);
	else
		return (object_color(param));
}

void	rt_tracer(t_param *param)
{
	int		col[3];
	int		tmp_col;
	int 	alias[2];

	param->i[0] = 0;
	while (param->i[0] < HEIGHT)
	{
		param->i[1] = 1;
		while (param->i[1] < WIDTH)
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
					param->current_object = NULL;
					ray_direction(param,
						ANTI_ALIASING * param->i[0] + alias[0],
						ANTI_ALIASING * param->i[1] + alias[1]);//définit la direction du rayon
					tmp_col = ray_color(param, param->eye, param->v, 0);//définit la couleur du rayon
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
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
}