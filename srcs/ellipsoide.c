#include "rt.h"
/*
int 	rt_ellipsoide_parser(t_param *param, t_parse *config)
{
	double		*org;
	t_object 	*tmp_object;
	t_parse		*tmp_config;

	if (!(org = (double*)malloc(sizeof(double) * 3)))
		return (0);
	org[0] = ft_atod(config->str);
	org[1] = ft_atod(config->next->str);
	org[2] = ft_atod(config->next->next->str);
	tmp_object = add_ellipsoide(param, org, ft_atod(config->next->next->next->str),
		ft_atod(config->next->next->next->next->str),
		ft_atod(config->next->next->next->next->next->str));
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

t_object		*add_ellipsoide(t_param *param, double *center, double a, double b, double c)
{
	t_object	*tmp;

	tmp = NULL;
	if (!center)
		return (NULL);
	tmp = object_constructor(param);
	if (tmp)
	{
		tmp->type = 5;
		tmp->kd = 0.55;
		tmp->ks = 0.25;
		tmp->phong = param->macro.specular_exp;
		if (!(tmp->dim = ((t_ellipsoide*)malloc(sizeof(t_ellipsoide)))))
			return (NULL);
		ft_memcpy(&(((t_ellipsoide*)tmp->dim)->center), center, VEC_SIZE * sizeof(double));
//		((t_ellipsoide*)(tmp->dim))->center = center;
		((t_ellipsoide*)(tmp->dim))->a = a;
		((t_ellipsoide*)(tmp->dim))->b = b;
		((t_ellipsoide*)(tmp->dim))->c = c;
	}
	return (tmp);
}
*/
double	distance_to_ellipsoide(t_object *tmp, double *from, double *to)
{
	if (tmp && from && to)
		return (-1.0);
	else
		return (-2.0);
}

void	update_normal_ellipsoide(t_object *tmp, t_path *path)
{
	if (tmp && path)
		ft_putstr("\n$$ coucou $$\n");
}
