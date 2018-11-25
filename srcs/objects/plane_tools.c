#include "rt_objects.h"

int		is_inside_plane(double *pt, t_object *tmp)
{
	vec_soustraction(pt, ((t_plane*)(tmp->dim))->ref, tmp->tmp_vec);
	return scalar_product(tmp->tmp_vec, ((t_plane*)(tmp->dim))->n) == 0.0 ? 1 : 0;
}

int		is_in_limit(double *pt, t_limit *limit)
{
	double tmp[3];

 	vec_soustraction(pt, limit->plane.ref, tmp);
	if (scalar_product(tmp, limit->plane.n) > 0.0)
		return (0);
	return (1);
}

int		is_in_limits(double *pt, t_object *obj, t_limit *limit)
{
	t_limit *tmp;

	tmp = obj->limits;
	while (tmp)
	{
		if (tmp != limit && !is_in_limit(pt, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}