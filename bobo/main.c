#include "cub3d.h"

static void	free_map(t_map *map);

static int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width)
		return (1);
	return (game->map.grid[y][x] == '1');
}

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static void	draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
	int	y;

	if (start < 0)
		start = 0;
	if (end >= WIN_H)
		end = WIN_H - 1;
	y = start;
	while (y <= end)
	{
		put_pixel(&game->img, x, y, color);
		y++;
	}
}

static void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
				put_pixel(&game->img, x, y, 0x87CEEB);
			else
				put_pixel(&game->img, x, y, 0x3C2F2F);
			x++;
		}
		y++;
	}
}

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)WIN_W - 1.0;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30; // arbitrary number to avoid division by zero
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	ray->hit = 0;
}

static void	set_steps_and_sidedist(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_game *game, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(game, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

static void	draw_wall_slice(t_game *game, t_ray *ray, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	wall_color;

	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist <= 0.0001)
		ray->perp_wall_dist = 0.0001;
	line_height = (int)(WIN_H / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_H / 2;
	draw_end = line_height / 2 + WIN_H / 2;
	wall_color = 0xD2B48C;
	if (ray->side == 1)
		wall_color = 0xA28264;
	draw_vertical_line(game, x, draw_start, draw_end, wall_color);
}

static void	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;

	draw_background(game);
	x = 0;
	while (x < WIN_W)
	{
		init_ray(game, &ray, x);
		set_steps_and_sidedist(game, &ray);
		perform_dda(game, &ray);
		draw_wall_slice(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

static void	try_move(t_game *game, double move_x, double move_y)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x + move_x;
	next_y = game->player.y + move_y;
	if (!is_wall(game, (int)next_x, (int)game->player.y))
		game->player.x = next_x;
	if (!is_wall(game, (int)game->player.x, (int)next_y))
		game->player.y = next_y;
}

static void	update_player(t_game *game)
{
	if (game->key_w)
		try_move(game, game->player.dir_x * MOVE_SPEED,
			game->player.dir_y * MOVE_SPEED);
	if (game->key_s)
		try_move(game, -game->player.dir_x * MOVE_SPEED,
			-game->player.dir_y * MOVE_SPEED);
	if (game->key_a)
		try_move(game, -game->player.plane_x * MOVE_SPEED,
			-game->player.plane_y * MOVE_SPEED);
	if (game->key_d)
		try_move(game, game->player.plane_x * MOVE_SPEED,
			game->player.plane_y * MOVE_SPEED);
	if (game->key_left)
		rotate_player(game, -ROT_SPEED);
	if (game->key_right)
		rotate_player(game, ROT_SPEED);
}

static int	loop_hook(t_game *game)
{
	update_player(game);
	render_frame(game);
	return (0);
}

static int	close_window(t_game *game)
{
	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(&game->map);
	exit(0);
	return (0);
}

static int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	if (keycode == W)
		game->key_w = 1;
	if (keycode == A)
		game->key_a = 1;
	if (keycode == S)
		game->key_s = 1;
	if (keycode == D)
		game->key_d = 1;
	if (keycode == LEFT)
		game->key_left = 1;
	if (keycode == RIGHT)
		game->key_right = 1;
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->key_w = 0;
	if (keycode == A)
		game->key_a = 0;
	if (keycode == S)
		game->key_s = 0;
	if (keycode == D)
		game->key_d = 0;
	if (keycode == LEFT)
		game->key_left = 0;
	if (keycode == RIGHT)
		game->key_right = 0;
	return (0);
}

static void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height)
		free(map->grid[i++]);
	free(map->grid);
	map->grid = NULL;
}

static int	load_map(t_game *game, const char *path)
{
	int		fd;
	char	*line;
	char	**grid;
	int		i;
	int		len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	grid = ft_calloc(1024, sizeof(char *));
	if (!grid)
		return (close(fd), 0);
	i = 0;
	line = get_next_line(fd);
	while (line && i < 1023)
	{
		len = (int)ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[--len] = '\0';
		grid[i++] = line;
		if (len > game->map.width)
			game->map.width = len;
		line = get_next_line(fd);
	}
	close(fd);
	game->map.grid = grid;
	game->map.height = i;
	return (i > 0);
}

static void	init_player(t_game *game)
{
	game->player.x = 1.5;
	game->player.y = 1.5;
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (write(2, "Usage: ./cub3D <map.map>\n", 25), 1);
	ft_bzero(&game, sizeof(t_game));
	if (!load_map(&game, argv[1]))
		return (write(2, "Error: failed to load map\n", 26), 1);
	init_player(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (write(2, "Error: mlx_init failed\n", 23), 1);
	game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, "cub3D - DDA first render");
	if (!game.win)
		return (write(2, "Error: mlx_new_window failed\n", 29), 1);
	game.img.ptr = mlx_new_image(game.mlx, WIN_W, WIN_H);
	if (!game.img.ptr)
		return (write(2, "Error: mlx_new_image failed\n", 28), 1);
	game.img.addr = mlx_get_data_addr(game.img.ptr, &game.img.bpp,
			&game.img.line_len, &game.img.endian);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}