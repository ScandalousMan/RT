/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:32:22 by jbouille          #+#    #+#             */
/*   Updated: 2018/12/04 17:59:14 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include <rt_objects.h>
#include <stddef.h>
#include <libft.h>
#include <objects_storage.h>

int	is_type_3(void *value, t_jtype jtype, t_rt_type type)
{
	if (type == RTN)
		return ((jtype == JINT && *((int*)value) >= 1)
				|| (jtype == JDOUBLE && *((double*)value) >= 1.0));
	else if (type == RTSIGN)
		return (jtype == JSTRING && ft_strlen((char*)value) == 1 &&
			(((char*)value)[0] == '-' || ((char*)value)[0] == '+'));
	else if (type == RTLIMIT)
		return (jtype == JOBJECT
				&& is_object((t_jobject*)value, g_limit_keys,
					RT_KEYS_SIZE(g_limit_keys), 0));
	else if (type == RTLIGHTTYPE)
		return (jtype == JSTRING && (ft_strequ((char*)value, "spot") ||
			ft_strequ((char*)value, "parallel")));
	else
		return (0);
}

int	is_type_2(void *value, t_jtype jtype, t_rt_type type, t_rt_type subtype)
{
	if (type == RTOBJECT)
		return (jtype == JOBJECT && is_rt_object((t_jobject*)value));
	else if (type == RTVECTOR)
		return (jtype == JARRAY && jarray_len((t_jarray*)value) == 3
		&& check_subtypes((t_jarray*)value, subtype));
	else if (type == RTCOEF)
		return ((jtype == JINT && *((int*)value) >= 0 && *((int*)value) <= 1) ||
			(jtype == JDOUBLE && *((double*)value) >= 0.0 &&
					*((double*)value) <= 1.0));
	else if (type == RTANGLE)
		return ((jtype == JINT && *((int*)value) >= 0 && *((int*)value) < 90) ||
			(jtype == JDOUBLE && *((double*)value) >= 0.0 &&
					*((double*)value) < 90.0));
	else if (type == RTTEXTURE)
		return (jtype == JOBJECT
				&& is_object((t_jobject*)value, g_texture_keys,
					RT_KEYS_SIZE(g_texture_keys), 0));
	else
		return (is_type_3(value, jtype, type));
}

int	is_type(void *value, t_jtype jtype, t_rt_type type, t_rt_type subtype)
{
	if (type == RTNULL)
		return (jtype == JNULL);
	else if (type == RTSTRING)
		return (jtype == JSTRING);
	else if (type == RTDOUBLE)
		return (jtype == JDOUBLE || jtype == JINT);
	else if (type == RTUDOUBLE)
		return ((jtype == JINT && *((int*)value) >= 0) ||
			(jtype == JDOUBLE && *((double*)value) >= 0.0));
	else if (type == RTCHAR)
		return (jtype == JINT && *((int*)value) >= 0 && *((int*)value) <= 255);
	else if (type == RTINT)
		return (jtype == JINT);
	else if (type == RTARRAY)
		return (jtype == JARRAY && check_subtypes((t_jarray*)value, subtype));
	else if (type == RTCAMERA)
		return (jtype == JOBJECT
				&& is_object((t_jobject*)value, g_camera_keys,
					RT_KEYS_SIZE(g_camera_keys), 0));
	else if (type == RTLIGHT)
		return (jtype == JOBJECT && is_object((t_jobject*)value, g_light_keys,
			RT_KEYS_SIZE(g_light_keys), 0));
	else
		return (is_type_2(value, jtype, type, subtype));
}
