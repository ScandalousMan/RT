#include <rt.h>

double	distance_to_sphere(t_object *tmp, double *from, double *to)
{
	double	a;
	double	d;
	double	norm;
	double	temp[VEC_SIZE];

	d = -1.0;
	norm = vec_norm(to);
	temp[0] = from[0] - ((t_sphere*)(tmp->dim))->center[0];
	temp[1] = from[1] - ((t_sphere*)(tmp->dim))->center[1];
	temp[2] = from[2] - ((t_sphere*)(tmp->dim))->center[2];
	if ((a = second_level(norm * norm,
			2.0 * (to[0] * temp[0] + to[1] * temp[1] + to[2] * temp[2]),
			temp[0] * temp[0] + temp[1] * temp[1] + temp[2] * temp[2] +
			- ((t_sphere*)(tmp->dim))->radius * ((t_sphere*)(tmp->dim))->radius))
			>= 0)
		d = a * norm;
	return (d);
}

void	update_normal_sphere(t_object *tmp, t_path *path)
{
	vec_soustraction(path->valid_x, ((t_sphere*)(tmp->dim))->center, path->valid_n);
}

int		is_inside_sphere(double *pt, t_object *tmp)
{
	if (pt_dist_root(pt, ((t_sphere*)(tmp->dim))->center) > ((t_sphere*)(tmp->dim))->radius * ((t_sphere*)(tmp->dim))->radius)
		return 0;
	return 1;
}
