#include "rt.h"

double	quadric_first_term(t_quadric *tmp, double *to)
{
	return (tmp->a * to[0] * to[0] + tmp->e * to[1] * to[1] + tmp->i * to[2] * to[2] +
		(tmp->d + tmp->b) * to[0] * to[1] + (tmp->c + tmp->g) * to[0] * to[2] + (tmp->h + tmp->f) * to[1] * to[2]);
}

double	quadric_second_term(t_quadric *tmp, double *from, double *to)
{
	return (2.0 * tmp->a * from[0] * to[0] + 2.0 * tmp->e * from[1] * to[1] + 2.0 * tmp->i * from[2] * to[2] +
		(tmp->d + tmp->b) * (from[0] * to[1] + from[1] * to[0]) + (tmp->c + tmp->g) * (from[0] * to[2] + from[2] * to[0]) + (tmp->h + tmp->f) * (from[1] * to[2] + from[2] * to[1]) -
		to[0] * (2.0 * tmp->a * tmp->center[0] + (tmp->d + tmp->b) * tmp->center[1] + (tmp->c + tmp->g) * tmp->center[2]) - to[1] * (2.0 * tmp->e * tmp->center[1] + (tmp->d + tmp->b) * tmp->center[0] + (tmp->h + tmp->f) * tmp->center[2]) - to[2] * (2.0 * tmp->i * tmp->center[2] + (tmp->c + tmp->g) * tmp->center[0] + (tmp->h + tmp->f) * tmp->center[1]));
}

double	quadric_third_term(t_quadric *tmp, double *from)
{
	return (tmp->a * from[0] * from[0] + tmp->e * from[1] * from[1] + tmp->i * from[2] * from[2] +
		(tmp->d + tmp->b) * from[0] * from[1] + (tmp->c + tmp->g) * from[0] * from[2] + (tmp->h + tmp->f) * from[1] * from[2] -
		from[0] * (2.0 * tmp->a * tmp->center[0] + (tmp->d + tmp->b) * tmp->center[1] + (tmp->c + tmp->g) * tmp->center[2]) - from[1] * (2.0 * tmp->e * tmp->center[1] + (tmp->d + tmp->b) * tmp->center[0] + (tmp->h + tmp->f) * tmp->center[2]) - from[2] * (2.0 * tmp->i * tmp->center[2] + (tmp->c + tmp->g) * tmp->center[0] + (tmp->h + tmp->f) * tmp->center[1]) +
		tmp->a * tmp->center[0] * tmp->center[0] + tmp->e * tmp->center[1] * tmp->center[1] + tmp->i * tmp->center[2] * tmp->center[2] +
		(tmp->d + tmp->b) * tmp->center[0] * tmp->center[1] + (tmp->c + tmp->g) * tmp->center[0] * tmp->center[2] + (tmp->h + tmp->f) * tmp->center[1] * tmp->center[2] - tmp->r * tmp->r);
}
