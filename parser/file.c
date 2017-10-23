/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 15:58:14 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/23 10:09:36 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

/*					DEBUG													  */

void	print_lst(t_list *lst)
{
	ft_putendl((char*)(lst->content));
	ft_putnbr((int)(lst->content_size));
	ft_putchar('\n');
}

/*					END														  */

static const size_t get_string_size(t_list *lst)
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

char	*lst_to_string(t_list *lst)
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
	return (s);
}

char	*clear_string(char *s)
{
	int		i;
	size_t	c;
	int		in_str;

	in_str = 0;
	i = 0;
	c = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			if (i > 0 && s[i - 1] == '\\')
				;
			else
			{
				ft_memmove(s + i - c, s + i, ft_strlen(s + i) + 1);
				c = 0;
				in_str = (in_str + 1) % 2;
			}
		}
		else if (isspace(s[i])/* == ' '*/ && in_str == 0)
			c++;
		else
		{
			ft_memmove(s + i - c, s + i, ft_strlen(s + i) + 1);
			c = 0;
		}
		i++;
	}
	return (s);
}

int	read_lines(int fd, t_list **lst)
{
	char	*line;
	int		ret;
	t_list	*tmp;
	t_list	*tmp_prev;

	tmp = NULL;
	tmp_prev = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_putendl(line);
		if ((tmp = ft_lstnew((const void*)clear_string(line), ft_strlen(line) + 1)) == NULL)
			return (EXIT_FAILURE);
		if (tmp_prev == NULL)
			ft_lstadd(lst, tmp);
		else
			ft_lstadd(&(tmp_prev->next), tmp);
		tmp_prev = tmp;
	}
	return (EXIT_SUCCESS);
}

int read_file(const char *path)
{
	int		fd;
	int		ret;
	t_list	*lst;

	ret = EXIT_SUCCESS;
	lst = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	ret = read_lines(fd, &lst);
	if (close(fd) != 0)
		return (EXIT_FAILURE);
	ft_lstiter(lst, &print_lst);
	ft_putendl(lst_to_string(lst));
	return (ret);
}

int main()
{
	read_file("test.json");
	return (EXIT_SUCCESS);
}
