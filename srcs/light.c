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

