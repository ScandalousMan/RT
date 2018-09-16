#include "rt.h"
#include <gsl/gsl_poly.h>

double	distance_to_tore(t_object *tmp, double *from, double *to, t_param *param)
{
	gsl_poly_complex_workspace	*w;
	double 											a[5];
	double											z[8];
	double											res;

	// sim_matrice_rotation(((t_tore*)(tmp->dim))->axis, ((t_tore*)(tmp->dim))->axis, param);
	// matrice_product(param->rot, to, ((t_tore*)(tmp->dim))->to);
	// matrice_product(param->rot, from, ((t_tore*)(tmp->dim))->from);

	vec_copy(to, ((t_tore*)(tmp->dim))->to);
	vec_copy(from, ((t_tore*)(tmp->dim))->from);
	w = gsl_poly_complex_workspace_alloc(5);
	a[4] = tore_first_term(((t_tore*)(tmp->dim))->to);
	a[3] = tore_second_term(((t_tore*)(tmp->dim))->from, ((t_tore*)(tmp->dim))->to);
	a[2] = tore_third_term((t_tore*)(tmp->dim), ((t_tore*)(tmp->dim))->from, ((t_tore*)(tmp->dim))->to);
	a[1] = tore_fourth_term((t_tore*)(tmp->dim), ((t_tore*)(tmp->dim))->from, ((t_tore*)(tmp->dim))->to);
	a[0] = tore_fifth_term((t_tore*)(tmp->dim), ((t_tore*)(tmp->dim))->from);
	gsl_poly_complex_solve(a, 5, w, z);
	if (point_display(param))
		printf("TORE\n");
	gsl_poly_complex_workspace_free(w);
	res = -1;
	if (z[0] > 0 && ft_absdbl(z[1]) <= EPSILON)
		res = z[0];
	if (z[2] > 0.0 && (z[2] < res || res < 0.0) && ft_absdbl(z[3]) <= EPSILON)
		res = z[2];
	if (z[4] > 0.0 && (z[4] < res || res < 0.0) && ft_absdbl(z[5]) <= EPSILON)
		res = z[4];
	if (z[6] > 0.0 && (z[6] < res || res < 0.0) && ft_absdbl(z[7]) <= EPSILON)
		res = z[6];
	return (res);
}

void	update_normal_tore(t_tore *tmp, t_path *path)
{
	path->valid_n[0] = 4.0 * ft_pow(path->valid_x[0], 3) +
		4.0 * path->valid_x[0] * (path->valid_x[1] * path->valid_x[1] + path->valid_x[2] * path->valid_x[2] + tmp->r1 * tmp->r1 - tmp->r2 * tmp->r2) -
		8.0 * tmp->r1 *tmp->r1 * path->valid_x[0];
	path->valid_n[1] = 4.0 * ft_pow(path->valid_x[1], 3) +
		4.0 * path->valid_x[1] * (path->valid_x[0] * path->valid_x[0] + path->valid_x[2] * path->valid_x[2] + tmp->r1 * tmp->r1 - tmp->r2 * tmp->r2) -
		8.0 * tmp->r1 *tmp->r1 * path->valid_x[1];
	path->valid_n[2] = 4.0 * ft_pow(path->valid_x[2], 3) +
		4.0 * path->valid_x[2] * (path->valid_x[1] * path->valid_x[1] + path->valid_x[0] * path->valid_x[0] + tmp->r1 * tmp->r1 - tmp->r2 * tmp->r2);

	// path->valid_n[0] = 2.0 * path->valid_x[0] * path->valid_x[1] - 2.0 * path->valid_x[2] * tmp->r1 - 4.0 * path->valid_x[0] * path->valid_x[2];
	// path->valid_n[1] = 3.0 * path->valid_x[1] * path->valid_x[1] - 4.0 * path->valid_x[2] * path->valid_x[1] + path->valid_x[0] * path->valid_x[0] + path->valid_x[2] * path->valid_x[2] - tmp->r1 * tmp->r1;
	// path->valid_n[2] = -2.0 * path->valid_x[1] * path->valid_x[1] + 2.0 * path->valid_x[1] * path->valid_x[2] - 2.0 * path->valid_x[0] * path->valid_x[0];
}

int		is_inside_tore(double *pt, t_object *tmp)
{
	return (tmp && pt ? 1 : 0);
}
