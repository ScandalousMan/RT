/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:35:54 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/24 11:31:47 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	if ((unsigned char)*s1 == (unsigned char)*s2 && (unsigned char)*s2 == '\0')
		return (0);
	else if (((unsigned char)*s1 == (unsigned char)*s2) && n > 1)
		return (ft_strncmp(s1 + 1, s2 + 1, n - 1));
	else
		return ((unsigned char)*s1 - (unsigned char)*s2);
}
