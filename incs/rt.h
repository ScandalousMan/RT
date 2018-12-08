/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:39:54 by aguemy            #+#    #+#             */
/*   Updated: 2018/12/04 16:01:22 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define PARSING_PRECISION 10
# define FOCAL_VALUE 40.0
# define ABS(Value) ((Value < 0) ? -1 * Value : Value)
# ifdef __linux__
#  define M_PI 3.141592653589793238462643383279
# endif
# define EPSILON 0.000001
# define DEBUG 0

# define MIN_DOUBLE_OBJECT -5000.0f
# define MAX_DOUBLE_OBJECT 5000.0f
# define MIN_DOUBLE_POS_EYE -10000.0
# define MAX_DOUBLE_POS_EYE 10000.0

# define PIXELISATION	8

# define ANTI_ALIASING 1
# define STEP_ANTI_ALIASING 1
# define MAX_ANTI_ALIASING 1
# define MIN_ANTI_ALIASING 10

# define RECURSION 0
# define STEP_RECURSION 1
# define MAX_RECURSION 10
# define MIN_RECURSION 0

# define SPECULAR_EXP 1
# define STEP_SPECULAR_EXP 1
# define MAX_SPECULAR_EXP 16
# define MIN_SPECULAR_EXP 1

# define ROTATION_ANGLE 30
# define STEP_ROTATION_ANGLE 1
# define MAX_ROTATION_ANGLE 90
# define MIN_ROTATION_ANGLE 1

# define K_AMBIENCE 0.2
# define STEP_K_AMBIENCE 0.05
# define MAX_K_AMBIENCE 1.0
# define MIN_K_AMBIENCE 0.0

# define CARTOON_FACTOR 25
# define STEP_CARTOON_FACTOR 1
# define MIN_CARTOON_FACTOR 5
# define MAX_CARTOON_FACTOR 50

# define BLUR_RADIUS 4
# define STEP_BLUR_RADIUS 1
# define MIN_BLUR_RADIUS 0
# define MAX_BLUR_RADIUS 50

# define SIERPINSKI 4

# define NOISE_SIZE 128
# define TURB_SIZE 32.0
# define TURB_POWER 5.0


# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdint.h>
# include <stdarg.h>
# include <string.h>
# include <assert.h>
# include <limits.h>
# include <time.h>

# include <GL/glew.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_opengl.h>

# include <libft.h>

# define NK_INCLUDE_FIXED_TYPES
# define NK_INCLUDE_STANDARD_IO
# define NK_INCLUDE_STANDARD_VARARGS
# define NK_INCLUDE_DEFAULT_ALLOCATOR
# define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
# define NK_INCLUDE_FONT_BAKING
# define NK_INCLUDE_DEFAULT_FONT

# include "nuklear.h"
# include "nuklear_sdl_gl3.h"

# define WINDOW_GUI_WIDTH 500
# define WINDOW_GUI_HEIGHT 800
# define WINDOW_SDL_WIDTH 800
# define WINDOW_SDL_HEIGHT 800

# define NB_THREAD 4

# define MAX_VERTEX_MEMORY 512 * 1024
# define MAX_ELEMENT_MEMORY 128 * 1024

# define UNUSED(a) (void)a
# define MIN(a,b) ((a) < (b) ? (a) : (b))
# define MAX(a,b) ((a) < (b) ? (b) : (a))
# define LEN(a) (sizeof(a)/sizeof(a)[0])

# define TRUE 1
# define FALSE 0

typedef struct nk_context		t_nk_context;
typedef struct nk_font_atlas	t_nk_font_atlas;

typedef enum nk_anti_aliasing	t_nk_anti_aliasing;

# define VEC_SIZE 3

typedef struct	s_sphere
{
	double			center[VEC_SIZE];
	double			radius;
}				t_sphere;

typedef struct s_plane
{
	double			n[VEC_SIZE];
	double			ref[VEC_SIZE];
}				t_plane;

typedef struct s_cone
{
	double			org[VEC_SIZE];
	double			u[VEC_SIZE];
	double			angle;
}				t_cone;

typedef struct s_cylindre
{
	double			org[VEC_SIZE];
	double			u[VEC_SIZE];
	double			radius;
}				t_cylindre;

typedef struct	s_quadric
{
	double			center[VEC_SIZE];
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			f;
	double			g;
	double			h;
	double			i;
	double			r;
}				t_quadric;

typedef struct	s_cube
{
	double			center[VEC_SIZE];
	double			h;
	double			n[VEC_SIZE];
}				t_cube;

typedef struct	s_limit
{
	t_plane			plane;
	char			type;
	struct s_limit	*next;
}				t_limit;

typedef struct	s_reference
{
	double		i[VEC_SIZE];
	double		j[VEC_SIZE];
	double		k[VEC_SIZE];
}				t_reference;

typedef struct	s_effects
{
	char				color;
	char				normal;
}				t_effects;

/*
** dim is a void for each specific object
*/
typedef struct	s_object
{
	void				*dim;
	void				*parsed;
	int					num;
	int					type;//1 for sphere, 2 for plane, 3 for cone, 4 for cylindre
//	double			shadow;
	t_reference	ref;
	double			tmp_vec[VEC_SIZE];
	int					col;//couleur de surface de l'objet
	double			kd;//coefficient de réflexion diffuse de l'objet
	double			ks;//coefficient de réflexion spéculaire de l'objet
	double			transparency;
	double			reflection;
	double			thickness;//épaisseur de l'objet, 0 par défaut
	double			index;//indice du matériaux constituant l'objet, 1 par défaut
	int					phong;//exposant de Phong de l'objet
	t_limit			*limits;
	double			uv_map[2];
	t_effects		effects;
	double			rotation[VEC_SIZE];
	double			translation[VEC_SIZE];
	struct s_object	*next;//liste chainée
}				t_object;

typedef struct	s_light
{
	int							type;
	int							num;
	int							col;
	double					src[VEC_SIZE];//position de la source lumineuse
	double					i;//intensité de la source lumineuse
	int							tmp_col;//for times where light goes through transparent objects
	struct s_light	*next;
}				t_light;

typedef struct	s_path
{
	double			from[VEC_SIZE];
	double			v[VEC_SIZE];//triplet pour la direction du rayon initial
	double			x[VEC_SIZE];//triplet pour point d'intersection
	double			n[VEC_SIZE];//triplet pour vecteur normal
	double			l[VEC_SIZE];//rayon de la lumiere
	double			r[VEC_SIZE];//rayon réfléchi
	double			t[VEC_SIZE];//rayon transmis
	double			tmp_x[VEC_SIZE];//use for cut objects tmp points
	double			valid_n[VEC_SIZE];//to store final cut normal
	double			valid_x[VEC_SIZE];//to store final cut intersection
	t_object		*current_object;
	t_object		*inside_obj;
	struct s_path	*reflected;
	struct s_path	*transmitted;
}				t_path;

typedef struct			s_custom_obj
{
	char				op;
	t_object			*object;
	struct s_custom_obj	*next;
}						t_custom_obj;

typedef struct	s_custom
{
	double				org[VEC_SIZE];//todo change
	double				u[VEC_SIZE];//todo change

	int					id;
	char				*name;
	struct s_custom_obj	*objects;
	struct s_custom		*next;
}				t_custom;

typedef struct		s_macro
{
	float			k_ambience;
	int				anti_aliasing;
	int				blur_radius;
	int				cartoon_factor;
	int				filter;
	int				recursion;
	int				rotation_angle;
	int				specular_exp;
}					t_macro;

typedef	struct		s_update_img
{
	char			process;
	char			post_process;
}					t_update_img;

typedef struct s_sdl
{
	SDL_Window *win_gl;
	SDL_GLContext gl_context;

	SDL_Window *win_sdl;
	SDL_Renderer *render_sdl;
	SDL_Surface *surfs[NB_THREAD];
	SDL_Surface *tmp_surfs[NB_THREAD];
	int show_tmp;

	t_object *current_object;

	t_nk_context *ctx;
} t_sdl;

typedef struct		s_param
{
	clock_t			start;//TODO delete
	clock_t			end;//TODO delete
	double			f;//focale
	double			eye[VEC_SIZE];//position de l'oeil de l'observateur
	double			look[VEC_SIZE];//direction dans laquelle l'oeil regarde
	double			align[VEC_SIZE];//eye's alignment to define what is looked at
	double			third[VEC_SIZE];//third dimension in the referential
	double			obj_d;//object's distance
	double			tmp_d;//last distance used
	double			tmp_d_cut;//used to detect cutting planes
	t_path			*path;
	t_custom		*customs;
	t_object		*objects;
	t_light			*lights;
	int				num_lights;
	t_object		*intersect_object;
	int 			num_objects;
	char			is_cut;
	char			is_for_light;
	t_light			*tmp_light;
	double			tmp_vec[VEC_SIZE];
	int 			brightness;
	int				final_col;
	int				texture_col;
	int				i[2];
	double			rot[VEC_SIZE][VEC_SIZE];
	double			epsilon;
	t_sdl			*graph;
	SDL_Thread		**thread;
	
	int				current_thread;
	t_update_img	up_img;
	int					**pxl_infos;
	double			ia;//intensité de la lumiere ambiante
	double			m[VEC_SIZE];//triplet intermediaire pour calculs ombres
	double			perlin_noise[NOISE_SIZE][NOISE_SIZE];

	int				to_pix;
	clock_t			last_mv;

	t_macro			macro; // Contain all global variable across program

	char			quit; // Used to know if program must exit
	SDL_Surface		*texture;
}				t_param;

/*
**------------------------------------colors------------------------------------
*/
int								rgb_color(unsigned char r, unsigned char g, unsigned char b);
int								rgb_ratio(int color, double a);
int								color_summer(int col1, int col2);
int 							color_absorber(int obj_col, int light_col);
/*
**------------------------------------create------------------------------------
*/
t_param							*struct_create(void);
t_param							*stereoscopy_cpy(t_param *param1);
void								stereoscopy_free(t_param *param);
t_sdl								*copy_pxls(t_param *param);
t_param							*pxl_infos_create(t_param *param);
t_param							*new_content(t_param *param);
//t_light							*add_light(t_light **lights, double *src, double i, int col);
t_light							*light_copy(t_light *src);
//t_object						*add_sphere(t_param *param, double *center, double radius);
//t_object						*add_cube(t_param *param, double *center, double side);
//t_object						*add_plane(t_param *param, double *n, double *ref);
//t_object						*add_cone(t_param *param, double *org, double *u,
//								double angle);
t_object						*object_copy(t_object *src);
//t_object						*add_cylindre(t_param *param, double *org, double *u,
//								double radius);
/*
**-------------------------------------init-------------------------------------
*/
t_param							*values_init(t_param *param);
void							rt_filler(t_param *param);
t_object						*light_masked(t_param *param, double *from, double *to, t_path *path);
void							print_obj_point(t_param *param);
/*
**------------------------------------tools-------------------------------------
*/
void							*duplicate(void *src, size_t size);
//double							ft_atod(const char *str);
double							second_level(double a, double b, double c);
double							vec_norm(double *v);
double							*vec_to_unit_norm(double *v);
//double							pt_dist(double *x, double *y);//TODO delete?
double							pt_dist_root(double *x, double *y);
double							*vec_multiply(double a, double *vec, double *container);
double							*pt_translated(double *pt, double *vec, double *container);
void							vec_copy(double *src, double *des);
double							*coord_copy(double *des, double x, double y, double z);
double							scalar_product(double *x, double *y);
double							*vector_product(double *x, double *y, double *container);
double							*vec_soustraction(double *x, double *y, double *container);
int								is_in_list(t_param *param, t_light *light);
void							matrice_product(double matrice[VEC_SIZE][VEC_SIZE], double *col, double *dest);
double							*vec_dup(double *vec);
/*
**------------------------------------display-----------------------------------
*/
void							display_objects(t_param *param);
int								point_display(t_param *param);
void							light_display_objects(t_param *param);
/*
**------------------------------------sphere------------------------------------
*/
double			distance_calc(t_object *tmp, double *from, double *to);
double			distance_to_sphere(t_object *tmp, double *from, double *to);
int					is_inside_sphere(double *pt, t_object *tmp);
double 			*sphere_position(double *pt, t_object *obj);
void				display_sphere(t_object *objs);
/*
**------------------------------------plane-------------------------------------
*/
double			plane_distance(double *from, double *to, double *n, double *ref);
double			distance_to_plane(t_object *tmp, double *from, double *to);
int					is_inside_plane(double *pt, t_object *tmp);
double			*plane_position(double *pt, t_object *obj);
void				display_plane(t_object *objs);
/*
**-------------------------------------cone-------------------------------------
*/
double			cone_first_term(t_object *tmp, double *to);
double			cone_second_term(t_object *tmp, double *to, double *x);
double			cone_third_term(t_object *tmp, double *x);
int					is_inside_cone(double *pt, t_object *tmp);
void				display_cone(t_object *objs);
double			distance_to_cone(t_object *tmp, double *from, double *to);
double			*cone_position(double *pt, t_object *object);
/*
**-----------------------------------cylindre-----------------------------------
*/
double			cylindre_first_term(t_object *tmp, double *to);
double			cylindre_second_term(t_object *tmp, double *to);
double			cylindre_third_term(t_object *tmp);
int					is_inside_cylindre(double *pt, t_object *tmp);
void				display_cylindre(t_object *objs);
double			distance_to_cylindre(t_object *tmp, double *from, double *to);
double			*cylindre_position(double *pt, t_object *object);
/*
**------------------------------------quadric-----------------------------------
*/
double			quadric_first_term(t_quadric *tmp, double *to);
double			quadric_second_term(t_quadric *tmp, double *from, double *to);
double			quadric_third_term(t_quadric *tmp, double *from);
int					is_inside_quadric(double *pt, t_quadric *tmp);
double			distance_to_quadric(t_object *tmp, double *from, double *to);
double			*quadric_position(double *pt, t_object *object);
void				display_quadric(t_object *objs);
/*
**-------------------------------------cube-------------------------------------
*/
int					is_inside_cube(double *pt, t_object *tmp);
double			distance_to_face1(t_object *tmp, double *from, double *to, double face);
double			distance_to_face2(t_object *tmp, double *from, double *to, double face);
double			distance_to_face3(t_object *tmp, double *from, double *to, double face);
void				display_cube(t_object *objs);
double			distance_to_cube(t_object *t, double *from, double *to);
double			*cube_position(double *pt, t_object *obj);

double			ft_absdbl(double a);
int 				ft_absint(int a);
void				ft_putvec(double *x);
void				eye_rotation(double alpha, double beta, double gamma, t_param *param);
void				rotation_matrice(double alpha, double beta, double gamma, t_param *param);
/*
**------------------------------------parser------------------------------------
*/
//t_param	*rt_parser(t_param *param);
//t_parse	*split_whitespace(char *line);
//int 	rt_light_parser(t_param *param, t_parse *config);
//int 	rt_objects_lights_parser(t_param *param, t_parse *config);
int 	rt_init(t_param *param, char *line, int count);
//int 	rt_object_parser(t_param *param, t_parse *config);
//int 	rt_sphere_parser(t_param *param, t_parse *config);
//int 	rt_plane_parser(t_param *param, t_parse *config);
//int 	rt_cone_parser(t_param *param, t_parse *config);
//int 	rt_cylindre_parser(t_param *param, t_parse *config);

void			rt_tracer(t_param *param);
t_object	*first_obj_hit(t_param *param, double *from, double *to, t_path *path);
int				is_in_limit(double *pt, t_limit *limit);
int				is_in_limits(double *pt, t_object *obj, t_limit *limit);
void			update_normal_vector(t_object *tmp, t_path *path, double *pt);
void			update_objects(t_param *param);
void			update_sphere(t_object *obj, t_param *param);
void			update_cube(t_object *obj, t_param *param);
void			update_cylindre(t_object *obj, t_param *param);
void			update_plane(t_object *obj, t_param *param);
void			update_quadric(t_object *obj, t_param *param);
void			update_cone(t_object *obj, t_param *param);
// void			reset_moves(t_object *obj);
void			limits_move(double *o, t_object *obj, t_param *param);
void			ref_move(t_object *obj, t_param *param);
int				is_inside_object(double *pt, t_object *tmp, t_limit *limit);
void			object_position(double *pt, t_object *object);
void 			object_color_changer(t_object *object, t_param *param);
void			object_normal_changer(t_object *object, t_param *param, t_path *path);
t_object	*object_constructor(t_param *param);
void			update_normal_sphere(t_object *tmp, t_path *path);
void			update_normal_plane(t_object *tmp, t_path *path);
void			update_normal_cone(t_object *tmp, t_path *path);
void			update_normal_cylindre(t_object *tmp, t_path *path);
void			update_normal_quadric(t_quadric *tmp, t_path *path);
void			update_normal_cube(t_object *tmp, t_path *path);
void			display_lights(t_param *param);
int 			my_key_func(int keycode, t_param *param);
t_path			*path_create(t_param *param, int index);
/*
***REFERENTIAL
*/
void			default_ref_updater(t_object *obj);
void			special_ref_updater(double *vec, t_object *obj);
/*
**REFRACTION
*/
void			define_refracted_n(t_path *path1, t_path *path2);
double		get_index_n(t_path *path);
int				snell_descartes(double n1, double n2, t_path *path1, t_path *path2);
/*
**POST PROCESSING FUNCTIONS
*/
void 							greyscale(t_param *param);
void						 	sepia(t_param *param);
void							cartoon(t_param *param);
void							blur(t_param *param);
void							stereoscopy(t_param *param);
void							to_negative(t_param *param);
/*
**PERLIN
*/
double 		turbulence(double x, double y, double size, t_param *param);
double		marble_ratio(double u, double v, double size, t_param *param);
char			wood_ratio(double u, double v, double size, t_param *param);
/*
** NK_API SDL Prototypes
*/

t_nk_context					*nk_sdl_init(SDL_Window *win);
void							nk_sdl_font_stash_begin(struct nk_font_atlas
									**atlas);
void							nk_sdl_font_stash_end(void);
int								nk_sdl_handle_event(SDL_Event *evt);
void							nk_sdl_render(t_nk_anti_aliasing
									nk_anti_aliasing,
									int max_vertex_buffer,
									int max_element_buffer);
void							nk_sdl_shutdown(void);
void							nk_sdl_device_destroy(void);
void							nk_sdl_device_create(void);

/*
** NK_API Prototypes
*/

/*
** Nuklear function
*/

void							nukl_gui(t_param *param);
void							nukl_camera(t_param *param);
void							nukl_objects(t_param *param);
void 							nukl_global_app_setting(t_param *param);

void 							nukl_objects_show_pos(t_param *param,
									double *pos);
void 							nukl_objects_show_edit_double(t_param *param,
									char *name, double *dbl, double step);

void							global_settings_1(t_param *param);
void							global_settings_2(t_param *param);
void							global_settings_3(t_param *param);
void							global_settings_4(t_param *param);
void							global_settings_filters(t_param *param);

void 							gui_sphere(t_param *param);
void 							gui_plane(t_param *param);
void 							gui_cylindre(t_param *param);
void 							gui_quadric(t_param *param);
void 							gui_cone(t_param *param);
void 							gui_cube(t_param *param);

/*
** SDL2 Prototypes
*/

int								convert_Uint32_to_int(Uint32 pixel,SDL_PixelFormat *fmt);
Uint32							format_Uint32(Uint32 pixel, SDL_PixelFormat *fmt);
Uint32 							getpxl(t_param *param, int y, int x);
void							putpxl(t_param *param, int y, int x, Uint32 pixel);
Uint32							jpg_find_pxl(t_param *param, double x, double y);
void							save_img(t_param *param, char *name);
void							sdl_draw(t_sdl *graph);
void 							sdl_init(t_sdl *graph);
void							sdl_init_window(t_sdl *graph);
void							sdl_init_nuklear(t_sdl *graph);
void							sdl_pull_evts(t_param *param);
void							sdl_quit(t_sdl *graph);

/**
 * SDL_Event protos
**/

void 							handle_keyboard(int keycode, t_param *param);
void 							handle_keyboard_caps(int keycode, t_param *param);

/*
** Graph prototype
*/

void							launch_threads(t_param *param);

/*
** Free functions
*/

void 							free_objects(t_param *param, char final);
void 							free_lights(t_light *lights);
void							free_pxl_infos(int **pxl_infos);
void 							free_path(t_path *path);
void 							end_program(t_param *param);

#endif
