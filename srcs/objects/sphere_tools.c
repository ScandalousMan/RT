/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 21:39:11 by malexand          #+#    #+#             */
/*   Updated: 2019/01/10 21:42:06 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	display_sphere(t_object *objs)
{
	ft_putstr("** new sphere **\n");
	ft_putstr("centre : ");
	ft_putvec(((t_sphere*)(objs->parsed))->center);
	ft_putchar('\n');
	ft_putstr("radius : ");
	ft_putnbr(((t_sphere*)(objs->parsed))->radius);
	ft_putchar('\n');
}
