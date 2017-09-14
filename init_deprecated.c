/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:28:19 by aguemy            #+#    #+#             */
/*   Updated: 2017/06/25 14:06:51 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		obj_color(t_object *object)
{
	object->ks = 0.85;
	object->kd = 0.65;
	object->phong = 2;//surement des valeurs liees a l'affichage de la couleur, a unifier
}

t_param		*new_content(t_param *param)
{
	double		*src;
	double		*src2;
	double		*ref;
	double		*ref2;
	double		*ref3;
	double		*ref4;
	double		*n;
	double		*u;
	double		*v;
	t_object	*tmp_object;
	t_light		*tmp_light;

	if (param)
	{
		param->f = FOCAL_VALUE;
		param->ia = 1.0;
		tmp_object = param->objects;
		tmp_light = param->lights;
		if (tmp_object && tmp_light)
		{
			while (tmp_object)
			{
				obj_color(tmp_object);
				tmp_object = tmp_object->next;
			}
		}
		param->eye[0] = 0.0;
		param->eye[1] = -100.0;
		param->eye[2] = 0.0;
		param->look[0] = 0.0;
		param->look[1] = 1.0;
		param->look[2] = 0.0;
		param->align[0] = 1.0;
		param->align[1] = 0.0;
		param->align[2] = 0.0;
		vec_to_unit_norm(param->look);
		vec_to_unit_norm(param->align);
		vec_to_unit_norm(vector_product(param->align, param->look, param->third));
		if ((src = (double*)malloc(sizeof(double) * 3)))
		{
			src[0] = 40.0;
			src[1] = -5.0;
			src[2] = -40.0;
			tmp_light = add_light(&(param->lights), src, 1.0, 0x00FFFFFF);
			ft_putstr('light 1 has been created');
			param->num_lights++;
		}
		if ((src2 = (double*)malloc(sizeof(double) * 3)))
		{
			src2[0] = 40.0;
			src2[1] = -5.0;
			src2[2] = 40.0;
			tmp_light = add_light(&(param->lights), src2, 1.0, 0x00FFFFFF);
			ft_putstr('light 1 has been created');
			param->num_lights++;
		}
		if ((ref = (double*)malloc(sizeof(double) * 3)))
		{
			ref[0] = -5.0;
			ref[1] = -5.0;
			ref[2] = 5.0;
			tmp_object = add_sphere(param, ref, 5.0);
			ft_putstr('sphere has been created');
			tmp_object->col = 0x00FF0000;
		}
		if ((ref2 = (double*)malloc(sizeof(double) * 3)) &&
				(n = (double*)malloc(sizeof(double) * 3)))
		{
			ref2[0] = 0.0;
			ref2[1] = 0.0;
			ref2[2] = 0.0;
			n[0]= 0.0;
			n[1]= 1.0;
			n[2]= 0.0;
			tmp_object = add_plane(param, n, ref2);
			ft_putstr('plane has been created');
			tmp_object->col = 0x00CCCCCC;
		}
		if ((ref3 = (double*)malloc(sizeof(double) * 3)) &&
				(u = (double*)malloc(sizeof(double) * 3)))
		{
			ref3[0] = 0.0;
			ref3[1] = -5.0;
			ref3[2] = 0.0;
			u[0] = 1.0;
			u[1] = 0.0;
			u[2] = 1.0;
			tmp_object = add_cone(param, ref3, u, M_PI / 6.0);
			ft_putstr('cone has been created');
			tmp_object->col = 0x00FF00FF;
		}
		if ((ref4 = (double*)malloc(sizeof(double) * 3)) &&
				(v = (double*)malloc(sizeof(double) * 3)))
		{
			ref4[0] = 10.0;
			ref4[1] = -5.0;
			ref4[2] = 10.0;
			v[0] = 1.0;
			v[1] = 0.0;
			v[2] = 0.0;
			tmp_object = add_cylindre(param, ref4, v, 5.0);
			ft_putstr('cylindre has been created');
			tmp_object->col = 0x00FFFF00;
		}
	}
	return (param);
}
