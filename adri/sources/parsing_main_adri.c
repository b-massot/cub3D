/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main_adri.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 12:49:04 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 13:53:13 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

int	parsing_map(t_map_info *map);

int	read_map(t_map_info *map)
{
	if (!fill_file_array(map))
		return (0);
	if (!check_map_validity(map))
		return (0);
	if (!parsing_map(map))
		return (0);
	return (1);
}

int	init_map(t_map_info *map, char *str)
{
	map->fd = open(str, O_RDONLY);
	if (map->fd == -1)
		return (0);
	close(map->fd);
	map->validity = 1;
	map->error_code = -1;
	map->path = str;
	if (!read_map(map))
	{
		map->validity = -1;
		return (0);
	}
	return (1);
}
