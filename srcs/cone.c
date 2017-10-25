#include "rt.h"

int 	rt_cone_parser(t_param *param, t_parse *config)
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
	tmp_object = add_cone(param, org, u, M_PI / 180.0 *
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
		((t_cone*)(tmp_object->dim))->org[0] += ft_atod(tmp_config->str);
		((t_cone*)(tmp_object->dim))->org[1] += ft_atod(tmp_config->next->str);
		((t_cone*)(tmp_object->dim))->org[2] += ft_atod(tmp_config->next->next->str);
		rotation_matrice(ft_atod(tmp_config->next->next->next->str),
			ft_atod(tmp_config->next->next->next->next->str),
			ft_atod(tmp_config->next->next->next->next->next->str), param);
		matrice_product(param->rot, ((t_cone*)(tmp_object->dim))->u, ((t_cone*)(tmp_object->dim))->u);
	}
	return (1);
}

t_object		*add_cone(t_param *param, double *org, double *u,
		double angle)
{
	t_object	*tmp;

	tmp = NULL;
	if (!org || !u || M_PI / 2 <= angle || -M_PI / 2 >= angle)
		return (NULL);
	tmp = object_constructor(param);
	if (tmp)
	{
		tmp->type = 3;
		tmp->kd = 0.55;
		tmp->ks = 0.25;
		tmp->phong = SPECULAR_EXP;
		if (!(tmp->dim = ((t_cone*)malloc(sizeof(t_cone)))))
			return (NULL);
		ft_memcpy(&(((t_cone*)tmp->dim)->org), org, VEC_SIZE * sizeof(double));
		ft_memcpy(&(((t_cone*)tmp->dim)->u), vec_to_unit_norm(u), VEC_SIZE * sizeof(double));
		((t_cone*)(tmp->dim))->angle = angle;
	}
	return (tmp);
}

double	distance_to_cone(t_object *tmp, double *from, double *to)
{
	vec_soustraction(from, ((t_cone*)(tmp->dim))->org, tmp->tmp_vec);
	return (vec_norm(to) * second_level(cone_first_term(tmp, to),
		cone_second_term(tmp, to, tmp->tmp_vec),
		cone_third_term(tmp, tmp->tmp_vec)));
}

void	update_normal_cone(t_object *tmp, t_path *path)
{
	vec_soustraction(path->x, ((t_cone*)(tmp->dim))->org, path->n);
	vec_multiply(1.0 / scalar_product(path->n, ((t_cone*)(tmp->dim))->u) * vec_norm(path->n) * vec_norm(path->n), ((t_cone*)(tmp->dim))->u, tmp->tmp_vec);
	vec_soustraction(path->n, tmp->tmp_vec, path->n);
}
