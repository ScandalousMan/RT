#include "rt.h"

// void		print_obj_point(t_param *param)
// {
// 	double	bright;
// 	double	diffuse;

// 	if (param && param->current_object)
// 	{
// 		bright = 0.0;
// 		diffuse = 0.0;
// 		param->tmp_light = param->lights;
// 		while (param->tmp_light)
// 		{
// 			vec_soustraction(param->tmp_light->src, param->x, param->l);
// 			vec_to_unit_norm(param->l);
// 			vec_multiply(-2.0 * scalar_product(param->n, param->v), param->n, param->r);
// 			pt_translated(param->r, param->v, param->r);
// 			vec_to_unit_norm(param->r);
// 			if (!object_intersection(param, param->x, param->tmp_light->src))
// 			{
// 				if (scalar_product(param->l, param->n) * param->tmp_light->i > 0.0)
// 					diffuse += scalar_product(param->l, param->n) * param->tmp_light->i;
// 				if (param->bright && ft_pow(scalar_product(param->l, param->r), param->bright) * param->tmp_light->i > 0.0)
// 					bright += ft_pow(scalar_product(param->l, param->r), param->current_object->phong) * param->tmp_light->i;
// 			}
// 			param->tmp_light = param->tmp_light->next;
// 		}
// 		store_pixel(param, color_summer(rgb_ratio(param->current_object->col, 0.2 + param->current_object->kd * diffuse),
// 			rgb_ratio(16777215, param->current_object->ks * (bright > 1.0 ? 1.0 : bright))));
// 	}
// }

// t_param	*struct_init(void)
// {
// 	void	*mlx;
// 	void	*win;
// 	void	*img;
// 	char	*addr;

// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, WIDTH + 100, HEIGHT + 100, "RT aguemy");
// 	img = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	addr = addr_init(img);
// 	return (struct_create(mlx, win, img, addr));
// }

// int		main(void)
// {
// 	t_param	*param;

// 	if (!(param = struct_init()))
// 		return (-1);
// 	// new_content(param);
// 	rt_parser(param);
// 	rt_filler(param);
// 	mlx_hook(param->win, 2, 1L << 2, my_key_func, param);
// 	mlx_loop(param->mlx);
// 	return(0);
// }

void    activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;

    (void)user_data;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "RT");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_show_all(window);
}

int     main(int argc, char **argv) {
    GtkApplication  *app;
    int             status;

    app = gtk_application_new("org.gtk.rt", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL/*Struct to main_function*/);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return (status);
}