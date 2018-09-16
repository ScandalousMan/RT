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

t_path			*path_create(t_param *param, int index)
{
	t_path		*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	path->current_object = NULL;
	path->inside_obj = NULL;
	path->reflected = index < param->macro.recursion ? path_create(param, index + 1) : NULL;
	path->transmitted = index < param->macro.recursion ? path_create(param, index + 1) : NULL;
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

void		free_pxl_infos(t_pxl_info ***pxl_infos)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_SDL_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_SDL_WIDTH)
		{
			free(pxl_infos[i][j]);
			j++;
		}
		free(pxl_infos[i]);
		i++;
	}
	free(pxl_infos);
}

t_sdl				*copy_pxls(t_param *param)
{
	t_sdl *graph;
	int 	count;

	count = -1;
	if (!(graph = (t_sdl*)malloc(sizeof(t_sdl))))
		return (NULL);
	graph->win_gl = param->graph->win_gl;
	graph->gl_context = param->graph->gl_context;
	graph->win_sdl = param->graph->win_sdl;
	graph->render_sdl = param->graph->render_sdl;
	count = 0;
	while (count < NB_THREAD)
	{
		if ((graph->surfs[count] = SDL_CreateRGBSurfaceWithFormat(0,
		WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT / NB_THREAD, 32, SDL_PIXELFORMAT_ARGB8888))
		== NULL)
			error(0, 0, "Can't create all surface");
		if ((graph->tmp_surfs[count] = SDL_CreateRGBSurfaceWithFormat(0,
		WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT / NB_THREAD, 32, SDL_PIXELFORMAT_ARGB8888))
		== NULL)
			error(0, 0, "Can't create all surface");
		count++;
	}
	graph->show_tmp = 0;
	return graph;
}

t_param			*stereoscopy_cpy(t_param *param1)
{
	t_param	*param;

	if (!(param = (t_param*)malloc(sizeof(t_param))))
		return (NULL);
	param->f = param1->f;
	param->quit = FALSE;
	vec_multiply(5.0, param1->align, param1->tmp_vec);
	pt_translated(param1->eye, param1->tmp_vec, param->eye);
	vec_copy(param1->look, param->look);
	vec_copy(param1->align, param->align);
	vec_to_unit_norm(vector_product(param->align, param->look, param->third));
	param->path = param1->path;
	param->customs = param1->customs;
	param->objects = param1->objects;
	param->lights = param1->lights;
	param->num_lights = param1->num_lights;
	param->intersect_object = NULL;
	param->tmp_light = NULL;
	param->brightness = param1->brightness;
	param->epsilon = param1->epsilon;
	param->thread = param1->thread;
	param->current_thread = 0;
	param->ia = param1->ia;
	param->macro = param1->macro;
	param->pxl_infos = param1->pxl_infos;
	if (!(param->graph = copy_pxls(param1)))
		return (NULL);
	return (param);
}

void				stereoscopy_free(t_param *param)
{
	int 	count;

	count = 0;
	while (count < NB_THREAD)
	{
		SDL_FreeSurface(param->graph->surfs[count]);
		SDL_FreeSurface(param->graph->tmp_surfs[count]);
		count++;
	}
	free(param->graph);
	free(param->thread);
	free(param);
}

t_param			*struct_create(void)
{
	t_param		*param;

	if (!(param = (t_param*)malloc(sizeof(t_param))))
		return (NULL);
	if (!(param->thread = (SDL_Thread**)malloc(sizeof(SDL_Thread*) * NB_THREAD)))
		return (NULL);
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
	param->refresh = 1;
	param->current_thread = 0;
	param->macro.anti_aliasing = ANTI_ALIASING;
	param->macro.recursion = RECURSION;
	param->macro.cartoon_factor = 25;
	param->macro.blur_radius = BLUR_RADIUS;
	param->macro.specular_exp = 1;
	param->macro.rotation_angle = 30;
	param->macro.k_ambience = K_AMBIENCE;
	param->macro.filter = 0;
	if (!(param->path = path_create(param, 0)))
		return (NULL);
	if (!pxl_infos_create(param))
		return (NULL);
	return (param);
}
