/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_storage.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:40:52 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/27 16:49:56 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_STORAGE_H
# define OBJECTS_STORAGE_H

# include <json.h>
# include <rt.h>

t_light		*lights_storage(t_jobject *obj);
t_object	*objects_storage(t_jobject *obj, t_param *param);

#endif
