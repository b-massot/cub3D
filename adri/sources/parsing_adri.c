/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_adri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 12:49:04 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/07 13:08:48 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

static int	extract_identifier_data(t_map_info *map, char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && !check_texture(line, i + 2))
		return ((map->error_code = TEXTURE_INVALID), 0);
	if (ft_strncmp(&line[i], "SO", 2) == 0 && !check_texture(line, i + 2))
		return ((map->error_code = TEXTURE_INVALID), 0);
	if (ft_strncmp(&line[i], "WE", 2) == 0 && !check_texture(line, i + 2))
		return ((map->error_code = TEXTURE_INVALID), 0);
	if (ft_strncmp(&line[i], "EA", 2) == 0 && !check_texture(line, i + 2))
		return ((map->error_code = TEXTURE_INVALID), 0);
	if (ft_strncmp(&line[i], "F ", 2) == 0 && !check_color(line, i + 2))
		return ((map->error_code = COLOR_INVALID), 0);
	if (ft_strncmp(&line[i], "C ", 2) == 0 && !check_color(line, i + 2))
		return ((map->error_code = COLOR_INVALID), 0);
	return (1);
}

static int	flood_fill(char **grid, int y, int x, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (0);
	if (grid[y][x] == '.' || grid[y][x] == '\0' || grid[y][x] == '\n')
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);
	grid[y][x] = 'V';
	if (!flood_fill(grid, y + 1, x, height, width)
		|| !flood_fill(grid, y - 1, x, height, width)
		|| !flood_fill(grid, y, x + 1, height, width)
		|| !flood_fill(grid, y, x - 1, height, width))
		return (0);
	return (1);
}

static int	get_max_width(char **file, int start, int height)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (i < height)
	{
		len = ft_strlen(file[start + i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static int	check_walls_and_player(t_map_info *map, int start, int height)
{
	char	**temp_grid;
	int		i;
	int		p_x;
	int		p_y;
	int		max_w;

	max_w = get_max_width(map->file, start, height);
	temp_grid = malloc(sizeof(char *) * (height + 1));
	if (!temp_grid)
		return (0);
	i = -1;
	p_y = -1;
	while (++i < height)
	{
		temp_grid[i] = malloc(sizeof(char) * (max_w + 1));
		ft_memset(temp_grid[i], '.', max_w);
		temp_grid[i][max_w] = '\0';
		int len = ft_strlen(map->file[start + i]);
		if (len > 0 && map->file[start + i][len - 1] == '\n')
			len--;
		ft_memcpy(temp_grid[i], map->file[start + i], len);
		int j = -1;
		while (temp_grid[i][++j])
		{
			if (ft_strchr("NSWE", temp_grid[i][j]))
			{
				p_x = j;
				p_y = i;
			}
		}
	}
	temp_grid[height] = NULL;
	if (p_y == -1 || !flood_fill(temp_grid, p_y, p_x, height, max_w))
		return (free_file_array(temp_grid), (map->error_code = INVALID_MAP), 0);
	return (free_file_array(temp_grid), 1);
}

static int	validate_map_characters(t_map_info *map, int start_line)
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
			else if (map->file[i][j] != '0' && map->file[i][j] != '1'
				&& map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\n')
				return ((map->error_code = INVALID_MAP), 0);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return ((map->error_code = INVALID_MAP), 0);
	return (check_walls_and_player(map, start_line, i - start_line));
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
		int type = check_identifier_type(map->file[i]);
		if (type > 0)
		{
			if (in_map)
				return ((map->error_code = INVALID_MAP), 0);
			if (!extract_identifier_data(map, map->file[i], 0))
				return (0);
		}
		else
		{
			if (in_map == 2)
				return ((map->error_code = INVALID_MAP), 0);
			if (!in_map)
			{
				in_map = 1;
				map_start = i;
			}
		}
		i++;
	}
	if (map_start == -1)
		return ((map->error_code = MAP_EMPTY), 0);
	return (validate_map_characters(map, map_start));
}

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

int	init_map(t_map_info	*map, char	*str)
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