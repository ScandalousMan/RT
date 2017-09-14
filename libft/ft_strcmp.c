/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:33:22 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/24 12:10:54 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if ((unsigned char)*s1 == (unsigned char)*s2 && (unsigned char)*s2 == '\0')
		return (0);
	else if ((unsigned char)*s1 == (unsigned char)*s2)
		return (ft_strcmp(s1 + 1, s2 + 1));
	else
		return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
