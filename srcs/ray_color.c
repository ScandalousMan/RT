/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:40:48 by jbouille          #+#    #+#             */
/*   Updated: 2018/08/06 16:03:55 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

int		object_color(t_param *param, t_path *path)
{
	if (param && path && path->current_object)
	{
		param->tmp_light = param->lights;
		object_position(path->x, path->current_object);
		object_color_changer(path->current_object, param);
		object_normal_changer(path->current_object, param, path);
		param->final_col = rgb_ratio(param->texture_col, (double)param->macro.k_ambience);
		while (param->tmp_light)
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
				if (scalar_product(path->l, path->n) > 0.0){
					param->final_col = color_summer(param->final_col,
						rgb_ratio(color_absorber(param->tmp_light->tmp_col, param->texture_col),
							path->current_object->kd * scalar_product(path->l, path->n) * param->tmp_light->i));
				}
				if (param->brightness && ft_pow(scalar_product(path->l, path->r), param->brightness) > 0.0){
					param->final_col = color_summer(param->final_col,
						rgb_ratio(param->tmp_light->tmp_col, path->current_object->ks * ft_pow(scalar_product(path->l, path->r), path->current_object->phong) * param->tmp_light->i));
				}
			param->tmp_light = param->tmp_light->next;
		}
		return param->final_col;
	}
	return (0);
}

int		ray_color(t_param *param, double *from, double *to, int index, t_path *path)
{
	path->current_object = NULL;
	param->intersect_object = NULL;
	param->is_for_light = 0;
	path->current_object = first_obj_hit(param, from, to, path);
	if (!path->current_object)
	{
		if (!index)
			param->pxl_infos[param->i[0]][param->i[1]] = 0;
		return 0;
	}
	else
	{
		if (!index)
			param->pxl_infos[param->i[0]][param->i[1]] = path->current_object->num;
		if (!param->to_pix && index < param->macro.recursion)
		{
			path->reflected->inside_obj = path->inside_obj;
			vec_copy(path->r, path->reflected->v);
			vec_copy(path->x, path->reflected->from);
			define_refracted_n(path, path->transmitted);
			if ((snell_descartes(get_index_n(path), get_index_n(path->transmitted), path, path->transmitted)))
			{
				vec_copy(path->x, path->transmitted->from);
				vec_multiply(EPSILON, path->v, param->tmp_vec);
				pt_translated(path->transmitted->from, param->tmp_vec, path->transmitted->from);
				vec_multiply(EPSILON, path->transmitted->v, param->tmp_vec);
				pt_translated(path->transmitted->from, param->tmp_vec, path->transmitted->from);
				return (
					color_summer(
						color_summer(
							rgb_ratio(object_color(param, path), (1.0 - path->current_object->transparency - path->current_object->reflection)),
							color_absorber(rgb_ratio(ray_color(param, path->transmitted->from, path->transmitted->v, index + 1, path->transmitted), path->current_object->transparency), path->current_object->col)
						),
						color_absorber(rgb_ratio(ray_color(param, path->reflected->from, path->reflected->v, index + 1, path->reflected), path->current_object->reflection), path->current_object->col)
					)
				);
			}
			else
			{
				return (
					color_summer(
						rgb_ratio(object_color(param, path), (1.0 - path->current_object->transparency - path->current_object->reflection)),
						color_absorber(rgb_ratio(ray_color(param, path->reflected->from, path->reflected->v, index + 1, path->reflected), path->current_object->reflection + path->current_object->transparency), path->current_object->col)
					)
				);
			}
		}
		else
			return (object_color(param, path));
	}
}
