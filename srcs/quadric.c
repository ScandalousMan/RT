#include "rt.h"

double	distance_to_quadric(t_object *tmp, double *from, double *to)
{
	return (vec_norm(to) * second_level(quadric_first_term((t_quadric*)(tmp->dim), to),
		quadric_second_term((t_quadric*)(tmp->dim), from, to), quadric_third_term((t_quadric*)(tmp->dim), from)));
}

void	update_normal_quadric(t_quadric *tmp, t_path *path)
{
	path->valid_n[0] = 2.0 * tmp->a * (path->valid_x[0] - tmp->center[0]) +
		(tmp->d + tmp->b) * (path->valid_x[1] - tmp->center[1]) +
		(tmp->g + tmp->c) * (path->valid_x[2] - tmp->center[2]);
	path->valid_n[1] = 2.0 * tmp->e * (path->valid_x[1] - tmp->center[1]) +
		(tmp->d + tmp->b) * (path->valid_x[0] - tmp->center[0]) +
		(tmp->h + tmp->f) * (path->valid_x[2] - tmp->center[2]);
	path->valid_n[2] = 2.0 * tmp->i * (path->valid_x[2] - tmp->center[2]) +
		(tmp->h + tmp->f) * (path->valid_x[1] - tmp->center[1]) +
		(tmp->g + tmp->c) * (path->valid_x[0] - tmp->center[0]);
}

int		is_inside_quadric(t_object *tmp, t_path *path)
{
	return tmp && path ? 1: 0;
}