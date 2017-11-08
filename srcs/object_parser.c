#include <rt.h>

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
