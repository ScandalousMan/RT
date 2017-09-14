#include "rt.h"

double	*vision_direction(t_param *param)
{
	vec_multiply(param->f, param->look, param->v);
	vec_multiply(((double)HEIGHT * ANTI_ALIASING / 2.0 - (double)param->i[0]) * 40.0 /
		(double)HEIGHT * ANTI_ALIASING, param->third, param->tmp_vec);

	pt_translated(param->v, param->tmp_vec, param->v);
	vec_multiply(((double)param->i[1] - (double)WIDTH * ANTI_ALIASING / 2.0) * 40.0 /
		(double)WIDTH * ANTI_ALIASING, param->align, param->tmp_vec);
	pt_translated(param->v, param->tmp_vec, param->v);
	vec_to_unit_norm(param->v);
	return (param->v);
}

void	rt_filler(t_param *param)
{
	param->i[0] = 0;
	while (param->i[0] < HEIGHT)
	{
		param->i[1] = 0;
		while (param->i[1] < WIDTH)
		{
			vision_direction(param);
			param->current_object = NULL;
			object_intersection(param, param->eye, param->v);
			if (param->current_object)
				print_obj_point(param);
			param->i[1]++;
		}
		param->i[0]++;
	}
	// ft_putstr("occurrences found :\n");
	// ft_putnbr(i[0]);
	// ft_putchar('\n');
	// ft_putnbr(i[1]);
	// ft_putchar('\n');
	// ft_putnbr(i[2]);
	// ft_putchar('\n');
	// ft_putnbr(i[3]);
	// ft_putchar('\n');
	mlx_put_image_to_window(param->mlx, param->win, param->img, 50, 50);
}