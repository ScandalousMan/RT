#include "rt.h"

void	display_sphere(t_object *objs)
{
	ft_putstr("** new sphere **\n");
	ft_putstr("centre : ");
	ft_putvec(((t_sphere*)(objs->parsed))->center);
	ft_putchar('\n');
	ft_putstr("radius : ");
	ft_putnbr(((t_sphere*)(objs->parsed))->radius);
	ft_putchar('\n');	
}