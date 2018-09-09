/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacrozet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:47:01 by vacrozet          #+#    #+#             */
/*   Updated: 2018/09/09 16:56:00 by vacrozet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	cylindre_first_term(t_object *tmp, double *to)
{
	return ((((t_cylindre*)(tmp->dim))->u[2] * to[1] -
			((t_cylindre*)(tmp->dim))->u[1] * to[2]) *
			(((t_cylindre*)(tmp->dim))->u[2] * to[1] -
			((t_cylindre*)(tmp->dim))->u[1] * to[2]) +
			(((t_cylindre*)(tmp->dim))->u[0] * to[2] -
			((t_cylindre*)(tmp->dim))->u[2] * to[0]) *
			(((t_cylindre*)(tmp->dim))->u[0] * to[2] -
			((t_cylindre*)(tmp->dim))->u[2] * to[0]) +
			(((t_cylindre*)(tmp->dim))->u[1] * to[0] -
			((t_cylindre*)(tmp->dim))->u[0] * to[1]) *
			(((t_cylindre*)(tmp->dim))->u[1] * to[0] -
			((t_cylindre*)(tmp->dim))->u[0] * to[1]));
}

double	cylindre_second_term(t_object *tmp, double *to)
{
	return (2.0 * ((((t_cylindre*)(tmp->dim))->u[2] * to[1] -
				((t_cylindre*)(tmp->dim))->u[1] * to[2]) *
				(((t_cylindre*)(tmp->dim))->u[2] * tmp->tmp_vec[1] -
				((t_cylindre*)(tmp->dim))->u[1] * tmp->tmp_vec[2]) +
				(((t_cylindre*)(tmp->dim))->u[0] * to[2] -
				((t_cylindre*)(tmp->dim))->u[2] * to[0]) *
				(((t_cylindre*)(tmp->dim))->u[0] * tmp->tmp_vec[2] -
				((t_cylindre*)(tmp->dim))->u[2] * tmp->tmp_vec[0]) +
				(((t_cylindre*)(tmp->dim))->u[1] * to[0] -
				((t_cylindre*)(tmp->dim))->u[0] * to[1]) *
				(((t_cylindre*)(tmp->dim))->u[1] * tmp->tmp_vec[0] -
				((t_cylindre*)(tmp->dim))->u[0] * tmp->tmp_vec[1])));
}

double	cylindre_third_term(t_object *tmp)
{
	return ((((t_cylindre*)(tmp->dim))->u[2] * tmp->tmp_vec[1] -
			((t_cylindre*)(tmp->dim))->u[1] * tmp->tmp_vec[2]) *
			(((t_cylindre*)(tmp->dim))->u[2] * tmp->tmp_vec[1] -
			((t_cylindre*)(tmp->dim))->u[1] * tmp->tmp_vec[2]) +
			(((t_cylindre*)(tmp->dim))->u[0] * tmp->tmp_vec[2] -
			((t_cylindre*)(tmp->dim))->u[2] * tmp->tmp_vec[0]) *
			(((t_cylindre*)(tmp->dim))->u[0] * tmp->tmp_vec[2] -
			((t_cylindre*)(tmp->dim))->u[2] * tmp->tmp_vec[0]) +
			(((t_cylindre*)(tmp->dim))->u[1] * tmp->tmp_vec[0] -
			((t_cylindre*)(tmp->dim))->u[0] * tmp->tmp_vec[1]) *
			(((t_cylindre*)(tmp->dim))->u[1] * tmp->tmp_vec[0] -
			((t_cylindre*)(tmp->dim))->u[0] * tmp->tmp_vec[1]) -
			((t_cylindre*)(tmp->dim))->radius *
			((t_cylindre*)(tmp->dim))->radius);
}
