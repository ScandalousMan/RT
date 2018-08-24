#include "rt.h"

// ruban de moebius => y^3  - 2zy^2  + (x^2 + z^2 - a^2) * y - 2xz * (x + a) = 0

double	tore_first_term(double *to)
{
	return (ft_pow((to[0] * to[0] + to[1] * to[1] + to[2] * to[2]), 2));

	// if (to)
	// 	return (0.0);
	// return (0.0);
}

double	tore_second_term(double *from, double *to)
{
	return (4.0 * (to[0] * to[0] + to[1] * to[1] + to[2] * to[2]) *
		(from[0] * to[0] + from[1] * to[1] + from[2] * to[2]));

	// if (from)
	// 	return (to[1] * (to[1] + to[0] - to[2]) * (to[1] - to[2] - to[0]) + 2.0 * to[0] * to[0] * (to[1] - to[2]));
	// return (0);
}

double	tore_third_term(t_tore *obj, double *from, double *to)
{
	return (2.0 * (to[0] * to[0] + to[1] * to[1] + to[2] * to[2]) *
		(from[0] * from[0] + from[1] * from[1] + from[2] * from[2] +
			obj->r1 * obj->r1 - obj->r2 * obj->r2) +
		4.0 * ft_pow(from[0] * to[0] + from[1] * to[1] + from[2] * to[2], 2) -
		4.0 * obj->r1 * obj->r1 * (to[0] * to[0] + to[1] * to[1]));

	// return (to[1] * (to[1] + to[0] - to[2]) * (from[1] - from[0] - from[2] - obj->r1) +
	// 	to[1] * (to[1] - to[0] - to[2]) * (from[1] + from[0] - from[2] + obj->r1) + 
	// 	from[1] * (to[1] - to[0] - to[2]) * (to[1] + to[0] - to[2]) +
	// 	2.0 * to[0] * (to[1] - to[2]) * (from[0] + obj->r1) +
	// 	2.0 * to[0] * to[0] * (from[1] - from[2]) +
	// 	2.0 * to[0] * from[0] * (to[1] - to[2]));
}

double	tore_fourth_term(t_tore *obj, double *from, double *to)
{
	return (4.0 * (from[0] * to[0] + from[1] * to[1] + from[2] * to[2]) *
		(from[0] * from[0] + from[1] * from[1] + from[2] * from[2] +
			obj->r1 * obj->r1 - obj->r2 * obj->r2) -
		8.0 * obj->r1 * obj->r1 * (from[0] * to[0] + from[1] * to[1]));

	// return (to[1] * (from[1] - from[2] + from[0] + obj->r1) * (from[1] - from[2] - from[0] - obj->r1) +
	// 	from[1] * (to[1] - to[2]+ to[0]) * (from[1] - from[2] - from[0] - obj->r1) +
	// 	from[1] * (from[1] - from[2] + from[0] + obj->r1) * (to[1] - to[2] - to[0]) +
	// 	2.0 * to[0] * (to[1] - to[2]) * (from[0] + obj->r1) +
	// 	2.0 * from[0] * (to[1] - to[2]) * (from[0] + obj->r1) +
	// 	2.0 * from[0] * (from[1] - from[2] * to[0]));
}

double	tore_fifth_term(t_tore *obj, double *from)
{
	return (ft_pow(from[0] * from[0] + from[1] * from[1] + from[2] * from[2] +
		obj->r1 * obj->r1 - obj->r2 * obj->r2, 2) -
		4.0 * obj->r1 * obj->r1 * (from[0] * from[0] + from[1] * from[1]));

	// return (from[1] * (from[1] - from[2] + from[0] + obj->r1) * (from[1] - from[2] - from[0] - obj->r1) +
	// 	2.0 * from[0] * (from[1] - from[2]) * (from[0] + obj->r1));
}
