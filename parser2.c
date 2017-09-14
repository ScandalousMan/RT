#include "rt.h"

int 	rt_light_parser(t_param *param, t_parse *config)
{
	double		*src;

	if (!(src = (double*)malloc(sizeof(double) * 3)))
		return (0);
	src[0] = ft_atod(config->next->str);
	src[1] = ft_atod(config->next->next->str);
	src[2] = ft_atod(config->next->next->next->str);
	add_light(&(param->lights), src,
		ft_atod(config->next->next->next->next->str)
		, rgb_color(
			ft_atoi(config->next->next->next->next->next->str),
			ft_atoi(config->next->next->next->next->next->next->str),
			ft_atoi(config->next->next->next->next->next->next->next->str)));
	param->num_lights++;
	return (1);
}

int 	rt_objects_lights_parser(t_param *param, t_parse *config)
{
	if (!ft_strcmp(config->str, "OBJECT"))
		return (rt_object_parser(param, config));
	else if (!ft_strcmp(config->str, "LIGHT") && config->list_len == 8)
		return (rt_light_parser(param, config));
	return (0);
}

void	free_config(t_parse *config)
{
	t_parse	*tmp;

	while(config)
	{
		tmp = config->next;
		free(config->str);
		free(config);
		config = tmp;
	}
}

int 	rt_init(t_param *param, char *line, int count)
{
	t_parse	*config;

	if (!line)
		return (0);
	config = split_whitespace(line);
	if (count == 1 && config->list_len == 3)
	{
		if (!(param->eye = (double*)malloc(sizeof(double) * 3)))
			return (0);
		param->eye[0] = ft_atod(config->str);
		param->eye[1] = ft_atod(config->next->str);
		param->eye[2] = ft_atod(config->next->next->str);
		ft_putstr("position de l'oeil:\n");
		ft_putvec(param->eye);
		ft_putstr("\n*********\n");
	}
	else if (count == 2 && config->list_len == 3)
	{
		if (!(param->look = (double*)malloc(sizeof(double) * 3)))
			return (0);
		param->look[0] = ft_atod(config->str);
		param->look[1] = ft_atod(config->next->str);
		param->look[2] = ft_atod(config->next->next->str);
		vec_to_unit_norm(param->look);
		ft_putstr("direction regard:\n");
		ft_putvec(param->look);
		ft_putstr("\n*********\n");
	}
	else if (count == 3 && config->list_len == 3)
	{
		if (!(param->align = (double*)malloc(sizeof(double) * 3)))
			return (0);
		param->align[0] = ft_atod(config->str);
		param->align[1] = ft_atod(config->next->str);
		param->align[2] = ft_atod(config->next->next->str);
		if (!param->look)
			return (0);
		if (!(param->third = (double*)malloc(sizeof(double) * 3)))
			return (0);
		vec_to_unit_norm(vector_product(param->align, param->look, param->third));
	}
	else if (!rt_objects_lights_parser(param, config))
			return 0;
	free_config(config);
	return (1);
}
