#include <rt.h>

double	distance_to_cylindre(t_object *tmp, double *from, double *to)
{
	vec_soustraction(from, ((t_cylindre*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(to) * second_level(cylindre_first_term(tmp, to),
		cylindre_second_term(tmp, to), cylindre_third_term(tmp)));
}

void	update_normal_cylindre(t_object *tmp, t_path *path)
{
	vec_soustraction(path->valid_x, ((t_cylindre*)(tmp->dim))->org, path->valid_n);
	vec_multiply(scalar_product(path->valid_n, ((t_cylindre*)(tmp->dim))->u), ((t_cylindre*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(path->valid_n, tmp->tmp_vec, path->valid_n);
}

int		is_inside_cylindre(t_object *tmp, t_path *path)
{
	update_normal_cylindre(tmp, path);
	return (vec_norm(path->valid_n) > ((t_cylindre*)(tmp->dim))->radius) ? 0 : 1;
}
