/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:55:51 by jbouille          #+#    #+#             */
/*   Updated: 2017/11/14 14:36:31 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include <stdlib.h>
#include <json_free.h>

void	free_jvalue(t_jtype type, void *value)
{
	if (type == JARRAY)
		free_jarray(value);
	else if (type == JOBJECT)
		free_jobject(value);
	else if (type != JNULL)
		free(value);
}

void	free_jarray(t_jarray *array)
{
	if (array == NULL)
		return ;
	free_jvalue(array->type, array->value);
	array->value = NULL;
	free_jarray(array->next);
	array->next = NULL;
	free(array);
	array = NULL;
}

void	free_jobject(t_jobject *obj)
{
	if (obj == NULL)
		return ;
	if (obj->key != NULL)
	{
		free(obj->key);
		obj->key = NULL;
	}
	free_jvalue(obj->type, obj->value);
	obj->value = NULL;
	free_jobject(obj->next);
	obj->next = NULL;
	free(obj);
	obj = NULL;
}
