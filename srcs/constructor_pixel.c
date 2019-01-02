/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor_pixel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:57:42 by aguemy            #+#    #+#             */
/*   Updated: 2018/08/12 18:58:38 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_param			*pxl_infos_create(t_param *param)
{
	if (!(param->pxl_infos = (int**)malloc(sizeof(int*) * WINDOW_SDL_HEIGHT)))
		return (NULL);
	param->i[0] = 0;
	while (param->i[0] < WINDOW_SDL_HEIGHT)
	{
		if (!(param->pxl_infos[param->i[0]] = (int*)malloc(sizeof(int) *
			WINDOW_SDL_WIDTH)))
			return (NULL);
		param->i[1] = 0;
		while (param->i[1] < WINDOW_SDL_WIDTH)
		{
			param->pxl_infos[param->i[0]][param->i[1]] = 0;
			param->i[1]++;
		}
		param->i[0]++;
	}
	return (param);
}

void		free_pxl_infos(int **pxl_infos)
{
	int i;

	i = 0;
	while (i < WINDOW_SDL_HEIGHT)
	{
		free(pxl_infos[i]);
		i++;
	}
	free(pxl_infos);
}

t_sdl				*copy_pxls(t_param *param)
{
	t_sdl *graph;
	int 	count;

	count = 0;
	if (!(graph = (t_sdl*)malloc(sizeof(t_sdl))))
		return (NULL);
	graph->win_gl = param->graph->win_gl;
	graph->gl_context = param->graph->gl_context;
	graph->win_sdl = param->graph->win_sdl;
	graph->render_sdl = param->graph->render_sdl;
	while (count < NB_THREAD)
	{
		if ((graph->surfs[count] = SDL_CreateRGBSurfaceWithFormat(0,
		WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT / NB_THREAD, 32,
		SDL_PIXELFORMAT_ARGB8888)) == NULL)
			error(0, 0, "Can't create all surface");
		if ((graph->tmp_surfs[count] = SDL_CreateRGBSurfaceWithFormat(0,
		WINDOW_SDL_WIDTH, WINDOW_SDL_HEIGHT / NB_THREAD, 32,
		SDL_PIXELFORMAT_ARGB8888)) == NULL)
			error(0, 0, "Can't create all surface");
		count++;
	}
	graph->show_tmp = 0;
	return graph;
}
