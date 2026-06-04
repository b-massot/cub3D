/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_adri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 11:04:24 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 13:51:09 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

void	read_map(t_map_info *map)
{
	// checks: info in the map, 1 and 0 in the map, floodfill, empty lines, space in the map
	//checks : texutres (valid, begin with identifier, etc), floor and ceiling, player, colors

	info_map(&map);

}

int	init_map(t_map_info	*map, char	*str)
{
	map->fd = open(str, O_RDONLY);
	map->validity = 1;
	map->path = str;
	read_map(map);
	if(map->validity == 1)
		return (close(map->fd), 1);
	return (close(map->fd), 0);
}