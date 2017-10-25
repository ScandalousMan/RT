#include "rt.h"

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

t_object		*add_plane(t_param *param, double *n, double *ref)
{
	t_object	*tmp;

	tmp = NULL;
	if (!ref || !n)
		return (NULL);
	tmp = object_constructor(param);
	if (tmp)
	{
		tmp->type = 2;
		tmp->kd = 0.55;
		tmp->ks = 0.0;
		tmp->phong = SPECULAR_EXP;
		if (!(tmp->dim = ((t_plane*)malloc(sizeof(t_plane)))))
			return (NULL);
		ft_memcpy(&(((t_plane*)tmp->dim)->ref), ref, VEC_SIZE * sizeof(double));
		ft_memcpy(&(((t_plane*)tmp->dim)->n), vec_to_unit_norm(n), VEC_SIZE * sizeof(double));
//		((t_plane*)(tmp->dim))->ref = ref;
//		((t_plane*)(tmp->dim))->n = vec_to_unit_norm(n);
	}
	return (tmp);
}

double	distance_to_plane(t_object *tmp, double *from, double *to)
{
	if (scalar_product(((t_plane*)(tmp->dim))->n, to) == 0.0)
	{
		if (((t_plane*)(tmp->dim))->n[0] * (((t_plane*)(tmp->dim))->ref[0] - from[0]) + ((t_plane*)(tmp->dim))->n[1] * (((t_plane*)(tmp->dim))->ref[1] * from[1]) +
				((t_plane*)(tmp->dim))->n[2] * (((t_plane*)(tmp->dim))->ref[2] - from[2]) == 0.0)
			return (0.0);
		return (-1.0);
	}
	else
		return ((((t_plane*)(tmp->dim))->n[0] * (((t_plane*)(tmp->dim))->ref[0] - from[0]) + ((t_plane*)(tmp->dim))->n[1] *
					(((t_plane*)(tmp->dim))->ref[1] - from[1]) + ((t_plane*)(tmp->dim))->n[2] *
					(((t_plane*)(tmp->dim))->ref[2] - from[2])) / scalar_product(((t_plane*)(tmp->dim))->n, to));
}

void	update_normal_plane(t_object *tmp, t_path *path)
{
	vec_copy(((t_plane*)(tmp->dim))->n, path->n);
	if (scalar_product(path->n, path->v) > 0.0)
		vec_multiply(-1.0, path->n, path->n);
}
