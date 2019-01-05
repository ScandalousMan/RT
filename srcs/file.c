/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 15:58:14 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/29 18:57:54 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <libft.h>
#include <json.h>
#include <json_parse.h>

static size_t	get_string_size(t_list *lst)
{
	size_t	size;
	t_list	*tmp;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		size += tmp->content_size - 1;
		tmp = tmp->next;
	}
	return (size + 1);
}

char			*lst_to_string(t_list *lst)
{
	char	*s;
	size_t	size;
	t_list	*tmp;

	size = get_string_size(lst);
	if ((s = (char*)malloc(size)) == NULL)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		ft_strlcat(s, tmp->content, size);
		tmp = tmp->next;
	}
	s[size - 1] = '\0';
	return (s);
}

int				read_lines(int fd, t_list **lst)
{
	char	*line;
	int		ret;
	t_list	*tmp;
	t_list	*tmp_prev;

	tmp = NULL;
	tmp_prev = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		stringify(line);
		if ((tmp = ft_lstnew((const void*)line, ft_strlen(line) + 1)) == NULL)
			return (EXIT_FAILURE);
		if (tmp_prev == NULL)
			ft_lstadd(lst, tmp);
		else
			ft_lstadd(&(tmp_prev->next), tmp);
		tmp_prev = tmp;
		free(line);
	}
	return (EXIT_SUCCESS);
}

void			free_lst(t_list *lst)
{
	t_list *tmp;
	t_list *to_free;

	tmp = lst;
	while (tmp != NULL)
	{
		free(tmp->content);
		tmp->content = NULL;
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
		to_free = NULL;
	}
}

char			*read_file(const char *path)
{
	int		fd;
	char	*json;
	t_list	*lst;

	lst = NULL;
	json = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	if (read_lines(fd, &lst))
		return (NULL);
	if (close(fd) != 0)
		return (NULL);
	json = lst_to_string(lst);
	free_lst(lst);
	return (json);
}
