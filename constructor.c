/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:57:42 by aguemy            #+#    #+#             */
/*   Updated: 2017/06/02 15:18:21 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// NE PAS OUBLIER DE VERIFIER QUE LA NORME DES VECTEURS DIRECTEURS N'EST PAS NULLE

t_param			*struct_create(void *mlx, void *win, void *img, char *addr)
{
	t_param		*param;

	if (!(param = (t_param*)malloc(sizeof(t_param))))
		return (NULL);
	if (!(param->v = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(param->x = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(param->n = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(param->l = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(param->r = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(param->tmp_vec = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	if (!(param->i = (int*)malloc(sizeof(int) * 2)))
		return (NULL);
	param->mlx = mlx;
	param->win = win;
	param->img = img;
	param->addr = addr;
	param->bright = 1;
	param->epsilon = EPSILON;
	param->objects = NULL;
	param->lights = NULL;
	param->tmp_object = NULL;
	param->tmp_light = NULL;
	param->current_object = NULL;
	param->intersect_object = NULL;
	if (!(param->rot = (double**)malloc(sizeof(double*) * 3)))
		return NULL;
	if (!(param->rot[0] = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	if (!(param->rot[1] = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	if (!(param->rot[2] = (double*)malloc(sizeof(double) * 3)))
		return NULL;
	return (param);
}

t_light			*add_light(t_light **lights, double *src, double i, int col)
{
	t_light		*prev;
	t_light		*new;
	int			num;

	if (!src)
		return (NULL);
	new = *lights;
	prev = NULL;
	num = 0;
	while (new)
	{
		num++;
		prev = new;
		new = new->next;
	}
	if (!(new = (t_light*)malloc(sizeof(t_light))))
		return (NULL);
	new->src = src;
	new->i = i;
	new->col = col;
	new->num = num;
	new->next = NULL;
	if (*lights && prev)
		prev->next = new;
	else
		*lights = new;
	return (new);
}

t_object		*object_constructor(t_param *param)
{
	int			num;
	t_object	*prev;

	param->tmp_object = param->objects;
	num = 1;
	prev = NULL;
	while (param->tmp_object)
	{
		num++;
		prev = param->tmp_object;
		param->tmp_object = param->tmp_object->next;
	}
	if (!(param->tmp_object = (t_object*)malloc(sizeof(t_object))))
		return (NULL);
	// if (!(param->tmp_object->translate = (double*)malloc(sizeof(double) * 3)))
	// 	return (NULL);
	// if (!(param->tmp_object->rotate = (double*)malloc(sizeof(double) * 3)))
	// 	return (NULL);
	param->tmp_object->num = num;
	if (!(param->tmp_object->tmp_vec = (double*)malloc(sizeof(double) * 3)))
		return (NULL);
	param->tmp_object->next = NULL;
	if (param->objects && prev)
		prev->next = param->tmp_object;
	else
		param->objects = param->tmp_object;
	return (param->tmp_object);
}

t_object		*add_sphere(t_param *param, double *center, double radius)
{
	t_object	*tmp;

	tmp = NULL;
	if (!center)
		return (NULL);
	tmp = object_constructor(param);
	if (tmp)
	{
		tmp->type = 1;
		tmp->kd = 0.55;
		tmp->ks = 0.25;
		tmp->phong = SPECULAR_EXP;
		if (!(tmp->dim = ((t_sphere*)malloc(sizeof(t_sphere)))))
			return (NULL);
		((t_sphere*)(tmp->dim))->center = center;
		((t_sphere*)(tmp->dim))->radius = radius;
	}
	return (tmp);
}

t_object		*add_plane(t_param *param, double *n, double *ref)
{
	t_object	*tmp;

	tmp = NULL;
	if (!ref || !n)
		return (NULL);
	tmp = object_constructor(param);
	if (tmp)
	{
		tmp->type = 2;
		tmp->kd = 0.55;
		tmp->ks = 0.0;
		tmp->phong = SPECULAR_EXP;
		if (!(tmp->dim = ((t_plane*)malloc(sizeof(t_plane)))))
			return (NULL);
		((t_plane*)(tmp->dim))->ref = ref;
		((t_plane*)(tmp->dim))->n = vec_to_unit_norm(n);
	}
	return (tmp);
}

t_object		*add_cone(t_param *param, double *org, double *u,
		double angle)
{
	t_object	*tmp;

	tmp = NULL;
	if (!org || !u || M_PI / 2 <= angle || -M_PI / 2 >= angle)
		return (NULL);
	tmp = object_constructor(param);
	if (tmp)
	{
		tmp->type = 3;
		tmp->kd = 0.55;
		tmp->ks = 0.25;
		tmp->phong = SPECULAR_EXP;
		if (!(tmp->dim = ((t_cone*)malloc(sizeof(t_cone)))))
			return (NULL);
		((t_cone*)(tmp->dim))->org = org;
		((t_cone*)(tmp->dim))->u = vec_to_unit_norm(u);
		((t_cone*)(tmp->dim))->angle = angle;
	}
	return (tmp);
}

t_object		*add_cylindre(t_param *param, double *org, double *u, double radius)
{
	t_object	*tmp;

	tmp = NULL;
	if (!org || !u)
		return (NULL);
	tmp = object_constructor(param);
	if (tmp)
	{
		tmp->type = 4;
		tmp->kd = 0.55;
		tmp->ks = 0.25;
		tmp->phong = SPECULAR_EXP;
		if (!(tmp->dim = ((t_cylindre*)malloc(sizeof(t_cylindre)))))
			return (NULL);
		((t_cylindre*)(tmp->dim))->org = org;
		((t_cylindre*)(tmp->dim))->radius = radius;
		((t_cylindre*)(tmp->dim))->u = vec_to_unit_norm(u);
	}
	return (tmp);
}