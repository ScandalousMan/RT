/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:32:22 by jbouille          #+#    #+#             */
/*   Updated: 2019/01/12 15:42:59 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

void	object_common_display(t_object *objs)
{
	ft_putchar('#');
	ft_putnbr(objs->num);
	ft_putstr("\ncolor = ");
	ft_putnbr(objs->col);
	ft_putstr("\nindex = ");
	ft_putdbl(objs->index, 2);
	ft_putstr("\nmirror:");
	ft_putdbl(objs->reflection, 4);
	ft_putstr("\n***************\n");
}

void	display_objects(t_param *param)
{
	t_object *objs;

	objs = param->objects;
	while (objs && DEBUG)
	{
		ft_putstr("\n***************\n");
		if (objs->type == RTSPHERE)
			display_sphere(objs);
		if (objs->type == RTPLAN)
			display_plane(objs);
		if (objs->type == RTCONE)
			display_cone(objs);
		if (objs->type == RTCYLINDER)
			display_cylindre(objs);
		if (objs->type == RTQUADRIC)
			display_quadric(objs);
		if (objs->type == RTCUBE)
			display_cube(objs);
		object_common_display(objs);
		objs = objs->next;
	}
}

void	display_lights(t_param *param)
{
	param->tmp_light = param->lights;
	while (param->tmp_light && DEBUG)
	{
		ft_putstr("light detected,#");
		ft_putnbr(param->tmp_light->num);
		ft_putstr("\ntype: ");
		ft_putnbr(param->tmp_light->type);
		ft_putendl("");
		ft_putvec(param->tmp_light->src);
		ft_putstr("\n**************\n");
		param->tmp_light = param->tmp_light->next;
	}
}

void	light_display_objects(t_param *param)
{
	t_object *tmp;

	tmp = param->objects;
	while (tmp)
	{
		if (DEBUG)
			mprintf(1, "number object: %d, type: %d, address: %p\n",
			tmp->num, tmp->type, tmp);
		tmp = tmp->next;
	}
}

int		point_display(t_param *param)
{
	return (!param->is_for_light && ft_absint(param->i[0] - 357) <= 0 &&
		ft_absint(param->i[1] - 329) <= 0);
}
