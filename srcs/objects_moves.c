#include "rt_objects.h"

void	limits_move(double *o, t_object *obj, t_param *param)
{
	t_limit	*tmp;

	tmp = obj->limits;
	while (tmp)
	{
		printf("\n<>\norigin before: %f, %f, %f\n", tmp->plane.ref[0], tmp->plane.ref[1], tmp->plane.ref[2]);
		matrice_product(param->rot, tmp->plane.n, tmp->plane.n);
		pt_translated(o, tmp->plane.ref, tmp->plane.ref);
		printf("\n><\norigin after: %f, %f, %f\n", tmp->plane.ref[0], tmp->plane.ref[1], tmp->plane.ref[2]);
		tmp = tmp->next;
	}
}

void	reset_moves(t_object *obj)
{
	ft_bzero(&(obj->translation), sizeof(double) * 3);
	ft_bzero(&(obj->rotation), sizeof(double) * 3);
}

void	ref_move(t_object *obj, t_param *param)
{
	rotation_matrice(obj->rotation[0], obj->rotation[1], obj->rotation[2], param);
	matrice_product(param->rot, obj->ref.i, obj->ref.i);
	matrice_product(param->rot, obj->ref.j, obj->ref.j);
	matrice_product(param->rot, obj->ref.k, obj->ref.k);
}