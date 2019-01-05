/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:57:42 by aguemy            #+#    #+#             */
/*   Updated: 2018/08/12 18:58:38 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_path	*path_create(t_param *param, int index)
{
	t_path		*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	path->current_object = NULL;
	path->inside_obj = NULL;
	path->reflected = index < param->macro.recursion ?
		path_create(param, index + 1) : NULL;
	path->transmitted = index < param->macro.recursion ?
		path_create(param, index + 1) : NULL;
	return (path);
}

void	struct_args_init(t_param *param)
{
	param->brightness = 1;
	param->quit = FALSE;
	param->epsilon = EPSILON;
	param->customs = NULL;
	param->objects = NULL;
	param->lights = NULL;
	param->tmp_light = NULL;
	param->intersect_object = NULL;
	param->f = FOCAL_VALUE;
	param->ia = 1.0;
	param->num_lights = 0;
	param->num_objects = 0;
	param->up_img.process = TRUE;
	param->up_img.post_process = TRUE;
	param->current_thread = 0;
	param->macro.anti_aliasing = ANTI_ALIASING;
	param->macro.recursion = RECURSION;
	param->macro.cartoon_factor = CARTOON_FACTOR;
	param->macro.blur_radius = BLUR_RADIUS;
	param->macro.specular_exp = SPECULAR_EXP;
	param->macro.rotation_angle = ROTATION_ANGLE;
	param->macro.k_ambience = K_AMBIENCE;
	param->macro.filter = 0;
}

t_param	*struct_create(void)
{
	t_param		*param;

	if (!(param = (t_param*)malloc(sizeof(t_param))))
		return (NULL);
	if (!(param->thread = (SDL_Thread**)malloc(sizeof(SDL_Thread*) *
		NB_THREAD)))
		return (NULL);
	struct_args_init(param);
	if (!(param->path = path_create(param, 0)))
		return (NULL);
	if (!pxl_infos_create(param))
		return (NULL);
	return (param);
}
