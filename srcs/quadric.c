#include <rt.h>

double	distance_to_quadric(t_object *tmp, double *from, double *to)
{
	return (vec_norm(to) * second_level(cylindre_first_term(tmp, to),
		cylindre_second_term(tmp, from, to), cylindre_third_term(tmp, from)));
}

void	update_normal_quadric(t_object *tmp, t_path *path)
{

}

int		is_inside_quadric(t_object *tmp, t_path *path)
{
	return tmp && path ? 1: 0;
}