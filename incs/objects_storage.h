/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_storage.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:40:52 by jbouille          #+#    #+#             */
/*   Updated: 2019/01/10 21:29:23 by vacrozet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_STORAGE_H
# define OBJECTS_STORAGE_H

# include <json.h>
# include <rt.h>

int			camera_storage(t_jobject *obj, t_param *param);
t_light		*lights_storage(t_jobject *obj);
t_object	*objects_storage(t_jobject *obj, t_param *param);
void		fill_vector(double vector[1][VEC_SIZE], t_jarray *array);

#endif
