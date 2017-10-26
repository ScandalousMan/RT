/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:40:48 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/26 23:44:49 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include <json_parse.h>
int	json_to_objects(t_jobject *obj);
#include <file.h>

#define MY_GLOBALS
#include <rt_objects.h>
int main(int ac, char **av)
{
	char		*json;
	t_jobject	*obj;
	int			ret;

	if (!(json = read_file("../rtv1.json")))
		return (EXIT_FAILURE);
	obj = NULL;
	ret = json_parse(json, &obj);
	free(json);
	if (!ret)
		printf("json_to_objects: %d\n", json_to_objects(obj));
	return (ret);
}
