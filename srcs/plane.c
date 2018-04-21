#include <rt.h>

double	plane_distance(double *from, double *to, double *n, double *ref)
{
	if (scalar_product(n, to) == 0.0)
	{
		if (n[0] * (ref[0] - from[0]) + n[1] * (ref[1] * from[1]) +
				n[2] * (ref[2] - from[2]) == 0.0)
			return (0.0);
		return (-1.0);
	}
	else
		return ((n[0] * (ref[0] - from[0]) + n[1] * (ref[1] - from[1]) +
			n[2] * (ref[2] - from[2])) / scalar_product(n, to));
}

double	distance_to_plane(t_object *tmp, double *from, double *to)
{
	return plane_distance(from, to, ((t_plane*)(tmp->dim))->n, ((t_plane*)(tmp->dim))->ref);
}

void	update_normal_plane(t_object *tmp, t_path *path)
{
	vec_copy(((t_plane*)(tmp->dim))->n, path->valid_n);
	if (scalar_product(path->valid_n, path->v) > 0.0)
		vec_multiply(-1.0, path->valid_n, path->valid_n);
}

int		is_inside_plane(t_object *tmp, t_path *path)
{
	return (tmp && path) ? 1 : 0;
}

int		is_in_limit(double *pt, t_limit *limit)
{
	double tmp[3];
 	vec_soustraction(pt, limit->plane.ref, tmp);
	if (scalar_product(tmp, limit->plane.n) > 0)
		return 0;
	return 1;
}
