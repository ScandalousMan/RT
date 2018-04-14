/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:39 by aguemy            #+#    #+#             */
/*   Updated: 2018/03/20 20:15:21 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_objects(t_param *param)
{
	t_object	*tmp;
	t_limit		*l_tmp;

	while (param && param->objects)
	{
		tmp = param->objects->next;
		if (param->objects->type == 1)
		{
			free ((t_sphere*)(param->objects->dim));
		}
		else if (param->objects->type == 2)
		{
			free ((t_plane*)(param->objects->dim));
		}
		else if (param->objects->type == 3)
		{
			free ((t_cone*)(param->objects->dim));
		}
		else if (param->objects->type == 4)
		{
			free ((t_cylindre*)(param->objects->dim));
		}
		if (param->objects->limit)
		{
			l_tmp = param->objects->limit->next;
			while (l_tmp)
			{
				free(param->objects->limit);
				param->objects->limit = l_tmp;
			}
		}
		free(param->objects);
		param->objects = tmp;
	}
}

void	free_lights(t_param *param)
{
	t_light		*tmp;

	while (param && param->lights)
	{
		tmp = param->lights->next;
		free(param->lights);
		param->lights = tmp;
	}
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
	free_objects(param);
	free_lights(param);
	free_path(param->path);
	free(param);
	exit(0);
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

int		my_key_func(int keycode, t_param *param)
{
	param->to_pix = 1;
	if (keycode == SDLK_ESCAPE)
		end_program(param);
	else if (keycode == SDLK_RIGHT) //droite
	{
		param->eye[0] += 10;
	}
	else if (keycode == SDLK_LEFT) //gauche
	{
		param->eye[0] -= 10;
	}
	else if (keycode == SDLK_UP) //haut
	{
		param->eye[2] += 10;
	}
	else if (keycode == SDLK_DOWN) //bas
	{
		param->eye[2] -= 10;
	}
	else if (keycode == SDLK_KP_PLUS) //zoom in
	{
		param->eye[1] += 10;
	}
	else if (keycode == SDLK_KP_MINUS) //zoom out
	{
		param->eye[1] -= 10;
	}
	else if (keycode == SDLK_a)
	{
		eye_rotation(0.0, 0.0, param->macro.rotation_angle, param);
	}
	else if (keycode == SDLK_q)
	{
		eye_rotation(param->macro.rotation_angle, 0.0, 0.0, param);
	}
	else if (keycode == SDLK_w)
	{
		eye_rotation(-param->macro.rotation_angle, 0.0, 0.0, param);
	}
	else if (keycode == SDLK_s)
	{
		eye_rotation(0.0, 0.0, -param->macro.rotation_angle, param);
	}
	else if (keycode == SDLK_z)
	{
		eye_rotation(0.0, -param->macro.rotation_angle, 0.0, param);
	}
	else if (keycode == SDLK_x)
	{
		eye_rotation(0.0, param->macro.rotation_angle, 0.0, param);
	}
	else if (keycode == SDLK_r)
	{
		free_objects(param);
		free_lights(param);
//		rt_parser(param);
		ft_putstr("\nnumber of lights\n");
		ft_putnbr(param->num_lights);
		ft_putchar('\n');
		rt_tracer(param);
	}
	else{
		ft_putnbr(keycode);
		ft_putstr("\n_---_\n");
	}
	if (keycode != SDLK_r)
	{
		rt_tracer(param);
	}
	param->last_mv = clock();
	return (0);
}
