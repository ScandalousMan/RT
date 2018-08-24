#include "rt_objects.h"

void	display_objects(t_param *param)
{
	t_object *objs = param->objects;
	while (objs && DEBUG)
	{
		ft_putstr("\n***************\n");
		if (objs->type == RTSPHERE)
		{
			ft_putstr("** nouvelle sphere **\n");
			ft_putstr("centre : ");
			ft_putvec(((t_sphere*)(objs->dim))->center);
			ft_putchar('\n');
			ft_putstr("rayon : ");
			ft_putnbr(((t_sphere*)(objs->dim))->radius);
			ft_putchar('\n');
		}
		if (objs->type == RTPLAN)
		{
			ft_putstr("** nouveau plan **\n");
			ft_putstr("point : ");
			ft_putvec(((t_plane*)(objs->dim))->ref);
			ft_putchar('\n');
			ft_putstr("normale : ");
			ft_putvec(((t_plane*)(objs->dim))->n);
			ft_putchar('\n');
		}
		if (objs->type == RTCONE)
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
		if (objs->type == RTCYLINDER)
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
		if (objs->type == RTQUADRIC)
		{
			ft_putstr("** nouvelle quadrique **\n");
			ft_putstr("centre : ");
			ft_putvec(((t_quadric*)(objs->dim))->center);
			ft_putchar('\n');
			ft_putstr("a: ");
			ft_putdbl(((t_quadric*)(objs->dim))->a, 4);
			ft_putchar('\n');
			ft_putstr("b: ");
			ft_putdbl(((t_quadric*)(objs->dim))->b, 4);
			ft_putchar('\n');
			ft_putstr("c: ");
			ft_putdbl(((t_quadric*)(objs->dim))->c, 4);
			ft_putchar('\n');
			ft_putstr("d: ");
			ft_putdbl(((t_quadric*)(objs->dim))->d, 4);
			ft_putchar('\n');
			ft_putstr("e: ");
			ft_putdbl(((t_quadric*)(objs->dim))->e, 4);
			ft_putchar('\n');
			ft_putstr("f: ");
			ft_putdbl(((t_quadric*)(objs->dim))->f, 4);
			ft_putchar('\n');
			ft_putstr("g: ");
			ft_putdbl(((t_quadric*)(objs->dim))->g, 4);
			ft_putchar('\n');
			ft_putstr("h: ");
			ft_putdbl(((t_quadric*)(objs->dim))->h, 4);
			ft_putchar('\n');
			ft_putstr("i: ");
			ft_putdbl(((t_quadric*)(objs->dim))->i, 4);
			ft_putchar('\n');
		}
		if (objs->type == RTTORE)
		{
			ft_putstr("** nouveau tore **\n");
			ft_putstr("R: ");
			ft_putnbr(((t_tore*)(objs->dim))->r1);
			ft_putchar('\n');
			ft_putstr("r: ");
			ft_putnbr(((t_tore*)(objs->dim))->r2);
			ft_putchar('\n');
			ft_putstr("axis: ");
			ft_putvec(((t_tore*)(objs->dim))->axis);
			ft_putchar('\n');
			ft_putstr("center: ");
			ft_putvec(((t_tore*)(objs->dim))->center);
			ft_putchar('\n');
		}
		ft_putchar('#');
		ft_putnbr(objs->num);
		ft_putstr("\ncolor = ");
		ft_putnbr(objs->col);
		ft_putstr("\nindice = ");
		ft_putdbl(objs->index, 2);
		ft_putstr("\nmiroir:");
		ft_putdbl(objs->reflection, 4);
		ft_putstr("\nreferentiel: ");
		ft_putdbl(objs->ref.i[0], 2);
		ft_putstr(", ");
		ft_putdbl(objs->ref.i[1], 2);
		ft_putstr(", ");
		ft_putdbl(objs->ref.i[2], 2);
		ft_putstr(" | ");
		ft_putdbl(objs->ref.j[0], 2);
		ft_putstr(", ");
		ft_putdbl(objs->ref.j[1], 2);
		ft_putstr(", ");
		ft_putdbl(objs->ref.j[2], 2);
		ft_putstr(" | ");
		ft_putdbl(objs->ref.k[0], 2);
		ft_putstr(", ");
		ft_putdbl(objs->ref.k[1], 2);
		ft_putstr(", ");
		ft_putdbl(objs->ref.k[2], 2);
		ft_putstr("\n***************\n");
		objs = objs->next;
	}
}

void	display_lights(t_param *param)
{
	param->tmp_light = param->lights;
	while (param->tmp_light && DEBUG)
	{
		ft_putstr("light detected,#");
		ft_putnbr(param->tmp_light->num);
		ft_putstr("\ntype: ");
		ft_putnbr(param->tmp_light->type);
		ft_putendl("");
		ft_putvec(param->tmp_light->src);
		ft_putstr("\n**************\n");
		param->tmp_light = param->tmp_light->next;
	}
}

void	light_display_objects(t_param *param)
{
	t_object *tmp;

	tmp = param->objects;
	while (tmp) {
		printf("number object: %d, type: %d, address: %p\n", tmp->num, tmp->type, tmp);
		tmp = tmp->next;
	}
}

int		point_display(t_param *param)
{
	return (ft_absint(param->i[0] - 10) <= 0 && ft_absint(param->i[1] - 10) <= 0);
}
