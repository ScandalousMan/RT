#include <rt.h>

double	distance_to_cylindre(t_object *tmp, double *from, double *to)
{
	vec_soustraction(from, ((t_cylindre*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(to) * second_level(cylindre_first_term(tmp, to),
		cylindre_second_term(tmp, to), cylindre_third_term(tmp)));
}

void	update_normal_cylindre(t_object *tmp, t_path *path)
{
	vec_soustraction(path->x, ((t_cylindre*)(tmp->dim))->org, path->n);
	vec_multiply(scalar_product(path->n, ((t_cylindre*)(tmp->dim))->u), ((t_cylindre*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(path->n, tmp->tmp_vec, path->n);
}
