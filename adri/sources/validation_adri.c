/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_adri.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:00:00 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 15:05:46 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == '\t' || c == '\n'
		|| c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static int	count_players_and_validate(t_map_info *map, int start_line)
{
	int	i;
	int	j;
	int	player_count;

	i = start_line;
	player_count = 0;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] == 'N' || map->file[i][j] == 'S'
				|| map->file[i][j] == 'W' || map->file[i][j] == 'E')
				player_count++;
			else if (!is_valid_map_char(map->file[i][j]))
				return ((map->error_code = INVALID_MAP), 0);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return ((map->error_code = INVALID_MAP), 0);
	return (1);
}

int	validate_map_content(t_map_info *map, int start_line)
{
	if (!count_players_and_validate(map, start_line))
		return (0);
	return (check_walls_and_player(map, start_line,
		count_lines(map->path) - start_line));
}