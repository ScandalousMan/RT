/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:01:17 by malexand          #+#    #+#             */
/*   Updated: 2017/11/14 20:23:21 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	error(int error, int send_perror, char *str)
{
	if (send_perror == 1)
	{
		ft_putstr_fd("Error \x1B[0m: ", 2);
		perror("");
	}
	else
	{
		ft_putstr_fd("Error", 2);
		ft_putstr_fd(" : ", 2);
		ft_putendl_fd(str, 2);
	}
	exit(error);
}
