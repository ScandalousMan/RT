#include "rt.h"

double	distance_to_tore(t_object *tmp, double *from, double *to)
{
	double 											a[5];

	ref_change(tmp->ref, to, ((t_tore*)(tmp->dim))->to);
	ref_change(tmp->ref, from, ((t_tore*)(tmp->dim))->from);
	a[4] = tore_first_term(((t_tore*)(tmp->dim))->to);
	a[3] = tore_second_term(((t_tore*)(tmp->dim))->from, ((t_tore*)(tmp->dim))->to);
	a[2] = tore_third_term((t_tore*)(tmp->dim), ((t_tore*)(tmp->dim))->from, ((t_tore*)(tmp->dim))->to);
	a[1] = tore_fourth_term((t_tore*)(tmp->dim), ((t_tore*)(tmp->dim))->from, ((t_tore*)(tmp->dim))->to);
	a[0] = tore_fifth_term((t_tore*)(tmp->dim), ((t_tore*)(tmp->dim))->from);

	return (ferrari(a[4], a[3], a[2], a[1], a[0]));
}

void	update_normal_tore(t_object *tmp, t_path *path)
{
	t_tore *tore;

	tore = ((t_tore*)(tmp->dim));
	vec_soustraction(path->valid_x, tore->center, tore->valid_x);
	ref_change(tmp->ref, tore->valid_x, tore->valid_x);
	path->valid_n[0] = 4.0 * ft_pow(path->valid_x[0], 3.0f) +
		4.0 * tore->valid_x[0] * (tore->valid_x[1] * tore->valid_x[1] + tore->valid_x[2] * tore->valid_x[2] + tore->r1 * tore->r1 - tore->r2 * tore->r2) -
		8.0 * tore->r1 *tore->r1 * tore->valid_x[0];
	path->valid_n[1] = 4.0 * ft_pow(tore->valid_x[1], 3.0f) +
		4.0 * tore->valid_x[1] * (tore->valid_x[0] * tore->valid_x[0] + tore->valid_x[2] * tore->valid_x[2] + tore->r1 * tore->r1 - tore->r2 * tore->r2) -
		8.0 * tore->r1 *tore->r1 * tore->valid_x[1];
	path->valid_n[2] = 4.0 * ft_pow(tore->valid_x[2], 3.0f) +
		4.0 * tore->valid_x[2] * (tore->valid_x[1] * tore->valid_x[1] + tore->valid_x[0] * tore->valid_x[0] + tore->r1 * tore->r1 - tore->r2 * tore->r2);
}

int		is_inside_tore(double *pt, t_object *tmp)
{
	return (tmp && pt ? 1 : 0);
}
