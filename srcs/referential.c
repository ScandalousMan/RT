#include "rt_objects.h"


void	default_ref_updater(t_object *obj)
{
	obj->ref.i[0] = 1.0f;
	obj->ref.i[1] = 0.0f;
	obj->ref.i[2] = 0.0f;
	obj->ref.j[0] = 0.0f;
	obj->ref.j[1] = 1.0f;
	obj->ref.j[2] = 0.0f;
	obj->ref.k[0] = 0.0f;
	obj->ref.k[1] = 0.0f;
	obj->ref.k[2] = 1.0f;
}

int		are_colinear(double *a, double *b)
{
	if (!vec_norm(a) || !vec_norm(b))
		return (0);
	if (ft_absdbl(scalar_product(a, b)) == vec_norm(a) * vec_norm(b))
		return (1);
	return (0);
}

void	special_ref_updater(double *vec, t_object *obj)
{
	default_ref_updater(obj);
	vec_copy(vec, obj->ref.k);
	if (are_colinear(vec, obj->ref.i))
	{
		vector_product(obj->ref.j, vec, obj->ref.i);
	}
	else
	{
		vector_product(vec, obj->ref.i, obj->ref.j);
		vec_to_unit_norm(obj->ref.j);
		vector_product(obj->ref.j, vec, obj->ref.i);
		vec_to_unit_norm(obj->ref.i);
	}
}
