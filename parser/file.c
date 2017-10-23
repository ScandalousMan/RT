/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 15:58:14 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/23 15:31:54 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <libft.h>
#include <json.h>

// TO DELETE (isspace)
#include <ctype.h>

/*					DEBUG													  */

void	print_lst(t_list *lst)
{
	ft_putendl((char*)(lst->content));
	ft_putnbr((int)(lst->content_size));
	ft_putchar('\n');
}

/*					END														  */

char	*parse_jstring(char *json, void **value)
{
	int	i;

	i = 1;
	if (json != NULL && json[i] != '\0')
	{
		++i;
		while (json[i])
		{
			if (json[i] == '"' && json[i - 1] != '\\')
			{
				json[i] = '\0';
				*value = json + 1;
				return (json + i + 1) ;
			}
			++i;
		}
	}
	return (NULL);
}

char *get_key(char *json, t_jstring *key)
{
	int	i;

	i = 0;
	if (json != NULL && json[i] != '\0')
	{
		++i;
		while (json[i])
		{
			if (json[i] == '"' && json[i - 1] != '\\')
			{
				json[i] = '\0';
				*key = json + 1;
				return (json + i + 1) ;
			}
			++i;
		}
	}
	return (NULL);
}

t_jtype	get_type(char *json)
{
	if (json)
	{
		if (json[0] == '"')
			return (JSTRING);
		else if (json[0] == '[')
			return (JARRAY);
		else if (json[0] == '{')
			return (JOBJECT);
//		else if ()
	}
	return (JUNKNOWN);
}

char *get_value(char *json, t_jtype *type, void **value)
{
	int	i;

	*type = get_type(json);
	i = 0;
	while (i < sizeof(g_func_parse) / sizeof(t_func_type))
	{
		if (g_func_parse[i].type == *type)
		{
			json = (g_func_parse[i].f)(json, value);
		}
		++i;
	}
	ft_putendl(*value);
	ft_putendl(json);
	return (json);
}

char	*parse_key_value(char *json, t_jobject *obj)
{
	if (json == NULL)
		return (NULL);
	if ((obj = (t_jobject*)malloc(sizeof(t_jobject))) == NULL)
		return (NULL); //EXIT ?
	obj->next = NULL;
	json = get_key(json, &(obj->key));
	//if NULL error
	ft_putendl((char*)(obj->key));
	if (json && json[0] == ':')
	{
		json = get_value(json + 1, &(obj->type), &(obj->value));
		if (json && json[0] == ',')
			json = parse_key_value(json + 1, obj->next);
	}
	else
		;//error
	return (json);
}

char *parse_jobject(char *json, void **value)
{

	return (json);
}

int	parse(char *json, t_jobject **obj)
{
	if (ft_strlen(json) >= 2)
	{
		if (json[0] != '{')
			return (EXIT_FAILURE);//ERROR
		json = parse_key_value(json + 1, *obj);
		if (ft_strlen(json) != 1 || json[0] != '}')
		{
			ft_putendl("EXIT_FAILURE");
			ft_putendl(json);
			return (EXIT_FAILURE);//ERROR
		}
	}
	return (EXIT_SUCCESS);
}

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
		else if (/* ft_ */isspace(s[i]) && in_str == 0)
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

	char *json = lst_to_string(lst);
	t_jobject	*obj;

	obj = NULL;
	parse(json, &obj);
	return (ret);
}

int main()
{
	read_file("test.json");
	return (EXIT_SUCCESS);
}
