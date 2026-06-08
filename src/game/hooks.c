/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <bmassot@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 00:00:00 by bmassot           #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by bmassot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == ESC)
		close_window(param);
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

int	key_release(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
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

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	/* Detruit les 4 textures pour eviter les fuites memoire */
	if (game->tex_north.ptr)
		mlx_destroy_image(game->mlx, game->tex_north.ptr);
	if (game->tex_south.ptr)
		mlx_destroy_image(game->mlx, game->tex_south.ptr);
	if (game->tex_west.ptr)
		mlx_destroy_image(game->mlx, game->tex_west.ptr);
	if (game->tex_east.ptr)
		mlx_destroy_image(game->mlx, game->tex_east.ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map_grid(&game->map);
	exit(0);
	return (0);
}

int	loop_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_player(game);
	render_frame(game);
	return (0);
}
