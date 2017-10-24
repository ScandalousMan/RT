/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_objects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:13:11 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/24 18:10:50 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJECTS_H
# define RT_OBJECTS_H

# include <json.h>

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
	const t_object_type	type;
	const t_key			*key;
}						t_object;

const t_key				g_common_keys[] = {
	{"type", RTSTRING, RTNULL},
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
	{RTSPHERE, g_sphere_keys},
	{RTPLAN, g_plan_keys},
	{RTCONE, g_cone_keys},
	{RTCYLINDER, g_cylinder_keys},
	{RTQUADRIC, g_quadric_keys}
};

#endif
