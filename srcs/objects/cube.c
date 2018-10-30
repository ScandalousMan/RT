#include "rt.h"

double	distance_to_cube(t_object *tmp, double *from, double *to)
{
	double	res;
	double	tmp_res;

	tmp_res = -1.0f;
	res = -1.0f;
	if ((res = distance_to_face1(tmp, from, to)) >= 0.0f)
		vec_copy(tmp->ref.i, ((t_cube*)(tmp->dim))->n);
	if ((tmp_res = distance_to_face2(tmp, from, to)) >= 0 &&
		(tmp_res < res || res < 0.0f))
	{
		res = tmp_res;
		vec_copy(tmp->ref.j, ((t_cube*)(tmp->dim))->n);
	}
	if ((tmp_res = distance_to_face3(tmp, from, to)) >= 0 &&
		(tmp_res < res || res < 0.0f))
	{
		res = tmp_res;
		vec_copy(tmp->ref.k, ((t_cube*)(tmp->dim))->n);
	}
	if ((tmp_res = distance_to_face4(tmp, from, to)) >= 0.0f &&
		(tmp_res < res || res < 0.0f))
	{
		res = tmp_res;
		vec_multiply(-1.0f, tmp->ref.i, ((t_cube*)(tmp->dim))->n);
	}
	if ((tmp_res = distance_to_face5(tmp, from, to)) >= 0 &&
		(tmp_res < res || res < 0.0f))
	{
		res = tmp_res;
		vec_multiply(-1.0f, tmp->ref.j, ((t_cube*)(tmp->dim))->n);
	}
	if ((tmp_res = distance_to_face6(tmp, from, to)) >= 0 &&
		(tmp_res < res || res < 0.0f))
	{
		res = tmp_res;
		vec_multiply(-1.0f, tmp->ref.k, ((t_cube*)(tmp->dim))->n);
	}
	return (res);
}

void	update_normal_cube(t_object *tmp, t_path *path)
{
	vec_copy(((t_cube*)(tmp->dim))->n, path->valid_n);
}

int		is_inside_cube(double *pt, t_object *tmp)
{
	vec_soustraction(pt, ((t_cube*)(tmp->dim))->center, tmp->tmp_vec);
	if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.i)) >
		((t_cube*)(tmp->dim))->h / 2.0f ||
		ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.j)) >
		((t_cube*)(tmp->dim))->h / 2.0f ||
		ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.k)) >
		((t_cube*)(tmp->dim))->h / 2.0f)
		return (0);
	return (1);
}

double *cube_position(double *pt, t_object *obj)
{
	double s[3];

	vec_soustraction(pt, ((t_cube*)(obj->dim))->center, obj->tmp_vec);
	s[0] = scalar_product(obj->tmp_vec, obj->ref.i);
	s[1] = scalar_product(obj->tmp_vec, obj->ref.j);
	s[2] = scalar_product(obj->tmp_vec, obj->ref.k);
	if (ft_absdbl(s[0]) > ft_absdbl(s[1]) &&
		ft_absdbl(s[0]) > ft_absdbl(s[2]))
	{
		obj->uv_map[0] = (s[1] + ((t_cube*)(obj->dim))->h / 2.0f) / ((t_cube*)(obj->dim))->h;
		obj->uv_map[1] = (s[2] + ((t_cube*)(obj->dim))->h / 2.0f) / ((t_cube*)(obj->dim))->h;
	}
	else if (ft_absdbl(s[1]) > ft_absdbl(s[0]) &&
		ft_absdbl(s[1]) > ft_absdbl(s[2]))
	{
		obj->uv_map[0] = (s[2] + ((t_cube*)(obj->dim))->h / 2.0f) / ((t_cube*)(obj->dim))->h;
		obj->uv_map[1] = (s[0] + ((t_cube*)(obj->dim))->h / 2.0f) / ((t_cube*)(obj->dim))->h;
	}
	else
	{
		obj->uv_map[0] = (s[0] + ((t_cube*)(obj->dim))->h / 2.0f) / ((t_cube*)(obj->dim))->h;
		obj->uv_map[1] = (s[1] + ((t_cube*)(obj->dim))->h / 2.0f) / ((t_cube*)(obj->dim))->h;
	}
	return (obj->uv_map);
}
