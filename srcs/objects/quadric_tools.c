#include "rt.h"

double	quadric_first_term(t_quadric *tmp, double *to)
{
	return (tmp->a * to[0] * to[0] + tmp->e * to[1] * to[1] +
		tmp->i * to[2] * to[2] + (tmp->d + tmp->b) * to[0] * to[1] +
		(tmp->c + tmp->g) * to[0] * to[2] + (tmp->h + tmp->f) * to[1] * to[2]);
}

double	quadric_second_term(t_quadric *tmp, double *from, double *to)
{
	return (2.0 * tmp->a * from[0] * to[0] + 2.0 * tmp->e * from[1] * to[1] +
		2.0 * tmp->i * from[2] * to[2] +
		(tmp->d + tmp->b) * (from[0] * to[1] + from[1] * to[0]) +
		(tmp->c + tmp->g) * (from[0] * to[2] + from[2] * to[0]) +
		(tmp->h + tmp->f) * (from[1] * to[2] + from[2] * to[1]) -
		to[0] * (2.0 * tmp->a * tmp->center[0] + (tmp->d + tmp->b) *
			tmp->center[1] + (tmp->c + tmp->g) * tmp->center[2]) -
		to[1] * (2.0 * tmp->e * tmp->center[1] + (tmp->d + tmp->b) *
			tmp->center[0] + (tmp->h + tmp->f) * tmp->center[2]) - to[2] *
		(2.0 * tmp->i * tmp->center[2] + (tmp->c + tmp->g) * tmp->center[0] +
			(tmp->h + tmp->f) * tmp->center[1]));
}

double	quadric_third_term(t_quadric *tmp, double *from)
{
	return (tmp->a * from[0] * from[0] + tmp->e * from[1] * from[1] +
		tmp->i * from[2] * from[2] + (tmp->d + tmp->b) * from[0] * from[1] +
		(tmp->c + tmp->g) * from[0] * from[2] +
		(tmp->h + tmp->f) * from[1] * from[2] -
		from[0] * (2.0 * tmp->a * tmp->center[0] + (tmp->d + tmp->b) *
			tmp->center[1] + (tmp->c + tmp->g) * tmp->center[2]) -
		from[1] * (2.0 * tmp->e * tmp->center[1] + (tmp->d + tmp->b) *
			tmp->center[0] + (tmp->h + tmp->f) * tmp->center[2]) -
		from[2] * (2.0 * tmp->i * tmp->center[2] + (tmp->c + tmp->g) *
			tmp->center[0] + (tmp->h + tmp->f) * tmp->center[1]) +
		tmp->a * tmp->center[0] * tmp->center[0] +
		tmp->e * tmp->center[1] * tmp->center[1] +
		tmp->i * tmp->center[2] * tmp->center[2] +
		(tmp->d + tmp->b) * tmp->center[0] * tmp->center[1] +
		(tmp->c + tmp->g) * tmp->center[0] * tmp->center[2] +
		(tmp->h + tmp->f) * tmp->center[1] * tmp->center[2] - tmp->r * tmp->r);
}

void	display_quadric(t_object *objs)
{
	ft_putstr("** new quadric **\n");
	ft_putstr("centre : ");
	ft_putvec(((t_quadric*)(objs->parsed))->center);
	ft_putstr("\na: ");
	ft_putdbl(((t_quadric*)(objs->parsed))->a, 4);
	ft_putstr("\nb: ");
	ft_putdbl(((t_quadric*)(objs->parsed))->b, 4);
	ft_putstr("\nc: ");
	ft_putdbl(((t_quadric*)(objs->parsed))->c, 4);
	ft_putstr("\nd: ");
	ft_putdbl(((t_quadric*)(objs->parsed))->d, 4);
	ft_putstr("\ne: ");
	ft_putdbl(((t_quadric*)(objs->parsed))->e, 4);
	ft_putstr("\nf: ");
	ft_putdbl(((t_quadric*)(objs->parsed))->f, 4);
	ft_putstr("\ng: ");
	ft_putdbl(((t_quadric*)(objs->parsed))->g, 4);
	ft_putstr("\nh: ");
	ft_putdbl(((t_quadric*)(objs->parsed))->h, 4);
	ft_putstr("\ni: ");
	ft_putdbl(((t_quadric*)(objs->parsed))->i, 4);
	ft_putstr("\nr: ");
	ft_putdbl(((t_quadric*)(objs->parsed))->r, 4);
	ft_putchar('\n');
}
