#include "rt.h"

t_parse	*copy_pos_len(char *line, int pos, int len)
{
	int 	i;
	t_parse	*tmp;

	i = 0;
	if (!(tmp = (t_parse*)malloc(sizeof(t_parse))))
		return (NULL);
	tmp->str = (char*)malloc(sizeof(char) * (len + 1));
	while (tmp->str && i < len)
	{
		tmp->str[i] = line[pos + i];
		i++;
	}
	tmp->str[i] = '\0';
	tmp->next = NULL;
	tmp->list_len = 1;
	return (tmp);
}

t_parse *add_end(t_parse *config, t_parse *tmp)
{
	t_parse *copy;

	if (!tmp)
		return (config);
	copy = config;
	while (copy && copy->next)
		copy = copy->next;
	if (config)
	{
		copy->next = tmp;
		config->list_len++;
	}
	else
		config = tmp;
	return (config);
}

t_parse	*split_whitespace(char *line)
{
	t_parse *config;
	t_parse *tmp;
	int 	pos;
	int 	len;

	config = NULL;
	pos = 0;
	while (line[pos] != '\0')
	{
		len = 0;
		while (line[pos] == ' ')
			pos++;
		while (line[pos] != ' ' && line[pos] != '\0')
		{
			pos++;
			len++;
		}
		if (len)
		{
			tmp = copy_pos_len(line, pos - len, len);
			config = add_end(config, tmp);
		}
	}
	return (config);
}

t_param 	*rt_parser(t_param *param)
{
	t_light		*tmp_light;
	int			fd;
	char 		*line;
	int			count;

	count = 0;
	if (param)
	{
		param->f = FOCAL_VALUE;
		param->ia = 1.0;
		param->num_lights = 0;
		fd = open("rtv1.config", O_RDONLY);
		if (fd < 0)
			return (0);
		while (get_next_line(fd, &line) > 0)
		{
			count++;
			if (!rt_init(param, line, count))
				return (0);
			free(line);
		}
		close(fd);
	}
	tmp_light = param->lights;
	while (tmp_light)
	{
		ft_putstr("light detected,#");
		ft_putnbr(tmp_light->num);
		ft_putchar('\n');
		ft_putvec(tmp_light->src);
		ft_putstr("\n**************\n");
		tmp_light = tmp_light->next;
	}
	// while (tmp_object)
	// {
	// 	ft_putstr("object detected, type: ");
	// 	ft_putnbr(tmp_object->type);
	// 	ft_putchar('\n');
	// 	tmp_object = tmp_object->next;
	// }
	display_objects(param);
	return (param);
}