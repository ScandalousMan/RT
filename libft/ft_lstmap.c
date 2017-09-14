/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:02:31 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/24 13:32:57 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*tmp;
	t_list	*out;

	if (lst != NULL && f)
	{
		if (!(tmp = ft_lstnew(lst->content, lst->content_size)))
			return (NULL);
		res = f(tmp);
		out = res;
		while (lst->next != NULL)
		{
			if (!(tmp = ft_lstnew(lst->next->content, lst->next->content_size)))
				return (NULL);
			res->next = f(tmp);
			lst = lst->next;
			res = res->next;
		}
		return (out);
	}
	else
		return (NULL);
}
