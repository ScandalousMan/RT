#include "rt.h"

t_param	*struct_init(void)
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH + 100, HEIGHT + 100, "RT aguemy");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	addr = addr_init(img);
	return (struct_create(mlx, win, img, addr));
}

int		main(void)
{
	t_param	*param;

	if (!(param = struct_init()))
		return (-1);
	rt_parser(param);
	rt_tracer(param);
	mlx_hook(param->win, 2, 1L << 2, my_key_func, param);
	mlx_loop(param->mlx);
	return(0);
}
