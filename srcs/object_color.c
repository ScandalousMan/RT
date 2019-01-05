/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:40:48 by jbouille          #+#    #+#             */
/*   Updated: 2018/08/06 16:03:55 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

void	object_color_updater(t_param *param, t_path *path)
{
	if (param->tmp_light->type == RTSPOT)
		vec_soustraction(param->tmp_light->src, path->x, path->l);
	else
		vec_multiply(-1.0, param->tmp_light->src, path->l);
	vec_to_unit_norm(path->l);
	vec_multiply(-2.0 * scalar_product(path->n, path->v), path->n, path->r);
	pt_translated(path->r, path->v, path->r);
	vec_to_unit_norm(path->r);
	light_masked(param, path->x, path->l, path);
	if (scalar_product(path->l, path->n) > 0.0)
	{
		param->final_col = color_summer(param->final_col,
			rgb_ratio(color_absorber(param->tmp_light->tmp_col,
			param->texture_col), path->current_object->kd *
			scalar_product(path->l, path->n) * param->tmp_light->i));
	}
	if (param->brightness && ft_pow(scalar_product(path->l, path->r),
		param->brightness) > 0.0)
	{
		param->final_col = color_summer(param->final_col,
			rgb_ratio(param->tmp_light->tmp_col, path->current_object->ks *
			ft_pow(scalar_product(path->l, path->r),
			path->current_object->phong) * param->tmp_light->i));
	}
}

int		object_color(t_param *param, t_path *path)
{
	if (param && path && path->current_object)
	{
		param->tmp_light = param->lights;
		object_position(path->x, path->current_object);
		object_color_changer(path->current_object, param);
		object_normal_changer(path->current_object, param, path);
		param->final_col = rgb_ratio(param->texture_col,
			(double)param->macro.k_ambience);
		while (param->tmp_light)
		{
			object_color_updater(param, path);
			param->tmp_light = param->tmp_light->next;
		}
		return (param->final_col);
	}
	return (0);
}
