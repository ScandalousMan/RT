#include "rt.h"

double	tore_first_term(double *to)
{
	// return (ft_pow(to[0], 4) + ft_pow(to[1], 4) + ft_pow(to[2], 4) +
	// 	2.0 * (to[0] * to[0] * to[1] * to[1]) +
	// 	2.0 * (to[1] * to[1] * to[2] * to[2]) +
	// 	2.0 * (to[2] * to[2] * to[0] * to[0]));
	return (ft_pow((to[0] * to[0] + to[1] * to[1] + to[2] * to[2]), 2));
}

double	tore_second_term(double *from, double *to)
{
	// return (4.0 * (ft_pow(to[0], 3) * from[0] + ft_pow(to[1], 3) * from[1] + ft_pow(to[2], 3) * from[2] +
	// 	from[0] * to[0] * to[1] * to[1] + from[1] * to[1] * to[0] * to[0] +
	// 	from[1] * to[1] * to[2] * to[2] + from[2] * to[2] * to[1] * to[1] +
	// 	from[2] * to[2] * to[0] * to[0] + from[0] * to[0] * to[2] * to[2]));
	return (4.0 * (to[0] * to[0] + to[1] * to[1] + to[2] * to[2]) * (from[0] * to[0] + from[1] * to[1] + from[2] * to[2]));
}

double	tore_third_term(t_tore *obj, double *from, double *to)
{
	// return (6.0 * from[0] * from[0] * to[0] * to[0] + 6.0 * from[1] * from[1] * to[1] * to[1] + 6.0 * from[2] * from[2] * to[2] * to[2] +
	// 	2.0 * (from[0] * from[0] * to[1] * to[1] + from[1] * from[1] * to[0] * to[0] +
	// 		from[1] * from[1] * to[2] * to[2] + from[2] * from[2] * to[1] * to[1] +
	// 		from[2] * from[2] * to[0] * to[0] + from[0] * from[0] * to[2] * to[2]) +
	// 	8.0 * (from[0] * from[1] * to[0] * to[1] + from[1] * from[2] * to[1] * to[2] + from[2] * from[0] * to[2] * to[0]) +
	// 	2.0 * (to[2] * to[2] * (obj->r1 * obj->r1 - obj->r2 * obj->r2) -
	// 		(obj->r1 * obj->r1 + obj->r2 * obj->r2) * (to[0] * to[0] + to[1] * to[1])));
	return (2.0 * (to[0] * to[0] + to[1] * to[1] + to[2] * to[2]) * (from[0] * from[0] + from[1] * from[1] + from[2] * from[2] + obj->r1 * obj->r1 - obj->r2 * obj->r2) +
		4.0 * ft_pow(from[0] * to[0] + from[1] * to[1] + from[2] * to[2], 2) - 4.0 * obj->r1 * obj->r1 * (to[0] * to[0] + to[1] * to[1]));
}

double	tore_fourth_term(t_tore *obj, double *from, double *to)
{
	// return (4.0 * (ft_pow(from[0], 3) * to[0] + ft_pow(from[1], 3) * to[1] + ft_pow(from[2], 3) * to[2] +
	// 	from[0] * from[0] * from[1] * to[1] + from[1] * from[1] * from[0] * to[0] +
	// 	from[1] * from[1] * from[2] * to[2] + from[2] * from[2] * from[1] * to[1] +
	// 	from[2] * from[2] * from[0] * to[0] + from[0] * from[0] * from[2] * to[2] +
	// 	(obj->r1 * obj->r1 - obj->r2 * obj->r2) * from[2] * to[2] -
	// 	(obj->r1 * obj->r1 + obj->r2 * obj->r2) * (from[0] * to[0] + from[1] * to[1])));
	return (4.0 * (from[0] * to[0] + from[1] * to[1] + from[2] * to[2]) * (from[0] * from[0] + from[1] * from[1] + from[2] * from[2] + obj->r1 * obj->r1 - obj->r2 * obj->r2) -
		8.0 * obj->r1 * obj->r1 * (from[0] * to[0] + from[1] * to[1]));
}

double	tore_fifth_term(t_tore *obj, double *from)
{
	// return (ft_pow(from[0], 4) + ft_pow(from[1], 4) + ft_pow(from[2], 4) +
	// 	2.0 * (from[0] * from[0] * from[1] * from[1] + from[1] * from[1] * from[2] * from[2] + from[2] * from[2] * from[0] * from[0] +
	// 		(obj->r1 * obj->r1 - obj->r2 * obj->r2) * from[2] * from[2] -
	// 		(obj->r1 * obj->r1 + obj->r2 * obj->r2) * (from[0] * from[0] + from[1] * from[1])));
	return (ft_pow(from[0] * from[0] + from[1] * from[1] + from[2] * from[2] + obj->r1 * obj->r1 - obj->r2 * obj->r2, 2) -
		4.0 * obj->r1 * obj->r1 * (from[0] * from[0] + from[1] * from[1]));
}