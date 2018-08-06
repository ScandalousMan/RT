/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_objects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:13:11 by jbouille          #+#    #+#             */
/*   Updated: 2018/08/06 17:30:41 by jbouille         ###   ########.fr       */
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
	RTTORE,
	RTCUSTOMOBJECT
}						t_object_type;

typedef enum			e_light_type
{
	RTSPOT=0,
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
	RTCUSTOM,
	RTCUSTOMOBJ,
	RTSIGN,
	RTLIMIT,
	RTLIGHTTYPE
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
# define CUSTOMS_KEY		"custom_objects"
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
	{"rotation", RTVECTOR, RTDOUBLE},
	{"limits", RTARRAY, RTLIMIT}
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
	{"center", RTVECTOR, RTDOUBLE},
	{"a", RTDOUBLE, RTNULL},
	{"b", RTDOUBLE, RTNULL},
	{"c", RTDOUBLE, RTNULL},
	{"d", RTDOUBLE, RTNULL},
	{"e", RTDOUBLE, RTNULL},
	{"f", RTDOUBLE, RTNULL},
	{"g", RTDOUBLE, RTNULL},
	{"h", RTDOUBLE, RTNULL},
	{"i", RTDOUBLE, RTNULL}
};

const t_key				g_tore_keys[] = {
	{"center", RTVECTOR, RTDOUBLE},
	{"R", RTUDOUBLE, RTNULL},
	{"r", RTUDOUBLE, RTNULL},
};

const t_key				g_customobject_keys[] = {
	{"name", RTSTRING, RTNULL},
	{"center", RTVECTOR, RTDOUBLE}
};

const t_key				g_camera_keys[] = {
	{"eye", RTVECTOR, RTDOUBLE},
	{"look", RTVECTOR, RTDOUBLE},
	{"align", RTVECTOR, RTDOUBLE},
};

const t_key				g_light_keys[] = {
	{"type", RTLIGHTTYPE, RTNULL},
	{"u", RTVECTOR, RTDOUBLE},
	{"color", RTVECTOR, RTCHAR},
	{"intensity", RTCOEF, RTNULL},
};

const t_key				g_main_object_keys[] = {
	{CAMERA_KEY, RTCAMERA, RTNULL},
	{LIGHTS_KEY, RTARRAY, RTLIGHT},
	{OBJECTS_KEY, RTARRAY, RTOBJECT},
	{CUSTOMS_KEY, RTARRAY, RTCUSTOM}
};

const t_key				g_texture_keys[] = {
	{RT_OBJECT_TYPE, RTSTRING, RTNULL},
	{"name", RTSTRING, RTNULL},
};

const t_key				g_custom_keys[] = {
	{"name", RTSTRING, RTNULL},
	{OBJECTS_KEY, RTARRAY, RTCUSTOMOBJ}
};

const t_key				g_customobj_keys[] = {
	{"intersection", RTSIGN, RTNULL},
	{"object", RTOBJECT, RTNULL}
};

/* TODO CHANGE FUNCTIONS DECLARATIONS */
void	*fill_sphere		(t_jobject *jobj, t_param *param);
void	*fill_plane			(t_jobject *jobj, t_param *param);
void	*fill_cone			(t_jobject *jobj, t_param *param);
void	*fill_cylinder		(t_jobject *jobj, t_param *param);
void	*fill_quadric		(t_jobject *jobj, t_param *param);
void	*fill_tore			(t_jobject *jobj, t_param *param);
void	*fill_customobject	(t_jobject *jobj, t_param *param);
const t_object_def		g_objects[] = {
	{"sphere", RTSPHERE, g_sphere_keys, RT_KEYS_SIZE(g_sphere_keys), &fill_sphere},
	{"plane", RTPLAN, g_plan_keys, RT_KEYS_SIZE(g_plan_keys), &fill_plane},
	{"cone", RTCONE, g_cone_keys, RT_KEYS_SIZE(g_cone_keys), &fill_cone},
	{"cylinder", RTCYLINDER, g_cylinder_keys, RT_KEYS_SIZE(g_cylinder_keys), &fill_cylinder},
	{"quadric", RTQUADRIC, g_quadric_keys, RT_KEYS_SIZE(g_quadric_keys), fill_quadric},
	{"tore", RTTORE, g_tore_keys, RT_KEYS_SIZE(g_tore_keys), &fill_tore},
	{"custom", RTCUSTOMOBJECT, g_customobject_keys, RT_KEYS_SIZE(g_customobject_keys), &fill_customobject}
};

#else

extern const t_object_def		g_objects[7];
extern const t_key				g_common_keys[12];
extern const t_key				g_sphere_keys[];
extern const t_key				g_plan_keys[2];
extern const t_key				g_cone_keys[];
extern const t_key				g_cylinder_keys[];
extern const t_key				g_quadric_keys[];
extern const t_key				g_customobject_keys[];
extern const t_key				g_camera_keys[3];
extern const t_key				g_light_keys[4];
extern const t_key				g_main_object_keys[4];
extern const t_key				g_texture_keys[2];
extern const t_key				g_custom_keys[2];
extern const t_key				g_customobj_keys[2];

#endif

#endif
