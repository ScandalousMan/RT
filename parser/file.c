/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 15:58:14 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/25 00:46:01 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <libft.h>
#include <json.h>

//#include <rt_objects.h>
const t_func_type		g_func_parse[] = {
	{JSTRING, &parse_jstring},
	{JOBJECT, &parse_jobject},
	{JARRAY, &parse_jarray},
	{JINT, &parse_jint},
	{JDOUBLE, &parse_jdouble},
	{JBOOL, &parse_jbool},
	{JNULL, &parse_jnull}
};

// TO DELETE (isspace)
#include <ctype.h>

//FOR PRINTF
#include <stdio.h>


//ERRNO
#include <errno.h>
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
				if ((*value = ft_strdup(json + 1)) == NULL)
				{
					perror(NULL);
					exit(EXIT_FAILURE);
				}
				return (json + i + 1) ;
			}
			++i;
		}
	}
	return (NULL);
}

char *get_key(char *json, t_jstring *key)
{
	char	tmp;
	int		i;

	i = 0;
	if (json != NULL && json[i] == '"')
	{
		++i;
		while (json[i])
		{
			if (json[i] == '"' && json[i - 1] != '\\')
			{
				tmp = json[i];
				json[i] = '\0';
				if ((*key = ft_strdup(json + 1)) == NULL)
				{
					perror(NULL);
					exit(EXIT_FAILURE);
				}
				json[i] = tmp;
				return (json + i + 1) ;
			}
			++i;
		}
	}
	return (NULL);
}

int	ft_isjint(char *json)
{
	int	i;

	i = 0;
	while (json && json[i] != '\0' && json[i] != ',' && json[i] != ']' && json[i] != '}')
	{
		if (i == 0 && json[i] == '-')
			;
		else if (ft_isdigit(json[i]) == 0)
			return (0);
		++i;
	}
	if (json && i == 1 && json[0] == '-')
		return (0);
	return (i);
}

int	ft_isjdouble(char *json)
{
	int	i;

	i = 0;
	while (json && json[i] != '\0' && json[i] != '.' && json[i] != ',' && json[i] != ']' && json[i] != '}')
	{
		if (i == 0 && json[i] == '-')
			;
		else if (ft_isdigit(json[i]) == 0)
			return (0);
		++i;
	}
	if (json && i == 1 && json[0] == '-')
		return (0);
	if (json && json[i] == '.')
	{
		++i;
		while (json && json[i] != '\0' && json[i] != ',' && json[i] != ']' && json[i] != '}')
		{
			if (ft_isdigit(json[i]) == 0)
				return (0);
			++i;
		}
	}
	return (i);
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
		else if (ft_isjint(json) > 0)
			return (JINT);
		else if (ft_isjdouble(json) > 0)
			return (JDOUBLE);
		else if (ft_strnequ("true", json, 4)
			|| ft_strnequ("false", json, 5))
			return (JBOOL);
		else if (ft_strnequ("null", json, 4))
			return (JNULL);
	}
	return (JUNKNOWN);
}

char *get_value(char *json, t_jtype *type, void **value)
{
	int	i;

	if (json == NULL)
		return (NULL);
	*type = get_type(json);
//	printf("type: %d\n", *type);
	if (*type == JUNKNOWN)
		return (NULL);
	i = 0;
	while (i < sizeof(g_func_parse) / sizeof(t_func_type))
	{
		if (g_func_parse[i].type == *type)
		{
			json = (g_func_parse[i].f)(json, value);
			printf("get_value: %s\n", json);
			break ;
		}
		++i;
	}

	//DEBUG
	if (*value)
	{
	if (*type == JSTRING)
		printf("%s\n", *value);
	else if (*type == JINT)
		printf("%i\n", (int)(((int*)(*value))[0]));
	else if (*type == JDOUBLE)
		printf("%f\n", (double)(((double*)(*value))[0]));
	else if (*type == JBOOL)
		printf("%d\n", (t_jbool)(((t_jbool*)(*value))[0]));
	else if (*type == JNULL)
		printf("%s\n", *value);
	}
	printf("%s\n", json);
	return (json);
}

char	*parse_key_value(char *json, t_jobject **obj)
{
	if (json == NULL)
		return (NULL);
	if ((*obj = (t_jobject*)malloc(sizeof(t_jobject))) == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	(*obj)->next = NULL;
	(*obj)->value = NULL;
	printf("avant get key: %s\n", json);
	json = get_key(json, &((*obj)->key));
	//if NULL error
	printf("%s\n", (char*)((*obj)->key));
	if (json && json[0] == ':')
	{
		json = get_value(json + 1, &((*obj)->type), &((*obj)->value));
		if (json == NULL)
			return (NULL);
		if (json && json[0] == ',')
			json = parse_key_value(json + 1, &((*obj)->next));
	}
	else
		return (NULL);//error
	return (json);
}

char	*parse_jint(char *json, void **value)
{
	char	tmp;
	size_t	size;
	t_jint	*number;

	if (json == NULL)
		return (NULL);
	if ((number = (t_jint*)malloc(sizeof(t_jint))) == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	size = ft_isjint(json);
	tmp = json[size];
	json[size] = '\0';
	*number = ft_atoi(json);
	*value = (void*)(number);
	json[size] = tmp;
	return (json + size);
}

char	*parse_jdouble(char *json, void **value)
{
	char		tmp;
	size_t		size;
	t_jdouble	*number;

	if (json == NULL)
		return (NULL);
	if ((number = (t_jdouble*)malloc(sizeof(t_jdouble))) == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	size = ft_isjdouble(json);
	tmp = json[size];
	json[size] = '\0';
	*number = ft_atod(json);
	*value = (void*)(number);
	json[size] = tmp;
	return (json + size);
}

char	*parse_jobject(char *json, void **value)
{
	t_jobject	*obj;

	if (json == NULL)
		return (NULL);
	obj = NULL;
	if (ft_strlen(json) >= 2)
	{
		if ((obj = (t_jobject*)malloc(sizeof(t_jobject))) == NULL)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
		if (json[0] != '{')
			return (NULL);//ERROR
		if (json[1] != '}')
			json = parse_key_value(json + 1, &obj);
		else
			json = json + 1;
		if (json == NULL || (json && json[0] != '}'))
		{
			ft_putendl("EXIT_FAILURE");
//			ft_putendl(json);
			return (NULL);
		}
	}
	*value = obj;
	return (json + 1);//ERROR
}

char	*parse_jarray_value(char *json, t_jarray **array)
{
	if (json == NULL)
		return (NULL);
	if ((*array = (t_jarray*)malloc(sizeof(t_jarray))) == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	(*array)->next = NULL;
	(*array)->value = NULL;
	json = get_value(json, &((*array)->type), &((*array)->value));
	printf("array_value: %d\n", *(int*)((*array)->value));
	if (json && json[0] == ',' && json[1] != ']')
		json = parse_jarray_value(json + 1, &((*array)->next));
	return (json);
}

char	*parse_jarray(char *json, void **value)
{
	t_jarray	*array;

	array = NULL;
	if (json == NULL)
		return (NULL);
	if (json[0] != '[')
		return (NULL);//ERROR
	if (json[1] != ']')
		json = parse_jarray_value(json + 1, &array);
	else
		json = json + 1;
	*value = array;
	if (json == NULL)
		return (NULL);
	if (json && json[0] != ']')
		return (NULL);//ERROR
	return (json + 1);
}

char	*parse_jbool(char *json, void **value)
{
	t_jbool	*b;

	if (ft_strnequ("true", json, 4) || ft_strnequ("false", json, 5))
	{
		if ((b = (t_jbool*)malloc(sizeof(t_jbool))) == NULL)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	if (ft_strnequ("true", json, 4))
	{
		*b = TRUE;
		*value = b;
		return (json + 4);
	}
	if (ft_strnequ("false", json, 5))
	{
		*b = FALSE;
		*value = b;
		return (json + 5);
	}
	return (NULL);
}

char	*parse_jnull(char *json, void **value)
{
	if (ft_strnequ("null", json, 4))
	{
		*value = NULL;
		return (json + 4);
	}
	return (NULL);
}

int	parse(char *json, t_jobject **obj)
{
	if (json && ft_strlen(json) >= 2)
	{
		if (json[0] != '{')
			return (EXIT_FAILURE);//ERROR
		json = parse_key_value(json + 1, obj);
		if (json == NULL || (json && (ft_strlen(json) != 1 || json[0] != '}')))
		{
			ft_putendl("EXIT_FAILURE");
//			ft_putendl(json);
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
				i -= c;
				c = 0;
				in_str = (in_str + 1) % 2;
			}
		}
		else if (/* ft_ */isspace(s[i]) && in_str == 0)
			c++;
		else
		{
			ft_memmove(s + i - c, s + i, ft_strlen(s + i) + 1);
			i -= c;
			c = 0;
		}
		i++;
	}
	s[i - c] = '\0';
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

void	free_lst(t_list *lst)
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
	free_lst(lst);
	
	t_jobject	*obj;
	int			retour;

	obj = NULL;
	retour = parse(json, &obj);
	free(json);
	if (!retour)
		printf("json_to_objects: %d\n", json_to_objects(obj));
	return (ret);
}

int main()
{
	read_file("rt.json");
	return (EXIT_SUCCESS);
}
