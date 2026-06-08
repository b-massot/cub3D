/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <bmassot@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 00:00:00 by bmassot           #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by bmassot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_player(t_game *game, double angle)
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

void	try_move(t_game *game, double move_x, double move_y)
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

void	update_player(t_game *game)
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

void	init_player(t_game *game, t_map_info *map_info)
{
	game->player.x = map_info->player.x + 0.5;
	game->player.y = map_info->player.y + 0.5;
	game->player.direction = map_info->player.direction;
	
	if (map_info->player.direction == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (map_info->player.direction == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
	else if (map_info->player.direction == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (map_info->player.direction == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
}

/* Charge les 4 textures XPM (north, south, west, east) et stocke dans t_game */
int	load_textures(t_game *game, t_map_info *map_info)
{
	int	width;
	int	height;

	game->tex_north.ptr = mlx_xpm_file_to_image(game->mlx,
			map_info->colors.north, &width, &height);
	if (!game->tex_north.ptr)
		return (0);
	game->tex_north.addr = mlx_get_data_addr(game->tex_north.ptr,
			&game->tex_north.bpp, &game->tex_north.line_len,
			&game->tex_north.endian);
	
	game->tex_south.ptr = mlx_xpm_file_to_image(game->mlx,
			map_info->colors.south, &width, &height);
	if (!game->tex_south.ptr)
		return (0);
	game->tex_south.addr = mlx_get_data_addr(game->tex_south.ptr,
			&game->tex_south.bpp, &game->tex_south.line_len,
			&game->tex_south.endian);
	
	game->tex_west.ptr = mlx_xpm_file_to_image(game->mlx,
			map_info->colors.west, &width, &height);
	if (!game->tex_west.ptr)
		return (0);
	game->tex_west.addr = mlx_get_data_addr(game->tex_west.ptr,
			&game->tex_west.bpp, &game->tex_west.line_len,
			&game->tex_west.endian);
	
	game->tex_east.ptr = mlx_xpm_file_to_image(game->mlx,
			map_info->colors.east, &width, &height);
	if (!game->tex_east.ptr)
		return (0);
	game->tex_east.addr = mlx_get_data_addr(game->tex_east.ptr,
			&game->tex_east.bpp, &game->tex_east.line_len,
			&game->tex_east.endian);
	
	return (1);
}

int	init_game(t_game *game, t_map_info *map_info)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (write(2, "Error: mlx_init failed\n", 23), 0);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		return (write(2, "Error: mlx_new_window failed\n", 29), 0);
	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img.ptr)
		return (write(2, "Error: mlx_new_image failed\n", 28), 0);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	/* Charge toutes les textures XPM depuis les chemins du .cub */
	if (!load_textures(game, map_info))
		return (write(2, "Error: texture loading failed\n", 30), 0);
	game->map = map_info->map_grid;
	init_player(game, map_info);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	return (1);
}
