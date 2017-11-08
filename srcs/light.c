#include <rt.h>

t_light	*light_copy(t_light *src)
{
	t_light	*copy;

	if (!src)
		return (NULL);
	if (!(copy = duplicate(src, sizeof(t_light))))
		return (NULL);
	if (src->next)
	{
		if (!(copy->next = light_copy(src->next)))
			return (NULL);
	}
	return (copy);
}
