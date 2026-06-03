#include "cub3d.h"

static void	draw_vertical_bar(void *mlx, void *win, int start_x, int end_x,
	int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < 600)
	{
		x = start_x;
		while (x < end_x)
		{
			mlx_pixel_put(mlx, win, x, y, color);
			x++;
		}
		y++;
	}
}

static int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 900, 600, "cub3D proof of life");
	if (!win)
		return (1);
	draw_vertical_bar(mlx, win, 0, 300, 0xFFFFFF);
	draw_vertical_bar(mlx, win, 300, 600, 0xF4D03F);
	draw_vertical_bar(mlx, win, 600, 900, 0x58D68D);
	mlx_hook(win, 17, 0, close_window, NULL);
	mlx_loop(mlx);
	return (0);
}