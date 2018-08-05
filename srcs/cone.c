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

	vec_soustraction(path->valid_x, ((t_cone*)(tmp->dim))->org, path->valid_n);
	norm = vec_norm(path->valid_n);
	vec_multiply(1.0 / scalar_product(path->valid_n, ((t_cone*)(tmp->dim))->u) * norm * norm, ((t_cone*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(path->valid_n, tmp->tmp_vec, path->valid_n);
}

int		is_inside_cone(t_object *tmp, t_path *path)
{
	vec_soustraction(path->valid_x, ((t_cone*)(tmp->dim))->org, path->valid_n);
	vec_multiply(scalar_product(path->valid_n, ((t_cone*)(tmp->dim))->u), ((t_cone*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(path->valid_n, tmp->tmp_vec, path->valid_n);
	return tan(((t_cone*)(tmp->dim))->angle) * tan(((t_cone*)(tmp->dim))->angle) * vec_norm(tmp->tmp_vec) * vec_norm(tmp->tmp_vec) > vec_norm(path->valid_n) * vec_norm(path->valid_n) ? 1 : 0;
}

int		is_inside_cone(double *pt, t_object *obj)
{
	vec_soustraction(pt, ((t_cone*)(obj->dim))->org, obj->tmp_vec);
	if (vec_norm(obj->tmp_vec) == 0 || acos(ABS(scalar_product(obj->tmp_vec, ((t_cone*)(obj->dim))->u)) / vec_norm(obj->tmp_vec)) <= ((t_cone*)(obj->dim))->angle)
		return 1;
	return 0;
}
