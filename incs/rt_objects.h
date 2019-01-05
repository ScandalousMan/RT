/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_objects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:13:11 by jbouille          #+#    #+#             */
/*   Updated: 2018/12/04 17:57:16 by jbouille         ###   ########.fr       */
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
	RTQUADRIC,
	RTCUBE
}						t_object_type;

typedef enum			e_light_type
{
	RTSPOT,
	RTPARALLEL
}						t_light_type;

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
	RTN,
	RTSIGN,
	RTLIMIT,
	RTLIGHTTYPE
}						t_rt_type;

typedef enum			e_color_effect
{
	RT_C_NONE,
	RT_C_CHESS,
	RT_C_SIERPINSKI,
	RT_C_CLOUD,
	RT_C_MARBLE,
	RT_C_WOOD
}						t_color_effect;

typedef enum			e_limit_type
{
	RT_C_RELATIVE,
	RT_C_ABSOLUTE
}						t_limit_type;

typedef enum			e_normal_effect
{
	RT_N_NONE,
	RT_N_SINUS
}						t_normal_effect;

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
	void				*(*fill)(t_jobject*, t_object*);
}						t_object_def;

# define RT_OBJECT_TYPE		"type"
# define RT_LIMITS_TYPE		"type"
# define CAMERA_KEY			"camera"
# define LIGHTS_KEY			"lights"
# define OBJECTS_KEY		"objects"
# define RT_KEYS_SIZE(keys)	(sizeof(keys) / sizeof(t_key))

static const t_key				g_common_keys[] = {
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
	{"rotation", RTVECTOR, RTDOUBLE},
	{"limits", RTARRAY, RTLIMIT}
};

static const t_key				g_plan_keys[] = {
	{"normal", RTVECTOR, RTDOUBLE},
	{"point", RTVECTOR, RTDOUBLE}
};

static const t_key				g_sphere_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"radius", RTUDOUBLE, RTNULL}
};

static const t_key				g_cone_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"angle", RTDOUBLE, RTNULL},
	{"vector", RTVECTOR, RTDOUBLE}
};

static const t_key				g_cylinder_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"radius", RTUDOUBLE, RTNULL},
	{"vector", RTVECTOR, RTDOUBLE}
};

static const t_key				g_quadric_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"a", RTDOUBLE, RTNULL},
	{"b", RTDOUBLE, RTNULL},
	{"c", RTDOUBLE, RTNULL},
	{"d", RTDOUBLE, RTNULL},
	{"e", RTDOUBLE, RTNULL},
	{"f", RTDOUBLE, RTNULL},
	{"g", RTDOUBLE, RTNULL},
	{"h", RTDOUBLE, RTNULL},
	{"i", RTDOUBLE, RTNULL},
	{"r", RTDOUBLE, RTNULL}
};

static const t_key				g_cube_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"h", RTDOUBLE, RTNULL},
};

static const t_key				g_limit_keys[] = {
	{"normal", RTVECTOR, RTDOUBLE},
	{"point", RTVECTOR, RTDOUBLE},
	{RT_LIMITS_TYPE, RTSTRING, RTNULL}
};

static const t_key				g_camera_keys[] = {
	{"eye", RTVECTOR, RTDOUBLE},
	{"look", RTVECTOR, RTDOUBLE},
	{"align", RTVECTOR, RTDOUBLE},
};

static const t_key				g_light_keys[] = {
	{"type", RTLIGHTTYPE, RTNULL},
	{"u", RTVECTOR, RTDOUBLE},
	{"color", RTVECTOR, RTCHAR},
	{"intensity", RTCOEF, RTNULL},
};

static const t_key				g_main_object_keys[] = {
	{CAMERA_KEY, RTCAMERA, RTNULL},
	{LIGHTS_KEY, RTARRAY, RTLIGHT},
	{OBJECTS_KEY, RTARRAY, RTOBJECT}
};

static const t_key			g_texture_keys[] = {
	{RT_OBJECT_TYPE, RTSTRING, RTNULL},
	{"name", RTSTRING, RTNULL},
};

/* TODO CHANGE FUNCTIONS DECLARATIONS */
void	*fill_sphere		(t_jobject *jobj, t_object *s_obj);
void	*fill_plane			(t_jobject *jobj, t_object *p_obj);
void	*fill_cone			(t_jobject *jobj, t_object *c_obj);
void	*fill_cylinder		(t_jobject *jobj, t_object *c_obj);
void	*fill_quadric		(t_jobject *jobj, t_object *q_obj);
void	*fill_cube			(t_jobject *jobj, t_object *c_obj);
static const t_object_def		g_objects[] = {
	{"sphere", RTSPHERE, g_sphere_keys, RT_KEYS_SIZE(g_sphere_keys), &fill_sphere},
	{"plane", RTPLAN, g_plan_keys, RT_KEYS_SIZE(g_plan_keys), &fill_plane},
	{"cone", RTCONE, g_cone_keys, RT_KEYS_SIZE(g_cone_keys), &fill_cone},
	{"cylinder", RTCYLINDER, g_cylinder_keys, RT_KEYS_SIZE(g_cylinder_keys), &fill_cylinder},
	{"quadric", RTQUADRIC, g_quadric_keys, RT_KEYS_SIZE(g_quadric_keys), &fill_quadric},
	{"cube", RTCUBE, g_cube_keys, RT_KEYS_SIZE(g_cube_keys), &fill_cube}
};

#endif
