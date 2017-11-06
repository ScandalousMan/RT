#include <rt.h>

double	distance_to_plane(t_object *tmp, double *from, double *to)
{
	if (scalar_product(((t_plane*)(tmp->dim))->n, to) == 0.0)
	{
		if (((t_plane*)(tmp->dim))->n[0] * (((t_plane*)(tmp->dim))->ref[0] - from[0]) + ((t_plane*)(tmp->dim))->n[1] * (((t_plane*)(tmp->dim))->ref[1] * from[1]) +
				((t_plane*)(tmp->dim))->n[2] * (((t_plane*)(tmp->dim))->ref[2] - from[2]) == 0.0)
			return (0.0);
		return (-1.0);
	}
	else
		return ((((t_plane*)(tmp->dim))->n[0] * (((t_plane*)(tmp->dim))->ref[0] - from[0]) + ((t_plane*)(tmp->dim))->n[1] *
					(((t_plane*)(tmp->dim))->ref[1] - from[1]) + ((t_plane*)(tmp->dim))->n[2] *
					(((t_plane*)(tmp->dim))->ref[2] - from[2])) / scalar_product(((t_plane*)(tmp->dim))->n, to));
}

void	update_normal_plane(t_object *tmp, t_path *path)
{
	vec_copy(((t_plane*)(tmp->dim))->n, path->n);
	if (scalar_product(path->n, path->v) > 0.0)
		vec_multiply(-1.0, path->n, path->n);
}
