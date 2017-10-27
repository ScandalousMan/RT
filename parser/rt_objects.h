/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_objects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:13:11 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/27 17:22:43 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJECTS_H
# define RT_OBJECTS_H

# include <json.h>
# include <stddef.h>
# include <rt.h>

typedef enum			e_object_type
{
	RTSPHERE=1,
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
	RTUDOUBLE,
	RTCHAR,
	RTINT,
	RTARRAY,
	RTCAMERA,
	RTLIGHT,
	RTOBJECT,
	RTVECTOR,
	RTCOEF,
	RTANGLE,
	RTTEXTURE,
	RTN
}						t_rt_type;

typedef struct			s_key
{
	const char			*key;
	const t_rt_type		type;
	const t_rt_type		content_type;
}						t_key;

typedef struct			s_object_def
{
	const char			*name;
	const t_object_type	type;
	const t_key			*key;
	const size_t		size;
	void				*(*fill)(t_jobject*, t_param*);
}						t_object_def;

# define RT_OBJECT_TYPE		"type"
# define CAMERA_KEY			"camera"
# define LIGHTS_KEY			"lights"
# define OBJECTS_KEY		"objects"
# define RT_KEYS_SIZE(keys)	(sizeof(keys) / sizeof(t_key))

# ifdef MY_GLOBALS

const t_key				g_common_keys[] = {
	{RT_OBJECT_TYPE, RTSTRING, RTNULL},
	{"color", RTVECTOR, RTCHAR},
	{"kd", RTCOEF, RTNULL},
	{"ks", RTCOEF, RTNULL},
	{"texture", RTTEXTURE, RTNULL},
	{"transparency", RTCOEF, RTNULL},
	{"reflection", RTCOEF, RTNULL},
	{"n", RTN, RTNULL},
	{"thickness", RTCOEF, RTNULL},
	{"translation", RTVECTOR, RTDOUBLE},
	{"rotation", RTVECTOR, RTDOUBLE}
};

const t_key				g_plan_keys[] = {
	{"normal", RTVECTOR, RTDOUBLE},
	{"point", RTVECTOR, RTDOUBLE}
};

const t_key				g_sphere_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"radius", RTUDOUBLE, RTNULL}
};

const t_key				g_cone_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"angle", RTDOUBLE, RTNULL},
	{"vector", RTVECTOR, RTDOUBLE}
};

const t_key				g_cylinder_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"radius", RTUDOUBLE, RTNULL},
	{"vector", RTVECTOR, RTDOUBLE}
};

const t_key				g_quadric_keys[] = {
	{"tmp", RTNULL, RTNULL}
};

const t_key				g_camera_keys[] = {
	{"eye", RTVECTOR, RTDOUBLE},
	{"look", RTVECTOR, RTDOUBLE},
	{"align", RTVECTOR, RTDOUBLE},
};

const t_key				g_light_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"color", RTVECTOR, RTCHAR},
	{"intensity", RTCOEF, RTNULL},
};

const t_key				g_main_object_keys[] = {
	{CAMERA_KEY, RTCAMERA, RTNULL},
	{LIGHTS_KEY, RTARRAY, RTLIGHT},
	{OBJECTS_KEY, RTARRAY, RTOBJECT}
};

const t_key				g_texture_keys[] = {
	{RT_OBJECT_TYPE, RTSTRING, RTNULL},
	{"name", RTSTRING, RTNULL},
};

/* TODO CHANGE FUNCTIONS DECLARATIONS */
void	*fill_sphere	(t_jobject *jobj, t_param *param);
void	*fill_plane		(t_jobject *jobj, t_param *param);
void	*fill_cone		(t_jobject *jobj, t_param *param);
void	*fill_cylinder	(t_jobject *jobj, t_param *param);
const t_object_def		g_objects[] = {
	{"sphere", RTSPHERE, g_sphere_keys, RT_KEYS_SIZE(g_sphere_keys), &fill_sphere},
	{"plane", RTPLAN, g_plan_keys, RT_KEYS_SIZE(g_plan_keys), &fill_plane},
	{"cone", RTCONE, g_cone_keys, RT_KEYS_SIZE(g_cone_keys), &fill_cone},
	{"cylinder", RTCYLINDER, g_cylinder_keys, RT_KEYS_SIZE(g_cylinder_keys), &fill_cylinder},
	{"quadric", RTQUADRIC, g_quadric_keys, RT_KEYS_SIZE(g_quadric_keys), NULL}
};

#else

extern const t_object_def		g_objects[5];
extern const t_key				g_common_keys[11];
extern const t_key				g_sphere_keys[];
extern const t_key				g_plan_keys[];
extern const t_key				g_cone_keys[];
extern const t_key				g_cylinder_keys[];
extern const t_key				g_quadric_keys[];
extern const t_key				g_camera_keys[3];
extern const t_key				g_light_keys[3];
extern const t_key				g_main_object_keys[3];
extern const t_key				g_texture_keys[2];

#endif

#endif
