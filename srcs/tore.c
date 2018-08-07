#include "rt.h"

double	distance_to_tore(t_object *tmp, double *from, double *to)
{
	return ferrari(tore_first_term(to),
		tore_second_term(from, to),
		tore_third_term((t_tore*)(tmp->dim), from, to),
		tore_fourth_term((t_tore*)(tmp->dim), from, to),
		tore_fifth_term((t_tore*)(tmp->dim), from));
}

void	update_normal_tore(t_object *tmp, t_path *path)
{
	if (tmp && path)
		return;
}

int		is_inside_tore(double *pt, t_object *tmp)
{
	return (tmp && pt ? 1 : 0);
}