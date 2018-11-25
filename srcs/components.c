#include "rt.h"

double	ft_absdbl(double a)
{
	return a < 0.0 ? -1.0 * a : a;
}

int 		ft_absint(int a)
{
	return a < 0 ? -1 * a : a;
}

void		ft_putvec(double *x)
{
	ft_putdbl(x[0], 4);
	ft_putstr(", ");
	ft_putdbl(x[1], 4);
	ft_putstr(", ");
	ft_putdbl(x[2], 4);
}
