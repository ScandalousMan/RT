#include "rt.h"

void	display_objects(t_param *param)
{
	t_object *objs = param->objects;
	while (objs)
	{
		ft_putstr("\n***************\n");
		if (objs->type == 1)
		{
			ft_putstr("** nouvelle sphere **\n");
			ft_putstr("centre : ");
			ft_putvec(((t_sphere*)(objs->dim))->center);
			ft_putchar('\n');
			ft_putstr("rayon : ");
			ft_putnbr(((t_sphere*)(objs->dim))->radius);
			ft_putchar('\n');
		}
		if (objs->type == 2)
		{
			ft_putstr("** nouveau plan **\n");
			ft_putstr("point : ");
			ft_putvec(((t_plane*)(objs->dim))->ref);
			ft_putchar('\n');
			ft_putstr("normale : ");
			ft_putvec(((t_plane*)(objs->dim))->n);
			ft_putchar('\n');
		}
		if (objs->type == 3)
		{
			ft_putstr("** nouveau cone **\n");
			ft_putstr("origine : ");
			ft_putvec(((t_cone*)(objs->dim))->org);
			ft_putchar('\n');
			ft_putstr("vecteur : ");
			ft_putvec(((t_cone*)(objs->dim))->u);
			ft_putchar('\n');
			ft_putstr("angle : ");
			ft_putnbr(((t_cone*)(objs->dim))->angle);
			ft_putchar('\n');
		}
		if (objs->type == 4)
		{
			ft_putstr("** nouveau cylindre **\n");
			ft_putstr("origine : ");
			ft_putvec(((t_cylindre*)(objs->dim))->org);
			ft_putchar('\n');
			ft_putstr("normale : ");
			ft_putvec(((t_cylindre*)(objs->dim))->u);
			ft_putchar('\n');
			ft_putstr("rayon : ");
			ft_putnbr(((t_cylindre*)(objs->dim))->radius);
			ft_putchar('\n');
		}
		ft_putnbr(objs->num);
		ft_putstr("\ncolor = ");
		ft_putnbr(objs->col);
		ft_putstr("\nmiroir:");
		ft_putdbl(objs->reflection, 4);
		ft_putstr("\n***************\n");
		objs = objs->next;
	}
}

void	display_lights(t_param *param)
{
	param->tmp_light = param->lights;
	while (param->tmp_light)
	{
		ft_putstr("light detected,#");
		ft_putnbr(param->tmp_light->num);
		ft_putchar('\n');
		ft_putnbr(param->tmp_light->type);
		ft_putendl("");
		ft_putvec(param->tmp_light->src);
		ft_putstr("\n**************\n");
		param->tmp_light = param->tmp_light->next;
	}
}

int		point_display(t_param *param)
{
	return (param->i[0] == 150 && param->i[1] == 225);
}
