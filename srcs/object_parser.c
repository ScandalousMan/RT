#include <rt.h>

void		*duplicate(void *src, size_t size)
{
	void	*copy;

	if (!(copy = malloc(size)))
		return (NULL);
	return (ft_memcpy(copy, src, size));
}

t_limit 	*limits_copy(t_limit *src)
{
	t_limit *copy;

	if ((copy = duplicate(src, sizeof(t_limit))) == NULL)
		return NULL;
	if (src->next)
	{
		if (!(copy->next = limits_copy(src->next)))
			return (NULL);
	}
	return (copy);
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
		copy->dim = duplicate(src->dim, sizeof(t_quadric));
	if (copy->dim == NULL)
		return (NULL);
	if (src->limits && (copy->limits = limits_copy(src->limits)) == NULL)
		return (NULL);
	if (src->next)
	{
		if (!(copy->next = object_copy(src->next)))
			return (NULL);
	}
	return (copy);
}
