#include "rt.h"

int 	rt_cylindre_parser(t_param *param, t_parse *config)
{
	double		*org;
	double		*u;
	t_object 	*tmp_object;
	t_parse		*tmp_config;

	if (!(org = (double*)malloc(sizeof(double) * 3)) ||
		!(u = (double*)malloc(sizeof(double) * 3)))
		return (0);
	org[0] = ft_atod(config->str);
	org[1] = ft_atod(config->next->str);
	org[2] = ft_atod(config->next->next->str);
	u[0] = ft_atod(config->next->next->next->str);
	u[1] = ft_atod(config->next->next->next->next->str);
	u[2] = ft_atod(config->next->next->next->next->next->str);
	tmp_object = add_cylindre(param, org, u,
		ft_atod(config->next->next->next->next->next->next->str));
	if (!tmp_object)
		return (0);
	tmp_object->col = rgb_color(
		ft_atoi(config->next->next->next->next->next->next->next->str),
		ft_atoi(config->next->next->next->next->next->next->next->next->str),
		ft_atoi(
			config->next->next->next->next->next->next->next->next->next->str));
	if (config->next->next->next->next->next->next->next->next->next->next)
	{
		tmp_config = config->next->next->next->next->next->next->next->next->next->next;
		((t_cylindre*)(tmp_object->dim))->org[0] += ft_atod(tmp_config->str);
		((t_cylindre*)(tmp_object->dim))->org[1] += ft_atod(tmp_config->next->str);
		((t_cylindre*)(tmp_object->dim))->org[2] += ft_atod(tmp_config->next->next->str);
		rotation_matrice(ft_atod(tmp_config->next->next->next->str),
			ft_atod(tmp_config->next->next->next->next->str),
			ft_atod(tmp_config->next->next->next->next->next->str), param);
		matrice_product(param->rot, ((t_cylindre*)(tmp_object->dim))->u, ((t_cylindre*)(tmp_object->dim))->u);
	}
	return (1);
}

t_object		*add_cylindre(t_param *param, double *org, double *u, double radius)
{
	t_object	*tmp;

	tmp = NULL;
	if (!org || !u)
		return (NULL);
	tmp = object_constructor(param);
	if (tmp)
	{
		tmp->type = 4;
		tmp->kd = 0.55;
		tmp->ks = 0.25;
		tmp->phong = SPECULAR_EXP;
		if (!(tmp->dim = ((t_cylindre*)malloc(sizeof(t_cylindre)))))
			return (NULL);
		((t_cylindre*)(tmp->dim))->org = org;
		((t_cylindre*)(tmp->dim))->radius = radius;
		((t_cylindre*)(tmp->dim))->u = vec_to_unit_norm(u);
	}
	return (tmp);
}

double	distance_to_cylindre(t_object *tmp, double *from, double *to)
{
	vec_soustraction(from, ((t_cylindre*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(to) * second_level(cylindre_first_term(tmp, to),
		cylindre_second_term(tmp, to), cylindre_third_term(tmp)));
}

void	update_normal_cylindre(t_object *tmp, t_path *path)
{
	vec_soustraction(path->x, ((t_cylindre*)(tmp->dim))->org, path->n);
	vec_multiply(scalar_product(path->n, ((t_cylindre*)(tmp->dim))->u), ((t_cylindre*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(path->n, tmp->tmp_vec, path->n);
}
