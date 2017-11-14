/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_free.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:19:58 by jbouille          #+#    #+#             */
/*   Updated: 2017/11/14 14:22:00 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_FREE_H
# define JSON_FREE_H

# include <json.h>

void	free_jvalue(t_jtype type, void *value);
void	free_jobject(t_jobject *obj);
void	free_jarray(t_jarray *array);

#endif
