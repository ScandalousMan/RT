#include "rt.h"

void	display_objects(t_param *param)
{
	param->tmp_object = param->objects;
	while (param->tmp_object)
	{
		ft_putstr("\n***************\n");
		if (param->tmp_object->type == 1)
		{
			ft_putstr("** nouvelle sphere **\n");
			ft_putstr("centre : ");
			ft_putvec(((t_sphere*)(param->tmp_object->dim))->center);
			ft_putchar('\n');
			ft_putstr("rayon : ");
			ft_putnbr(((t_sphere*)(param->tmp_object->dim))->radius);
			ft_putchar('\n');
		}
		if (param->tmp_object->type == 2)
		{
			ft_putstr("** nouveau plan **\n");
			ft_putstr("point : ");
			ft_putvec(((t_plane*)(param->tmp_object->dim))->ref);
			ft_putchar('\n');
			ft_putstr("normale : ");
			ft_putvec(((t_plane*)(param->tmp_object->dim))->n);
			ft_putchar('\n');
		}
		if (param->tmp_object->type == 3)
		{
			ft_putstr("** nouveau cone **\n");
			ft_putstr("origine : ");
			ft_putvec(((t_cone*)(param->tmp_object->dim))->org);
			ft_putchar('\n');
			ft_putstr("vecteur : ");
			ft_putvec(((t_cone*)(param->tmp_object->dim))->u);
			ft_putchar('\n');
			ft_putstr("angle : ");
			ft_putnbr(((t_cone*)(param->tmp_object->dim))->angle);
			ft_putchar('\n');
		}
		if (param->tmp_object->type == 4)
		{
			ft_putstr("** nouveau cylindre **\n");
			ft_putstr("origine : ");
			ft_putvec(((t_cylindre*)(param->tmp_object->dim))->org);
			ft_putchar('\n');
			ft_putstr("normale : ");
			ft_putvec(((t_cylindre*)(param->tmp_object->dim))->u);
			ft_putchar('\n');
			ft_putstr("rayon : ");
			ft_putnbr(((t_cylindre*)(param->tmp_object->dim))->radius);
			ft_putchar('\n');
		}
		ft_putnbr(param->tmp_object->num);
		ft_putstr("\ncolor = ");
		ft_putnbr(param->tmp_object->col);
		ft_putstr("\n***************\n");
		param->tmp_object = param->tmp_object->next;
	}
}

int	point_display(t_param *param)
{
	return (param->i[0] == 150 && param->i[1] == 225);
}