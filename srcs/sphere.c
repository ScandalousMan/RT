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
	return (1);
}

t_object		*add_sphere(t_param *param, double *center, double radius)
{
	t_object	*tmp;

	tmp = NULL;
	if (!center)
		return (NULL);
	tmp = object_constructor(param);
	if (tmp)
	{
		tmp->type = 1;
		tmp->kd = 0.55;
		tmp->ks = 0.25;
		tmp->phong = SPECULAR_EXP;
		if (!(tmp->dim = ((t_sphere*)malloc(sizeof(t_sphere)))))
			return (NULL);
		ft_memcpy(&(((t_sphere*)tmp->dim)->center), center, VEC_SIZE * sizeof(double));
//		((t_sphere*)(tmp->dim))->center = center;
		((t_sphere*)(tmp->dim))->radius = radius;
	}
	return (tmp);
}

double	distance_to_sphere(t_object *tmp, double *from, double *to)
{
	double	a;
	double	d;

	d = -1.0;
	if ((a = second_level(vec_norm(to) * vec_norm(to),
			2.0 * (to[0] * (from[0] - ((t_sphere*)(tmp->dim))->center[0]) +
			to[1] * (from[1] - ((t_sphere*)(tmp->dim))->center[1]) +
			to[2] * (from[2] - ((t_sphere*)(tmp->dim))->center[2])),
			(from[0] - ((t_sphere*)(tmp->dim))->center[0]) * (from[0] -
			((t_sphere*)(tmp->dim))->center[0]) +
			(from[1] - ((t_sphere*)(tmp->dim))->center[1]) * (from[1] -
			((t_sphere*)(tmp->dim))->center[1]) + (from[2] -
			((t_sphere*)(tmp->dim))->center[2]) * (from[2] -
			((t_sphere*)(tmp->dim))->center[2]) -
			((t_sphere*)(tmp->dim))->radius * ((t_sphere*)(tmp->dim))->radius))
			>= 0)
		d = a * vec_norm(to);
	return (d);
}

void	update_normal_sphere(t_object *tmp, t_path *path)
{
	vec_soustraction(path->x, ((t_sphere*)(tmp->dim))->center, path->n);
}
