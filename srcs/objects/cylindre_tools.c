/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 21:37:03 by malexand          #+#    #+#             */
/*   Updated: 2019/01/10 22:35:14 by malexand         ###   ########.fr       */
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
		((t_cylindre*)(tmp->dim))->u[2] *
		to[0]) * (((t_cylindre*)(tmp->dim))->u[0] * tmp->tmp_vec[2] -
		((t_cylindre*)(tmp->dim))->u[2] * tmp->tmp_vec[0]) +
		(((t_cylindre*)(tmp->dim))->u[1] * to[0] -
		((t_cylindre*)(tmp->dim))->u[0] *
		to[1]) * (((t_cylindre*)(tmp->dim))->u[1] * tmp->tmp_vec[0] -
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

void	display_cylindre(t_object *objs)
{
	ft_putstr("** new cylindre **\n");
	ft_putstr("origin : ");
	ft_putvec(((t_cylindre*)(objs->parsed))->org);
	ft_putchar('\n');
	ft_putstr("normal : ");
	ft_putvec(((t_cylindre*)(objs->parsed))->u);
	ft_putchar('\n');
	ft_putstr("radius : ");
	ft_putnbr(((t_cylindre*)(objs->parsed))->radius);
	ft_putchar('\n');
}
