#include "rt.h"

double	distance_to_face1(t_object *tmp, double *from, double *to)
{
	double	res;

	vec_multiply(0.5 * ((t_cube*)(tmp->dim))->h, tmp->ref.i, tmp->tmp_vec);
	pt_translated(((t_cube*)(tmp->dim))->center, tmp->tmp_vec, tmp->tmp_vec);
	res = plane_distance(from, to, tmp->ref.i, tmp->tmp_vec);
	if (res >= 0)
	{
		vec_multiply(res, to, tmp->tmp_vec);
		pt_translated(from, tmp->tmp_vec, tmp->tmp_vec);
		vec_soustraction(tmp->tmp_vec, ((t_cube*)(tmp->dim))->center, tmp->tmp_vec);
		if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.j)) >
			((t_cube*)(tmp->dim))->h / 2.0f ||
			ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.k)) >
			((t_cube*)(tmp->dim))->h / 2.0f)
			res = -1.0f;
	}
	return (res);
}

double	distance_to_face2(t_object *tmp, double *from, double *to)
{
	double	res;

	vec_multiply(0.5 * ((t_cube*)(tmp->dim))->h, tmp->ref.j, tmp->tmp_vec);
	pt_translated(((t_cube*)(tmp->dim))->center, tmp->tmp_vec, tmp->tmp_vec);
	res = plane_distance(from, to, tmp->ref.j, tmp->tmp_vec);
	if (res >= 0)
	{
		vec_multiply(res, to, tmp->tmp_vec);
		pt_translated(from, tmp->tmp_vec, tmp->tmp_vec);
		vec_soustraction(tmp->tmp_vec, ((t_cube*)(tmp->dim))->center, tmp->tmp_vec);
		if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.i)) >
			((t_cube*)(tmp->dim))->h / 2.0f ||
			ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.k)) >
			((t_cube*)(tmp->dim))->h / 2.0f)
			res = -1.0f;
	}
	return (res);
}

double	distance_to_face3(t_object *tmp, double *from, double *to)
{
	double	res;

	vec_multiply(0.5 * ((t_cube*)(tmp->dim))->h, tmp->ref.k, tmp->tmp_vec);
	pt_translated(((t_cube*)(tmp->dim))->center, tmp->tmp_vec, tmp->tmp_vec);
	res = plane_distance(from, to, tmp->ref.k, tmp->tmp_vec);
	if (res >= 0)
	{
		vec_multiply(res, to, tmp->tmp_vec);
		pt_translated(from, tmp->tmp_vec, tmp->tmp_vec);
		vec_soustraction(tmp->tmp_vec, ((t_cube*)(tmp->dim))->center, tmp->tmp_vec);
		if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.j)) >
			((t_cube*)(tmp->dim))->h / 2.0f ||
			ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.i)) >
			((t_cube*)(tmp->dim))->h / 2.0f)
			res = -1.0f;
	}
	return (res);
}

double	distance_to_face4(t_object *tmp, double *from, double *to)
{
	double	res;

	vec_multiply(-0.5 * ((t_cube*)(tmp->dim))->h, tmp->ref.i, tmp->tmp_vec);
	pt_translated(((t_cube*)(tmp->dim))->center, tmp->tmp_vec, tmp->tmp_vec);
	res = plane_distance(from, to, tmp->ref.i, tmp->tmp_vec);
	if (res >= 0)
	{
		vec_multiply(res, to, tmp->tmp_vec);
		pt_translated(from, tmp->tmp_vec, tmp->tmp_vec);
		vec_soustraction(tmp->tmp_vec, ((t_cube*)(tmp->dim))->center, tmp->tmp_vec);
		if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.j)) >
			((t_cube*)(tmp->dim))->h / 2.0f ||
			ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.k)) >
			((t_cube*)(tmp->dim))->h / 2.0f)
			res = -1.0f;
	}
	return (res);
}

double	distance_to_face5(t_object *tmp, double *from, double *to)
{
	double	res;

	vec_multiply(-0.5 * ((t_cube*)(tmp->dim))->h, tmp->ref.j, tmp->tmp_vec);
	pt_translated(((t_cube*)(tmp->dim))->center, tmp->tmp_vec, tmp->tmp_vec);
	res = plane_distance(from, to, tmp->ref.j, tmp->tmp_vec);
	if (res >= 0)
	{
		vec_multiply(res, to, tmp->tmp_vec);
		pt_translated(from, tmp->tmp_vec, tmp->tmp_vec);
		vec_soustraction(tmp->tmp_vec, ((t_cube*)(tmp->dim))->center, tmp->tmp_vec);
		if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.i)) >
			((t_cube*)(tmp->dim))->h / 2.0f ||
			ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.k)) >
			((t_cube*)(tmp->dim))->h / 2.0f)
			res = -1.0f;
	}
	return (res);
}

double	distance_to_face6(t_object *tmp, double *from, double *to)
{
	double	res;

	vec_multiply(-0.5 * ((t_cube*)(tmp->dim))->h, tmp->ref.k, tmp->tmp_vec);
	pt_translated(((t_cube*)(tmp->dim))->center, tmp->tmp_vec, tmp->tmp_vec);
	res = plane_distance(from, to, tmp->ref.k, tmp->tmp_vec);
	if (res >= 0)
	{
		vec_multiply(res, to, tmp->tmp_vec);
		pt_translated(from, tmp->tmp_vec, tmp->tmp_vec);
		vec_soustraction(tmp->tmp_vec, ((t_cube*)(tmp->dim))->center, tmp->tmp_vec);
		if (ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.j)) >
			((t_cube*)(tmp->dim))->h / 2.0f ||
			ft_absdbl(scalar_product(tmp->tmp_vec, tmp->ref.i)) >
			((t_cube*)(tmp->dim))->h / 2.0f)
			res = -1.0f;
	}
	return (res);
}
