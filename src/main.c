/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot & ajeanren                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 00:00:00 by bmassot           #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by bmassot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;
	t_map_info	*map_info;

	if (argc != 2 || !argv[1][0] || !check_extension(argv[1])
		|| !check_path(argv[1]))
		return (print_error("Usage: ./cub3D <map.cub>", 1), 1);
	map_info = malloc(sizeof(t_map_info));
	if (!map_info)
		return (print_error("Memory allocation failed", 1), 1);
	ft_bzero(map_info, sizeof(t_map_info));
	if (!init_map(map_info, argv[1]))
	{
		print_error("Invalid map", map_info->error_code);
		free_map_info(map_info);
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	if (!init_game(&game, map_info))
	{
		free_map_info(map_info);
		return (1);
	}
	mlx_loop(game.mlx);
	return (0);
}
