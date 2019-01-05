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

int		refraction_ray_color(t_param *param, t_path *path, int index)
{
	vec_copy(path->x, path->transmitted->from);
	vec_multiply(EPSILON, path->v, param->tmp_vec);
	pt_translated(path->transmitted->from, param->tmp_vec,
		path->transmitted->from);
	vec_multiply(EPSILON, path->transmitted->v, param->tmp_vec);
	pt_translated(path->transmitted->from, param->tmp_vec,
		path->transmitted->from);
	vec_copy(path->transmitted->v, path->transmitted->to);
	vec_copy(path->reflected->v, path->reflected->to);
	return (color_summer(color_summer(rgb_ratio(object_color(param, path),
		(1.0 - path->current_object->transparency -
			path->current_object->reflection)),
		color_absorber(rgb_ratio(ray_color(param, index + 1, path->transmitted),
			path->current_object->transparency), path->current_object->col)),
		color_absorber(rgb_ratio(ray_color(param, index + 1, path->reflected),
			path->current_object->reflection), path->current_object->col)));
}

int		reflection_ray_color(t_param *param, t_path *path, int index)
{
	vec_copy(path->reflected->v, path->reflected->to);
	return (color_summer(rgb_ratio(object_color(param, path),
		(1.0 - path->current_object->transparency -
			path->current_object->reflection)),
		color_absorber(rgb_ratio(ray_color(param, index + 1, path->reflected),
			path->current_object->reflection +
			path->current_object->transparency), path->current_object->col)));
}

int		object_hit_color(t_param *param, t_path *path, int index)
{
	if (!index)
		param->pxl_infos[param->i[0]][param->i[1]] = path->current_object->num;
	if (!param->to_pix && index < param->macro.recursion)
	{
		path->reflected->inside_obj = path->inside_obj;
		vec_copy(path->r, path->reflected->v);
		vec_copy(path->x, path->reflected->from);
		define_refracted_n(path, path->transmitted);
		if ((snell_descartes(get_index_n(path), get_index_n(path->transmitted),
			path, path->transmitted)))
			return (refraction_ray_color(param, path, index));
		else
			return (reflection_ray_color(param, path, index));
	}
	else
		return (object_color(param, path));
}

int		ray_color(t_param *param, int index, t_path *path)
{
	path->current_object = NULL;
	param->intersect_object = NULL;
	param->is_for_light = 0;
	path->current_object = first_obj_hit(param, path->from, path->to, path);
	if (!path->current_object)
	{
		if (!index)
			param->pxl_infos[param->i[0]][param->i[1]] = 0;
		return (0);
	}
	else
		return (object_hit_color(param, path, index));
}
