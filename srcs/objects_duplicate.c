/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_duplicate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2018/10/31 21:49:47 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

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
	if (copy->type == RTSPHERE)
		copy->dim = duplicate(src->dim, sizeof(t_sphere));
	else if (copy->type == RTPLAN)
		copy->dim = duplicate(src->dim, sizeof(t_plane));
	else if (copy->type == RTCONE)
		copy->dim = duplicate(src->dim, sizeof(t_cone));
	else if (copy->type == RTCYLINDER)
		copy->dim = duplicate(src->dim, sizeof(t_cylindre));
	else if (copy->type == RTQUADRIC)
		copy->dim = duplicate(src->dim, sizeof(t_quadric));
	else if (copy->type == RTCUBE)
		copy->dim = duplicate(src->dim, sizeof(t_cube));
	if (copy->dim == NULL)
		return (NULL);
	if (src->limits && (copy->limits = limits_copy(src->limits)) == NULL)
		return (NULL);
	if (src->next && !(copy->next = object_copy(src->next)))
		return (NULL);
	return (copy);
}
