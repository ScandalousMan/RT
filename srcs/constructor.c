/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:57:42 by aguemy            #+#    #+#             */
/*   Updated: 2017/11/20 00:26:53 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_path			*path_create(int index, t_param *param)
{
	t_path		*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	path->current_object = NULL;
	path->reflected = index < RECURSION ? path_create(index + 1, param) : NULL;
	path->transmitted = index < RECURSION ? path_create(index + 1, param) : NULL;
	return (path);
}

t_param			*pxl_infos_create(t_param *param)
{
	if (!(param->pxl_infos = (t_pxl_info***)malloc(sizeof(t_pxl_info**) * WINDOW_SDL_HEIGHT)))
		return (NULL);
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		if (!(param->pxl_infos[param->i[0]] = (t_pxl_info**)malloc(sizeof(t_pxl_info*) * WINDOW_SDL_WIDTH)))
			return (NULL);
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			if (!(param->pxl_infos[param->i[0]][param->i[1]] = (t_pxl_info*)malloc(sizeof(t_pxl_info))))
				return (NULL);
			param->i[1]++;
		}
		param->i[0]++;
	}
	return (param);
}

t_param			*struct_create(void)
{
	t_param		*param;

	if (!(param = (t_param*)malloc(sizeof(t_param))))
		return (NULL);
	param->path = path_create(0, param);
	if (!(param->thread = (SDL_Thread**)malloc(sizeof(SDL_Thread*) * NB_THREAD)))
		return (NULL);
	param->brightness = 1;
	param->epsilon = EPSILON;
	param->customs = NULL;
	param->objects = NULL;
	param->lights = NULL;
//	param->tmp_object = NULL;
	param->tmp_light = NULL;
	param->intersect_object = NULL;
	param->f = FOCAL_VALUE;
	param->ia = 1.0;
	param->num_lights = 0;
	param->refresh = 1;
	param->current_thread = 0;
	if (!pxl_infos_create(param))
		return (NULL);
	return (param);
}
