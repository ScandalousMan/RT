#include "rt_objects.h"

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
		rotation_matrice(0, 0, 45 * sin(object->uv_map[0] * 2.0 * M_PI * 20),
			param);
		matrice_product(param->rot, path->n, path->n);
	}
}
