#include "rt.h"

int 	rt_object_parser(t_param *param, t_parse *config)
{
	if (ft_atoi(config->next->str) == 1 &&
		(config->list_len == 9 || config->list_len == 12))
		return (rt_sphere_parser(param, config->next->next));
	else if (ft_atoi(config->next->str) == 2 &&
		(config->list_len == 11 || config->list_len == 17))
		return (rt_plane_parser(param, config->next->next));
	else if (ft_atoi(config->next->str) == 3 &&
		(config->list_len == 12 || config->list_len == 18))
		return (rt_cone_parser(param, config->next->next));
	else if (ft_atoi(config->next->str) == 4 &&
		(config->list_len == 12 || config->list_len == 18))
		return (rt_cylindre_parser(param, config->next->next));
	else if (ft_atoi(config->next->str) == 5 &&
		(config->list_len == 11 || config->list_len == 17))
		return (rt_ellipsoide_parser(param, config->next->next));
	return (0);
}