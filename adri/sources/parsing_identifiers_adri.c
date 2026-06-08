/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identifiers_adri.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:00:00 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 14:48:51 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

int	process_texture_id(t_map_info *map, char *line, int i, char id);

static int	process_color_id(t_map_info *map, char *line, int i, char id)
{
	if (!check_color(line, i + 2))
		return ((map->error_code = COLOR_INVALID), 0);
	if (!extract_color_values(map, line, i + 2, id))
		return (0);
	return (1);
}

static int	extract_identifier_data(t_map_info *map, char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0)
		return (process_texture_id(map, line, i, 'N'));
	else if (ft_strncmp(&line[i], "SO", 2) == 0)
		return (process_texture_id(map, line, i, 'S'));
	else if (ft_strncmp(&line[i], "WE", 2) == 0)
		return (process_texture_id(map, line, i, 'W'));
	else if (ft_strncmp(&line[i], "EA", 2) == 0)
		return (process_texture_id(map, line, i, 'E'));
	else if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (process_color_id(map, line, i, 'F'));
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (process_color_id(map, line, i, 'C'));
	return (1);
}

static int	handle_line(t_map_info *map, int *in_map, int *map_start, int i)
{
	if (check_identifier_type(map->file[i]) > 0)
	{
		if (*in_map)
			return ((map->error_code = INVALID_MAP), 0);
		if (!extract_identifier_data(map, map->file[i], 0))
			return (0);
	}
	else
	{
		if (*in_map == 2)
			return ((map->error_code = INVALID_MAP), 0);
		if (!*in_map)
		{
			*in_map = 1;
			*map_start = i;
		}
	}
	return (1);
}

int	parsing_map(t_map_info *map)
{
	int	i;
	int	in_map;
	int	map_start;

	i = 0;
	in_map = 0;
	map_start = -1;
	while (map->file[i])
	{
		if (check_empty_line(map->file[i]))
		{
			if (in_map == 1)
				in_map = 2;
			i++;
			continue ;
		}
		if (!handle_line(map, &in_map, &map_start, i))
			return (0);
		i++;
	}
	if (map_start == -1)
		return ((map->error_code = MAP_EMPTY), 0);
	return (validate_map_content(map, map_start));
}
