/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:59:42 by aguemy            #+#    #+#             */
/*   Updated: 2018/08/12 18:58:28 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void				stereoscopy_args_cpy(t_param *param, t_param *param1)
{
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
	stereoscopy_args_cpy(param, param1);
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
	free(param);
}
