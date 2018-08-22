#include "rt.h"
#include <gsl/gsl_poly.h>

double ft_absdbl(double a)
{
	if (a < 0.0)
		return (-a);
	return (a);
}

double	distance_to_tore(t_object *tmp, double *from, double *to, t_param *param)
{
	gsl_poly_complex_workspace	*w;
	double 											a[5];
	double											z[8];
	double											res;
	int													n;

	w = gsl_poly_complex_workspace_alloc(5);
	a[4] = tore_first_term(to);
	a[3] = tore_second_term(from, to);
	a[2] = tore_third_term((t_tore*)(tmp->dim), from, to);
	a[1] = tore_fourth_term((t_tore*)(tmp->dim), from, to);
	a[0] = tore_fifth_term((t_tore*)(tmp->dim), from);
	if (a[4] != 0.0)
		n = 5;
	else if (a[3] != 0.0)
		n = 4;
	else if (a[2] != 0.0)
		n = 3;
	else if (a[1] != 0.0)
		n = 2;
	else
		return (-1);
	gsl_poly_complex_solve(a, n, w, z);
	if (point_display(param))
		printf("TORE | n=%d | z=[%f,%f,%f,%f] , [%f,%f,%f,%f]\n", n, z[0], z[2], z[4], z[6], z[1], z[3], z[5], z[7]);
	// ajouter dans la structure param et free à la toute fin pour ne pas le faire pour chaque calcul
	gsl_poly_complex_workspace_free(w);
	res = -1;
	if (z[0] > 0 && ft_absdbl(z[1]) <= EPSILON)
		res = z[0];
	if (n > 2 && z[2] > 0.0 && (z[2] < res || res < 0.0) && ft_absdbl(z[3]) <= EPSILON)
		res = z[2];
	if (n > 3 && z[4] > 0.0 && (z[4] < res || res < 0.0) && ft_absdbl(z[5]) <= EPSILON)
		res = z[4];
	if (n > 4 && z[6] > 0.0 && (z[6] < res || res < 0.0) && ft_absdbl(z[7]) <= EPSILON)
		res = z[6];
	return (res);
	// return ferrari(tore_first_term(to),
	// 	tore_second_term(from, to),
	// 	tore_third_term((t_tore*)(tmp->dim), from, to),
	// 	tore_fourth_term((t_tore*)(tmp->dim), from, to),
	// 	tore_fifth_term((t_tore*)(tmp->dim), from));
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
}

int		is_inside_tore(double *pt, t_object *tmp)
{
	return (tmp && pt ? 1 : 0);
}