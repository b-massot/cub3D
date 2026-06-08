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
	if (!is_wall(game, (int)next_x, (int)next_y))
	{
		game->player.x = next_x;
		game->player.y = next_y;
	}
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
	game->player.x = map_info->player_x + 0.5;
	game->player.y = map_info->player_y + 0.5;
	game->player.direction = map_info->player_dir;
	
	if (map_info->player_dir == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (map_info->player_dir == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
	else if (map_info->player_dir == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (map_info->player_dir == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
}

//static void	draw_background(t_game *game, t_map_info *map_info)
//{
//	int	x;
//	int	y;
//	int	floor_color;
//	int	ceiling_color;

//	floor_color = (map_info->colors.floor[0] << 16)
//		| (map_info->colors.floor[1] << 8) | map_info->colors.floor[2];
//	ceiling_color = (map_info->colors.ceiling[0] << 16)
//		| (map_info->colors.ceiling[1] << 8) | map_info->colors.ceiling[2];
//	y = 0;
//	while (y < WIN_H)
//	{
//		x = 0;
//		while (x < WIN_W)
//		{
//			if (y < WIN_H / 2)
//				put_pixel(&game->img, x, y, ceiling_color);
//			else
//				put_pixel(&game->img, x, y, floor_color);
//			x++;
//		}
//		y++;
//	}
//}

/* Charge les 4 textures XPM (north, south, west, east) et stocke dans t_game */
int	load_textures(t_game *game, t_map_info *map_info)
{
	int	width;
	int	height;

	game->textures[0].ptr = mlx_xpm_file_to_image(game->mlx,
			map_info->colors.north, &width, &height);
	if (!game->textures[0].ptr)
		return (0);
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].ptr,
			&game->textures[0].bpp, &game->textures[0].line_len,
			&game->textures[0].endian);
	
	game->textures[1].ptr = mlx_xpm_file_to_image(game->mlx,
			map_info->colors.south, &width, &height);
	if (!game->textures[1].ptr)
		return (0);
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].ptr,
			&game->textures[1].bpp, &game->textures[1].line_len,
			&game->textures[1].endian);
	
	game->textures[2].ptr = mlx_xpm_file_to_image(game->mlx,
			map_info->colors.west, &width, &height);
	if (!game->textures[2].ptr)
		return (0);
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].ptr,
			&game->textures[2].bpp, &game->textures[2].line_len,
			&game->textures[2].endian);
	
	game->textures[3].ptr = mlx_xpm_file_to_image(game->mlx,
			map_info->colors.east, &width, &height);
	if (!game->textures[3].ptr)
		return (0);
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].ptr,
			&game->textures[3].bpp, &game->textures[3].line_len,
			&game->textures[3].endian);
	
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
	if (!load_textures(game, map_info))
		return (write(2, "Error: texture loading failed\n", 30), 0);
	game->map = map_info->grid;
	game->map_width = map_info->width;
	game->map_height = map_info->height;
	game->map_info = map_info;
	init_player(game, map_info);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	return (1);
}
