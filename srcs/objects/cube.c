#include "rt.h"

double	distance_to_cube(t_object *tmp, double *from, double *to, t_path *path)
{
	double	res;
	double	tmp_res;

	tmp_res = -1.0f;
	if ((res = distance_to_face1(tmp, from, to)) >= 0.0f)
		vec_copy(tmp->ref.i, path->valid_n);
	if ((tmp_res = distance_to_face2(tmp, from, to)) >= 0 && tmp_res < res)
	{
		res = tmp_res;
		vec_copy(tmp->ref.j, path->valid_n);
	}
	if ((tmp_res = distance_to_face3(tmp, from, to)) >= 0 && tmp_res < res)
	{
		res = tmp_res;
		vec_copy(tmp->ref.k, path->valid_n);
	}
	if ((tmp_res = distance_to_face4(tmp, from, to)) >= 0 && tmp_res < res)
	{
		res = tmp_res;
		vec_multiply(-1.0f, tmp->ref.i, path->valid_n);
	}
	if ((tmp_res = distance_to_face5(tmp, from, to)) >= 0 && tmp_res < res)
	{
		res = tmp_res;
		vec_multiply(-1.0f, tmp->ref.j, path->valid_n);
	}
	if ((tmp_res = distance_to_face6(tmp, from, to)) >= 0 && tmp_res < res)
	{
		res = tmp_res;
		vec_multiply(-1.0f, tmp->ref.k, path->valid_n);
	}
	return (res);
}

int		is_inside_cube(double *pt, t_object *tmp)
{
	return (tmp && pt ? 1 : 0);
}
