#include "rt_objects.h"

void		define_refracted_n(t_path *path1, t_path *path2)
{
	if (path1->current_object->type == RTPLAN)
		path2->inside_obj = path1->inside_obj;
	else if (path1->inside_obj != NULL)
		path2->inside_obj = NULL;
	else
		path2->inside_obj = path1->current_object;
}

double	get_index_n(t_path *path)
{
	if (path->inside_obj)
		return path->inside_obj->index;
	return (1.0);
}

int			snell_descartes(double n1, double n2, t_path *path1, t_path *path2)
{
	if (n1 == n2)
	{
		vec_copy(path1->v, path2->v);
		return (1);
	}
	if (scalar_product(path1->v, path1->n) == 0.0 ||
		ft_absdbl(n1 / n2 * sin(acos(scalar_product(path1->v, path1->n)))) >= 1.0)
		return (0);
	vec_multiply(1.0 / scalar_product(path1->v, path1->n), path1->v, path2->v);
	vec_soustraction(path1->n, path2->v, path2->v);
	vec_to_unit_norm(path2->v);
	vec_multiply(tan(asin(n1 / n2 * sin(acos(scalar_product(path1->v, path1->n))))),
		path2->v, path2->v);
	vec_soustraction(path2->v, path1->n, path2->v);
	vec_to_unit_norm(path2->v);
	return (1);
}