#include "cub3d.h"

typedef struct s_app
{
	void	*mlx;
	void	*win;
	void	*img;
} 	t_app;

static int	close_window(t_app *app)
{
	if (app->img)
		mlx_destroy_image(app->mlx, app->img);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	exit(0);
	return (0);
}

static int	key_hook(int keycode, t_app *app)
{
	if (keycode == ESC)
		close_window(app);
	return (0);
}

int	main(void)
{
	t_app	app;
	int	img_w;
	int	img_h;

	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.win = mlx_new_window(app.mlx, 1024, 1024, "cub3D image test");
	if (!app.win)
		return (1);
	app.img = mlx_xpm_file_to_image(app.mlx, "textures/texturize_voronoi_55_2048.xpm", &img_w, &img_h);
	if (!app.img)
		return (write(2, "Error: cannot load textures/demo.xpm\n", 37), 1);
	mlx_put_image_to_window(app.mlx, app.win, app.img, (1024 - img_w) / 2,
		(1024 - img_h) / 2);
	mlx_hook(app.win, 2, 1L << 0, key_hook, &app);
	mlx_hook(app.win, 17, 0, close_window, &app);
	mlx_loop(app.mlx);
	return (0);
}