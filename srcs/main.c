/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsalex <itsalex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:02:46 by malexand          #+#    #+#             */
/*   Updated: 2018/08/12 19:01:58 by itsalex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation.h"
#include "rt.h"
#include <rt_parser.h>

char	*concat_filename(int ac, char* str)
{
	char	*filename;
	int		len;

	if (ac == 2)
	{
		len = ft_strlen("scenes/");
		if (!(filename = (char*)malloc(sizeof(char) * (len + ft_strlen(str) + 1))))
			return (NULL);
		ft_memcpy((void*)filename, (void*)"scenes/", len);
		filename[len] = '\0';
		ft_strcat(filename, str);
	}
	else
	{
		len = ft_strlen("scenes/rtv1.json");
		if (!(filename = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		ft_memcpy((void*)filename, (void*)"scenes/rtv1.json", len);
		filename[len] = '\0';
	}
	return (filename);
}

int		main(int ac, char **av)
{
	t_param	*param;
	char	*filename;

	filename = concat_filename(ac, av[1]);
	if (!(param = struct_create()))
		return (-1);
	param->to_pix = 0;//todo change
	param->last_mv = clock();//todo change
	param->start = clock();//TODO delete
	if ((param->graph = graph_init()) == NULL)
		error(0, 0, "Can't allocate graph struct");
	if (!rt_parser(param, filename))
		return (1);
	sdl_init(param->graph);
	launch_threads(param);
	while (param->quit == FALSE)
	{
		sdl_pull_evts(param);
		if (param->to_pix && ((double)(clock() - param->last_mv) / (double)CLOCKS_PER_SEC) > 0.4)
		{
			param->to_pix = 0;
			param->refresh = 1;
		}
		nukl_gui(param);
		if (param->refresh == 1)
		{
			launch_threads(param);
			sdl_draw(param->graph);
			param->end = clock();//TODO delete
			printf("Render %.5lf secondes...\n", (double)(param->end - param->start) / CLOCKS_PER_SEC);
			save_img(param);
			param->refresh = 0;
		}
	}
	sdl_quit(param->graph);
	end_program(param);
	return (0);
}
