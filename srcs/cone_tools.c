/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacrozet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:11:26 by vacrozet          #+#    #+#             */
/*   Updated: 2018/09/09 16:11:59 by vacrozet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	cone_first_term(t_object *tmp, double *to)
{
	if (tmp)
		return (scalar_product(to, to) - ((1.0 +
					tan(((t_cone*)(tmp->dim))->angle) *
					tan(((t_cone*)(tmp->dim))->angle)) *
					scalar_product(to, ((t_cone*)(tmp->dim))->u) *
					scalar_product(to, ((t_cone*)(tmp->dim))->u)));
	else
		return (0);
}

double	cone_second_term(t_object *tmp, double *to, double *x)
{
	if (tmp)
		return (2.0 * (scalar_product(to, x) - (1.0 +
						tan(((t_cone*)(tmp->dim))->angle) *
						tan(((t_cone*)(tmp->dim))->angle)) *
					scalar_product(to, ((t_cone*)(tmp->dim))->u) *
					scalar_product(x, ((t_cone*)(tmp->dim))->u)));
	else
		return (0);
}

double	cone_third_term(t_object *tmp, double *x)
{
	if (tmp)
		return (scalar_product(x, x)
				- (1.0 + tan(((t_cone*)(tmp->dim))->angle) *
					tan(((t_cone*)(tmp->dim))->angle)) *
				scalar_product(x, ((t_cone*)(tmp->dim))->u) *
				scalar_product(x, ((t_cone*)(tmp->dim))->u));
	else
		return (0);
}
