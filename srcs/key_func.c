/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:39 by aguemy            #+#    #+#             */
/*   Updated: 2018/08/28 17:04:49 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_objects.h"

void	free_objects(t_param *param)
{
	t_object	*tmp;
	t_limit		*l_tmp;

	while (param && param->objects)
	{
		tmp = param->objects->next;
		if (param->objects->type == RTSPHERE)
			free ((t_sphere*)(param->objects->dim));
		else if (param->objects->type == RTPLAN)
			free ((t_plane*)(param->objects->dim));
		else if (param->objects->type == RTCONE)
			free ((t_cone*)(param->objects->dim));
		else if (param->objects->type == RTCYLINDER)
			free ((t_cylindre*)(param->objects->dim));
		else if (param->objects->type == RTQUADRIC)
			free ((t_quadric*)(param->objects->dim));
		else if (param->objects->type == RTTORE)
			free ((t_tore*)(param->objects->dim));
		while (param->objects->limits)
		{
			l_tmp = param->objects->limits->next;
			free(param->objects->limits);
			param->objects->limits = l_tmp;
		}
		free(param->objects);
		param->objects = tmp;
	}
}

void	free_lights(t_light *lights)
{
	t_light		*tmp;

	while (lights)
	{
		tmp = lights->next;
		free(lights);
		lights = tmp;
	}
	free(lights);
}

void	free_path(t_path *path)
{
	if (path)
	{
		free_path(path->reflected);
		free_path(path->transmitted);
		free(path);
	}
}

void	end_program(t_param *param)
{
	// UNUSED(param);
	free_objects(param);
	free_lights(param->lights);
	free_path(param->path);
	free_pxl_infos(param->pxl_infos);
	free(param->thread);
	SDL_FreeSurface(param->texture);
	free(param);
	// exit(0);
}

void	rotation_axis_matrice(double angle, double *axis, t_param *param)
{
	double	c;
	double	s;

	c = cos(angle * M_PI / 180.0);
	s = sin(angle * M_PI / 180.0);
	param->rot[0][0] = axis[0] * axis[0] * (1.0 - c) + c;
	param->rot[0][1] = axis[0] * axis[1] * (1.0 - c) - axis[2] * s;
	param->rot[0][2] = axis[0] * axis[2] * (1.0 - c) + axis[1] * s;
	param->rot[1][0] = axis[0] * axis[1] * (1.0 - c) + axis[2] * s;
	param->rot[1][1] = axis[1] * axis[1] * (1.0 - c) + c;
	param->rot[1][2] = axis[1] * axis[2] * (1.0 - c) - axis[0] * s;
	param->rot[2][0] = axis[0] * axis[2] * (1.0 - c) - axis[1] * s;
	param->rot[2][1] = axis[1] * axis[2] * (1.0 - c) + axis[0] * s;
	param->rot[2][2] = axis[2] * axis[2] * (1.0 - c) + c;
}

void	rotation_matrice(double alpha, double beta, double gamma, t_param *param)
{
	alpha = alpha * M_PI / 180.0;
	beta = beta * M_PI / 180.0;
	gamma = gamma * M_PI / 180.0;
	param->rot[0][0] = cos(beta) * cos(gamma);
	param->rot[0][1] = -1.0 * cos(beta) * sin(gamma);
	param->rot[0][2] = sin(beta);
	param->rot[1][0] = sin(alpha) * sin(beta) * cos(gamma) + cos(alpha) * sin(gamma);
	param->rot[1][1] = cos(alpha) * cos(gamma) - sin(alpha) * sin(beta) * sin(gamma);
	param->rot[1][2] = -1.0 * sin(alpha) * cos(beta);
	param->rot[2][0] = sin(alpha) * sin(gamma) - cos(alpha) * sin(beta) * cos(gamma);
	param->rot[2][1] = cos(alpha) * sin(beta) * sin(gamma) + sin(alpha) * cos(gamma);
	param->rot[2][2] = cos(alpha) * cos(beta);
}

void	eye_rotation(double alpha, double beta, double gamma, t_param *param)
{
	if (alpha)
		rotation_axis_matrice(alpha, param->third, param);
	else if (beta)
		rotation_axis_matrice(beta, param->align, param);
	else
		rotation_axis_matrice(gamma, param->look, param);
	matrice_product(param->rot, param->look, param->look);
	matrice_product(param->rot, param->align, param->align);
	vec_to_unit_norm(vector_product(param->align, param->look, param->third));
}
