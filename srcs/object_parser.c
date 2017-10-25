#include "rt.h"

int 		rt_object_parser(t_param *param, t_parse *config)
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

void	*duplicate(void *src, size_t size)
{
	void	*copy;

	if (!(copy = malloc(size)))
		return (NULL);
	return (ft_memcpy(copy, src, size));
}

t_object	*object_copy(t_object *src)
{
	t_object	*copy;

	if (!src)
		return (NULL);
	if (!(copy = duplicate(src, sizeof(t_object))))
		return (NULL);
	if (copy->type == 1)
		copy->dim = duplicate(src->dim, sizeof(t_sphere));
	else if (copy->type == 2)
		copy->dim = duplicate(src->dim, sizeof(t_plane));
	else if (copy->type == 3)
		copy->dim = duplicate(src->dim, sizeof(t_cone));
	else if (copy->type == 4)
		copy->dim = duplicate(src->dim, sizeof(t_cylindre));
	else if (copy->type == 5)
		copy->dim = duplicate(src->dim, sizeof(t_ellipsoide));
	if (copy->dim == NULL)
		return (NULL);
	if (src->next)
	{
		if (!(copy->next = object_copy(src->next)))
			return (NULL);
	}
	return (copy);
}
