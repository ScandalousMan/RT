#include "rt.h"

double	cone_first_term(t_object *tmp, double *to)
{
	if (tmp)
	return (scalar_product(to, to) - ((1.0 + tan(((t_cone*)(tmp->dim))->angle) *
			tan(((t_cone*)(tmp->dim))->angle)) *
			scalar_product(to, ((t_cone*)(tmp->dim))->u) *
			scalar_product(to, ((t_cone*)(tmp->dim))->u)));
	return (0);
}

double	cone_second_term(t_object *tmp, double *to, double *x)
{
	if (tmp)
	return (2.0 * (scalar_product(to, x) - (1.0 +
		tan(((t_cone*)(tmp->dim))->angle) *
		tan(((t_cone*)(tmp->dim))->angle)) *
		scalar_product(to, ((t_cone*)(tmp->dim))->u) *
		scalar_product(x, ((t_cone*)(tmp->dim))->u)));
	return (0);
}

double	cone_third_term(t_object *tmp, double *x)
{
	if (tmp)
	return (scalar_product(x, x)
	 - (1.0 + tan(((t_cone*)(tmp->dim))->angle) *
		tan(((t_cone*)(tmp->dim))->angle)) *
		scalar_product(x, ((t_cone*)(tmp->dim))->u) *
		scalar_product(x, ((t_cone*)(tmp->dim))->u));
	return (0);
}

void		display_cone(t_object *objs)
{
	ft_putstr("** new cone **\n");
	ft_putstr("origin : ");
	ft_putvec(((t_cone*)(objs->parsed))->org);
	ft_putchar('\n');
	ft_putstr("vector : ");
	ft_putvec(((t_cone*)(objs->parsed))->u);
	ft_putchar('\n');
	ft_putstr("angle : ");
	ft_putnbr(((t_cone*)(objs->parsed))->angle);
	ft_putchar('\n');
}
