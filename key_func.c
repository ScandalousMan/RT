/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:38:39 by aguemy            #+#    #+#             */
/*   Updated: 2017/05/01 18:19:04 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_objects(t_param *param)
{
	t_object	*tmp;

	while (param && param->objects)
	{
		tmp = param->objects->next;
		free(param->objects->tmp_vec);
		if (param->objects->type == 1)
		{
			free (((t_sphere*)(param->objects->dim))->center);
			free ((t_sphere*)(param->objects->dim));
		}
		else if (param->objects->type == 2)
		{
			free (((t_plane*)(param->objects->dim))->n);
			free (((t_plane*)(param->objects->dim))->ref);
			free ((t_plane*)(param->objects->dim));
		}
		else if (param->objects->type == 3)
		{
			free (((t_cone*)(param->objects->dim))->org);
			free (((t_cone*)(param->objects->dim))->u);
			free ((t_cone*)(param->objects->dim));
		}
		else if (param->objects->type == 4)
		{
			free (((t_cylindre*)(param->objects->dim))->org);
			free (((t_cylindre*)(param->objects->dim))->u);
			free ((t_cylindre*)(param->objects->dim));
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
		free(param->lights->src);
		free(param->lights);
		param->lights = tmp;
	}
}

void	end_program(t_param *param)
{
	free(param->addr);
	free(param->img);
	mlx_destroy_window(param->mlx, param->win);
	free(param->eye);
	free(param->look);
	free(param->align);
	free(param->third);
	free(param->v);
	free(param->x);
	free(param->n);
	free(param->l);
	free(param->r);
	free(param->tmp_vec);
	free(param->i);
	free(param->rot[0]);
	free(param->rot[1]);
	free(param->rot[2]);
	free(param->rot);
	free_objects(param);
	free_lights(param);
	free(param);
	exit(0);
}

double	**rotation_matrice(double alpha, double beta, double gamma, t_param *param)
{
	if (param->rot && param->rot[0] && param->rot[1] && param->rot[2])
	{
		alpha = alpha * M_PI / 180.0;
		beta = beta * M_PI / 180.0;
		gamma = gamma * M_PI / 180.0;
		ft_putstr("\nalpha:\n");
		ft_putdbl(alpha);
		ft_putstr("\nbeta :\n");
		ft_putdbl(beta);
		ft_putstr("\ngamma:\n");
		ft_putdbl(gamma);
		ft_putchar('\n');
		param->rot[0][0] = cos(beta) * cos(gamma);
		param->rot[0][1] = -1.0 * cos(beta) * sin(gamma);
		param->rot[0][2] = sin(beta);
		param->rot[1][0] = sin(alpha) * sin(beta) * cos(gamma) + cos(alpha) * sin(gamma);
		param->rot[1][1] = cos(alpha) * cos(gamma) - sin(alpha) * sin(beta) * sin(gamma);
		param->rot[1][2] = -1.0 * sin(alpha) * cos(beta);
		param->rot[2][0] = sin(alpha) * sin(gamma) - cos(alpha) * sin(beta) * cos(gamma);
		param->rot[2][1] = cos(alpha) * sin(beta) * sin(gamma) + sin(alpha) * cos(gamma);
		param->rot[2][2] = cos(alpha) * cos(beta);
		return param->rot;
	}
	else
		return NULL;
}

void	eye_rotation(double alpha, double beta, double gamma, t_param *param)
{
	rotation_matrice(alpha, beta, gamma, param);
	ft_putstr("\n1st line - rot\n");
	ft_putvec(param->rot[0]);
	ft_putstr("\n2nd line - rot\n");
	ft_putvec(param->rot[1]);
	ft_putstr("\n3rd line - rot\n");
	ft_putvec(param->rot[2]);
	ft_putstr("\nlook1:\n");
	ft_putvec(param->look);
	matrice_product(param->rot, param->look, param->look);
	ft_putstr("\nlook2:\n");
	ft_putvec(param->look);
	ft_putstr("\nalign:\n");
	ft_putvec(param->align);
	ft_putchar('\n');
	matrice_product(param->rot, param->align, param->align);
	vec_to_unit_norm(vector_product(param->align, param->look, param->third));
}

int		my_key_func(int keycode, t_param *param)
{
	if (keycode == ESCAPE)
		end_program(param);
	else if (keycode == RIGHT) //droite
	{
		param->eye[0] += 10;
	}
	else if (keycode == LEFT) //gauche
	{
		param->eye[0] -= 10;
	}
	else if (keycode == TOP) //haut
	{
		param->eye[2] += 10;
	}
	else if (keycode == BOTTOM) //bas
	{
		param->eye[2] -= 10;
	}
	else if (keycode == ZOOM_IN) //zoom in
	{
		param->eye[1] += 10;
	}
	else if (keycode == ZOOM_OUT) //zoom out
	{
		param->eye[1] -= 10;
	}
	else if (keycode == 0)
	{
		eye_rotation(0.0, 0.0, ROTATION, param);
	}
	else if (keycode == 13)
	{
		eye_rotation(ROTATION, 0.0, 0.0, param);
	}
	else if (keycode == 1)
	{
		eye_rotation(-ROTATION, 0.0, 0.0, param);
	}
	else if (keycode == 2)
	{
		eye_rotation(0.0, 0.0, -ROTATION, param);
	}
	else if (keycode == 6)
	{
		eye_rotation(0.0, -ROTATION, 0.0, param);
	}
	else if (keycode == 7)
	{
		eye_rotation(0.0, ROTATION, 0.0, param);
	}
	else if (keycode == BRIGHTNESS)
	{
		param->bright = 1 - param->bright;
		ft_putstr("new param->bright: ");
		ft_putnbr(param->bright);
		ft_putstr("\n");
	}
	else if (keycode == REFRESH)
	{
		ft_bzero(param->addr, HEIGHT * WIDTH * 4);
		free_objects(param);
		free_lights(param);
		rt_parser(param);
		rt_filler(param);
	}
	else{
		ft_putnbr(keycode);
		ft_putstr("\n_---_\n");
	}
	if (keycode != REFRESH)
	{
		ft_bzero(param->addr, HEIGHT * WIDTH * 4);
		rt_filler(param);
	}
	return (0);
}
