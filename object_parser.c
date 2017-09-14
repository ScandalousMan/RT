#include "rt.h"

int 	rt_sphere_parser(t_param *param, t_parse *config)
{
	double		*org;
	t_object 	*tmp_object;
	t_parse		*tmp_config;

	if (!(org = (double*)malloc(sizeof(double) * 3)))
		return (0);
	org[0] = ft_atod(config->str);
	org[1] = ft_atod(config->next->str);
	org[2] = ft_atod(config->next->next->str);
	tmp_object = add_sphere(param, org, ft_atod(config->next->next->next->str));
	if (!tmp_object)
		return (0);
	tmp_object->col = rgb_color(
		ft_atoi(config->next->next->next->next->str),
		ft_atoi(config->next->next->next->next->next->str),
		ft_atoi(config->next->next->next->next->next->next->str));
	if (config->next->next->next->next->next->next->next)
	{
		tmp_config = config->next->next->next->next->next->next->next;
		((t_sphere*)(tmp_object->dim))->center[0] += ft_atod(tmp_config->str);
		((t_sphere*)(tmp_object->dim))->center[1] += ft_atod(tmp_config->next->str);
		((t_sphere*)(tmp_object->dim))->center[2] += ft_atod(tmp_config->next->next->str);
	}
	tmp_object->transparence = 0.5;
	return (1);
}

int 	rt_plane_parser(t_param *param, t_parse *config)
{
	double		*org;
	double		*n;
	t_object 	*tmp_object;
	t_parse		*tmp_config;

	if (!(org = (double*)malloc(sizeof(double) * 3)) ||
		!(n = (double*)malloc(sizeof(double) * 3)))
		return (0);
	org[0] = ft_atod(config->str);
	org[1] = ft_atod(config->next->str);
	org[2] = ft_atod(config->next->next->str);
	n[0] = ft_atod(config->next->next->next->str);
	n[1] = ft_atod(config->next->next->next->next->str);
	n[2] = ft_atod(config->next->next->next->next->next->str);
	tmp_object = add_plane(param, n, org);
	if (!tmp_object)
		return (0);
	tmp_object->col = rgb_color(
		ft_atoi(config->next->next->next->next->next->next->str),
		ft_atoi(config->next->next->next->next->next->next->next->str),
		ft_atoi(config->next->next->next->next->next->next->next->next->str));
	if (config->next->next->next->next->next->next->next->next->next)
	{
		tmp_config = config->next->next->next->next->next->next->next->next->next;
		((t_plane*)(tmp_object->dim))->ref[0] += ft_atod(tmp_config->str);
		((t_plane*)(tmp_object->dim))->ref[1] += ft_atod(tmp_config->next->str);
		((t_plane*)(tmp_object->dim))->ref[2] += ft_atod(tmp_config->next->next->str);
		rotation_matrice(ft_atod(tmp_config->next->next->next->str),
			ft_atod(tmp_config->next->next->next->next->str),
			ft_atod(tmp_config->next->next->next->next->next->str), param);
		matrice_product(param->rot, ((t_plane*)(tmp_object->dim))->n, ((t_plane*)(tmp_object->dim))->n);
	}
	return (1);	
}

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

int 	rt_object_parser(t_param *param, t_parse *config)
{
	if (ft_atoi(config->next->str) == 1 &&
		(config->list_len == 9 || config->list_len == 12))
		return (rt_sphere_parser(param, config->next->next));
	if (ft_atoi(config->next->str) == 2 &&
		(config->list_len == 11 || config->list_len == 17))
		return (rt_plane_parser(param, config->next->next));
	if (ft_atoi(config->next->str) == 3 &&
		(config->list_len == 12 || config->list_len == 18))
		return (rt_cone_parser(param, config->next->next));
	if (ft_atoi(config->next->str) == 4 &&
		(config->list_len == 12 || config->list_len == 18))
		return (rt_cylindre_parser(param, config->next->next));
	return (0);
}