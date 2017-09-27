/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:39:54 by aguemy            #+#    #+#             */
/*   Updated: 2017/06/25 14:17:52 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define PARSING_PRECISION 10
# define FOCAL_VALUE 40.0
# define ABS(Value) ((Value < 0) ? -1 * Value : Value)
# define WIDTH 800
# define HEIGHT 800
# define SPECULAR_EXP 8
# define ESCAPE 53
# define REFRESH 15
# define RIGHT 124
# define LEFT 123
# define TOP 126
# define BOTTOM 125
# define ZOOM_IN 44
# define ZOOM_OUT 24
# define BRIGHTNESS 11
# define EPSILON 0.001
# define ROTATION 30.0
# define MAX_RECURSION 1
# define ANTI_ALIASING 1

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../lib-mlx/mlx.h"
# include <math.h>
# include "../libft/libft.h"

typedef struct  s_parse
{
	char			*str;
	int 			list_len;
	struct s_parse	*next;
}				t_parse;

typedef struct	s_sphere
{
	double			*center;
	double			radius;
}				t_sphere;

typedef struct s_plane
{
	double			*n;
	double			*ref;
}				t_plane;

typedef struct s_cone
{
	double			*org;
	double			*u;
	double			angle;
}				t_cone;

typedef struct s_cylindre
{
	double			*org;
	double			*u;
	double			radius;
}				t_cylindre;

typedef struct s_ellipsoide
{
	double			*center;
	double			a;
	double			b;
	double			c;
}				t_ellipsoide;

typedef struct	s_object
{
	void			*dim;
	int				num;
	int				type;//1 for sphere, 2 for plane, 3 for cone, 4 for cylindre

	double			shadow;

	double			*tmp_vec;
	int				col;//couleur de surface de l'objet
	double			kd;//coefficient de réflexion diffuse de l'objet
	double			ks;//coefficient de réflexion spéculaire de l'objet
	double			transparency;
	double			reflection;
	double			thickness;//épaisseur de l'objet, 0 par défaut
	double			index;//indice du matériaux constituant l'objet, 1 par défaut
	int				phong;//exposant de Phong de l'objet
	struct s_object	*next;//liste chainée
}				t_object;

typedef struct	s_light
{
	int				num;
	int				col;
	double			*src;//position de la source lumineuse
	double			i;//intensité de la source lumineuse
	struct s_light	*next;
}				t_light;

typedef struct	s_path
{
	double			*from;
	double			*v;//triplet pour la direction du rayon initial
	double			*x;//triplet pour point d'intersection
	double			*n;//triplet pour vecteur normal
	double			*l;//rayon de la lumiere
	double			*r;//rayon réfléchi
	double			*t;//rayon transmis
	t_object		*current_object;
	struct s_path	*reflected;
	struct s_path	*transmitted;
}				t_path;

typedef struct	s_param
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	double			f;//focale
	double			*eye;//position de l'oeil de l'observateur
	double			*look;//direction dans laquelle l'oeil regarde
	double			*align;//eye's alignment to define what is looked at
	double			*third;//third dimension in the referential
	double			obj_d;//object's distance
	double			tmp_d;//last distance used
	t_path			*path;
	t_object		*objects;
	t_light			*lights;
	int				num_lights;
	t_object		*intersect_object;
	t_object		*tmp_object;
	t_light			*tmp_light;
	double			*tmp_vec;
	int 			brightness;
	double			bright;
	double			diffuse;
	int				*i;
	double			**rot;
	double			epsilon;
	
	double			ia;//intensité de la lumiere ambiante
	double			*m;//triplet intermediaire pour calculs ombres
}				t_param;

/*
**----------------------------------components----------------------------------
*/
double			ft_pow(double x, int n);
int				rgb_color(unsigned char r, unsigned char g, unsigned char b);
int				rgb_ratio(int color, double a);
void			store_pixel(t_param *param, int color);
char			*addr_init(void *img);
void			display_info(t_param *param);
double			ft_atod(const char *str);
int				color_summer(int col1, int col2);
/*
**------------------------------------create------------------------------------
*/
t_param			*struct_create(void *mlx, void *win, void *img, char *addr);
t_param			*new_content(t_param *param);
t_light			*add_light(t_light **lights, double *src, double i, int col);
t_object		*add_sphere(t_param *param, double *center, double radius);
t_object		*add_cube(t_param *param, double *center, double side);
t_object		*add_plane(t_param *param, double *n, double *ref);
t_object		*add_cone(t_param *param, double *org, double *u,
				double angle);
t_object		*add_cylindre(t_param *param, double *org, double *u,
				double radius);
t_object		*add_ellipsoide(t_param *param, double *org, double a, double b,
				double c);
/*
**-------------------------------------init-------------------------------------
*/
t_param			*values_init(t_param *param);
void			rt_filler(t_param *param);
t_object		*object_intersection(t_param *param, double *from, double *to, t_path *path);
void			print_obj_point(t_param *param);
/*
**------------------------------------tools-------------------------------------
*/
double			ft_atod(const char *str);
double			second_level(double a, double b, double c);
double			vec_norm(double *v);
double			*vec_to_unit_norm(double *v);
double			pt_dist(double *x, double *y);
double			*vec_multiply(double a, double *vec, double *container);
double			*pt_translated(double *pt, double *vec, double *container);
void			vec_copy(double *src, double *des);
double			*coord_copy(double *des, double x, double y, double z);
double			scalar_product(double *x, double *y);
double			*vector_product(double *x, double *y, double *container);
double			*vec_soustraction(double *x, double *y, double *container);
int				is_in_list(t_param *param, t_light *light);
void			matrice_product(double **matrice, double *col, double *dest);
/*
**------------------------------------display-----------------------------------
*/
void			display_objects(t_param *param);
int				point_display(t_param *param);
/*
**-----------------------------------distance-----------------------------------
*/
double			distance_calc(t_object *tmp, t_param *param, double *from,
				double *to);
double			distance_to_sphere(t_object *tmp, double *from,
				double *to);
double			distance_to_plane(t_object *tmp, double *from,
				double *to);
double			distance_to_cone(t_object *tmp, double *from, double *to);
double			distance_to_cylindre(t_object *tmp, double *from, double *to);
double			distance_to_ellipsoide(t_object *tmp, double *from,
				double *to);
/*
**-------------------------------------cone-------------------------------------
*/
double			cone_first_term(t_object *tmp, double *to);
double			cone_second_term(t_object *tmp, double *to, double *x);
double			cone_third_term(t_object *tmp, double *x);
/*
**-----------------------------------cylindre-----------------------------------
*/
double			cylindre_first_term(t_object *tmp, double *to);
double			cylindre_second_term(t_object *tmp, double *to);
double			cylindre_third_term(t_object *tmp);

void			ft_putvec(double *x);
int				my_key_func(int keycode, t_param *param);
void			eye_rotation(double alpha, double beta, double gamma, t_param *param);
double			**rotation_matrice(double alpha, double beta, double gamma, t_param *param);
/*
**------------------------------------parser------------------------------------
*/
t_param	*rt_parser(t_param *param);
t_parse	*split_whitespace(char *line);
int 	rt_light_parser(t_param *param, t_parse *config);
int 	rt_objects_lights_parser(t_param *param, t_parse *config);
int 	rt_init(t_param *param, char *line, int count);
int 	rt_object_parser(t_param *param, t_parse *config);
int 	rt_sphere_parser(t_param *param, t_parse *config);
int 	rt_plane_parser(t_param *param, t_parse *config);
int 	rt_cone_parser(t_param *param, t_parse *config);
int 	rt_cylindre_parser(t_param *param, t_parse *config);
int		rt_ellipsoide_parser(t_param *param, t_parse *config);

void	rt_tracer(t_param *param);
t_object	*closest_object(t_param *param, double *from, double *to, t_path *path);
void		update_normal_vector(t_object *tmp, t_path *path);
t_object		*object_constructor(t_param *param);
void	update_normal_sphere(t_object *tmp, t_path *path);
void	update_normal_plane(t_object *tmp, t_path *path);
void	update_normal_cone(t_object *tmp, t_path *path);
void	update_normal_cylindre(t_object *tmp, t_path *path);
void	update_normal_ellipsoide(t_object *tmp, t_path *path);
void	display_lights(t_param *param);

#endif
