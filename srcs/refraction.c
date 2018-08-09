#include "rt.h"

int	snell_descartes(t_path *path1, t_path *path2)
{
	if (path1->inside_obj_n == path2->inside_obj_n)
	{
		vec_copy(path1->v, path2->v);
		return (1);
	}
	if (scalar_product(path1->v, path1->n) == 0.0 ||
		ABS(path1->inside_obj_n / path2->inside_obj_n * sin(acos(scalar_product(path1->v, path1->n)))) >= 1.0)
		return (0);
	vec_multiply(1.0 / scalar_product(path1->v, path1->n), path1->v, path2->v);
	vec_soustraction(path1->n, path2->v, path2->v);
	vec_to_unit_norm(path2->v);
	vec_multiply(tan(asin(path1->inside_obj_n / path2->inside_obj_n * sin(acos(scalar_product(path1->v, path1->n))))),
		path2->v, path2->v);
	vec_soustraction(path2->v, path1->n, path2->v);
	vec_to_unit_norm(path2->v);
	return (1);
}