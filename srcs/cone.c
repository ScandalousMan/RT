#include <rt.h>

double	distance_to_cone(t_object *tmp, double *from, double *to)
{
	vec_soustraction(from, ((t_cone*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(to) * second_level(cone_first_term(tmp, to),
		cone_second_term(tmp, to, tmp->tmp_vec),
		cone_third_term(tmp, tmp->tmp_vec)));
}

void	update_normal_cone(t_object *tmp, t_path *path)
{
	double	norm;

	vec_soustraction(path->x, ((t_cone*)(tmp->dim))->org, path->n);
	norm = vec_norm(path->n);
	vec_multiply(1.0 / scalar_product(path->n, ((t_cone*)(tmp->dim))->u) * norm * norm, ((t_cone*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(path->n, tmp->tmp_vec, path->n);
}

int		is_inside_cone(double *pt, t_object *obj)
{
	return (pt && obj) ? 1 : 0;
}
