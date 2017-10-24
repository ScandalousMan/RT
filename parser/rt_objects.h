/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_objects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:13:11 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/25 00:48:34 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJECTS_H
# define RT_OBJECTS_H

# include <json.h>
# include <stddef.h>

typedef enum			e_object_type
{
	RTSPHERE,
	RTPLAN,
	RTCONE,
	RTCYLINDER,
	RTQUADRIC
}						t_object_type;

typedef enum			e_rt_type
{
	RTNULL,
	RTSTRING,
	RTDOUBLE,
	RTCHAR,
	RTINT,
	RTARRAY,
	RTOBJECT,
	RTVECTOR
}						t_rt_type;

typedef struct			s_key
{
	const char			*key;
	const t_rt_type		type;
	const t_rt_type		content_type;
}						t_key;

typedef struct			s_object
{
	const char			*name;
	const t_object_type	type;
	const t_key			*key;
	const size_t		size;
}						t_object;

# define RT_OBJECT_TYPE "type"

const t_key				g_common_keys[] = {
	{RT_OBJECT_TYPE, RTSTRING, RTNULL},
	{"color", RTVECTOR, RTCHAR},
	{"kd", RTDOUBLE, RTNULL},
	{"ks", RTDOUBLE, RTNULL},
	{"texture", RTSTRING, RTNULL}
};

const t_key				g_plan_keys[] = {
	{"normal", RTVECTOR, RTDOUBLE},
	{"point", RTVECTOR, RTDOUBLE}
};

const t_key				g_sphere_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"radius", RTDOUBLE, RTNULL}
};

const t_key				g_cone_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"angle", RTINT, RTNULL},
	{"vector", RTVECTOR, RTDOUBLE}
};

const t_key				g_cylinder_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"radius", RTINT, RTNULL},
	{"vector", RTVECTOR, RTDOUBLE}
};

const t_key				g_quadric_keys[] = {
	{"tmp", RTNULL, RTNULL}
};

const t_key				g_main_object_keys[] = {
	{"objects", RTARRAY, RTOBJECT}
};

const t_object			g_objects[] = {
	{"sphere", RTSPHERE, g_sphere_keys, sizeof(g_sphere_keys) / sizeof(t_key)},
	{"plan", RTPLAN, g_plan_keys, sizeof(g_plan_keys) / sizeof(t_key)},
	{"cone", RTCONE, g_cone_keys, sizeof(g_cone_keys) / sizeof(t_key)},
	{"cylinder", RTCYLINDER, g_cylinder_keys, sizeof(g_cylinder_keys) / sizeof(t_key)},
	{"quadric", RTQUADRIC, g_quadric_keys, sizeof(g_quadric_keys) / sizeof(t_key)}
};

#endif
