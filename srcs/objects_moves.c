#include "rt_objects.h"

void	limits_move(t_object *obj, t_param *param)
{
	if (obj && param)
		printf("OK\n");
}

void	reset_moves(t_object *obj)
{
	ft_bzero(&(obj->translation), sizeof(double) * 3);
	ft_bzero(&(obj->rotation), sizeof(double) * 3);
}

void	ref_move(t_object *obj, t_param *param)
{
	if (obj && param)
		printf("OK\n");
}