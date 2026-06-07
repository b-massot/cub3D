/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_adri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 12:49:04 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/07 15:24:40 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

/* Extract and store texture path from line starting at position i. */
static int	extract_texture_path(t_map_info *map, char *line, int i, char id)
{
	int		start;
	int		end;
	int		len;
	char	*path;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	end = i;
	len = end - start;
	if (len <= 0)
		return (0);
	path = malloc(sizeof(char) * (len + 1));
	if (!path)
		return ((map->error_code = FAILED_MEMORY_ALLOCATION), 0);
	ft_strlcpy(path, &line[start], len + 1);
	if (id == 'N')
		map->colors.north = path;
	else if (id == 'S')
		map->colors.south = path;
	else if (id == 'W')
		map->colors.west = path;
	else if (id == 'E')
		map->colors.east = path;
	return (1);
}

/* Parse RGB color values from line and store in color array. */
/* static int	parse_rgb_color(int *color_array)
{
	color_array = malloc(sizeof(int) * 3);
	if (!color_array)
		return (0);
	return (1);
} */

/* Extract and store RGB color values from line starting at position i. */
static int	extract_color_values(t_map_info *map, char *line, int i, char id)
{
	int		*color;
	int		j;
	int		value;

	color = malloc(sizeof(int) * 3);
	if (!color)
		return ((map->error_code = FAILED_MEMORY_ALLOCATION), 0);
	j = 0;
	while (j < 3)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		value = 0;
		while (line[i] >= '0' && line[i] <= '9')
		{
			value = value * 10 + (line[i] - '0');
			i++;
		}
		color[j] = value;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (j < 2 && line[i] == ',')
			i++;
		j++;
	}
	if (id == 'F')
		map->colors.floor = color;
	else if (id == 'C')
		map->colors.ceiling = color;
	return (1);
}

/* Parse identifier line and extract texture or color data. */
static int	extract_identifier_data(t_map_info *map, char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0)
	{
		if (!check_texture(line, i + 2))
			return ((map->error_code = TEXTURE_INVALID), 0);
		if (!extract_texture_path(map, line, i + 2, 'N'))
			return (0);
	}
	else if (ft_strncmp(&line[i], "SO", 2) == 0)
	{
		if (!check_texture(line, i + 2))
			return ((map->error_code = TEXTURE_INVALID), 0);
		if (!extract_texture_path(map, line, i + 2, 'S'))
			return (0);
	}
	else if (ft_strncmp(&line[i], "WE", 2) == 0)
	{
		if (!check_texture(line, i + 2))
			return ((map->error_code = TEXTURE_INVALID), 0);
		if (!extract_texture_path(map, line, i + 2, 'W'))
			return (0);
	}
	else if (ft_strncmp(&line[i], "EA", 2) == 0)
	{
		if (!check_texture(line, i + 2))
			return ((map->error_code = TEXTURE_INVALID), 0);
		if (!extract_texture_path(map, line, i + 2, 'E'))
			return (0);
	}
	else if (ft_strncmp(&line[i], "F ", 2) == 0)
	{
		if (!check_color(line, i + 2))
			return ((map->error_code = COLOR_INVALID), 0);
		if (!extract_color_values(map, line, i + 2, 'F'))
			return (0);
	}
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
	{
		if (!check_color(line, i + 2))
			return ((map->error_code = COLOR_INVALID), 0);
		if (!extract_color_values(map, line, i + 2, 'C'))
			return (0);
	}
	return (1);
}

/* Flood fill algorithm to validate map enclosed by walls. */
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

/* Get maximum line width to normalize grid. */
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

/* Extract player position and validate walls using flood fill. */
static int	check_walls_and_player(t_map_info *map, int start, int height)
{
	char	**temp_grid;
	int		i;
	int		p_x;
	int		p_y;
	int		max_w;
	int		len;
	int		j;

	max_w = get_max_width(map->file, start, height);
	temp_grid = malloc(sizeof(char *) * (height + 1));
	if (!temp_grid)
		return (0);
	i = -1;
	p_y = -1;
	while (++i < height)
	{
		temp_grid[i] = malloc(sizeof(char) * (max_w + 1));
		if (!temp_grid[i])
			return (free_file_array(temp_grid), 0);
		ft_memset(temp_grid[i], '.', max_w);
		temp_grid[i][max_w] = '\0';
		len = ft_strlen(map->file[start + i]);
		if (len > 0 && map->file[start + i][len - 1] == '\n')
			len--;
		ft_memcpy(temp_grid[i], map->file[start + i], len);
		j = -1;
		while (temp_grid[i][++j])
		{
			if (ft_strchr("NSWE", temp_grid[i][j]))
			{
				p_x = j;
				p_y = i;
				map->player.direction = temp_grid[i][j];
				map->player.x = (double)p_x;
				map->player.y = (double)p_y;
			}
		}
	}
	temp_grid[height] = NULL;
	if (p_y == -1 || !flood_fill(temp_grid, p_y, p_x, height, max_w))
		return (free_file_array(temp_grid), (map->error_code = INVALID_MAP), 0);
	map->map_grid.width = max_w;
	map->map_grid.height = height;
	return (free_file_array(temp_grid), 1);
}

/* Validate all map characters and ensure single player. */
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

/* Parse entire map file for identifiers and map data. */
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
		if (check_identifier_type(map->file[i]) > 0)
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

/* Initialize map structure from file. */
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

/* Open file and initialize map structure with parsed data. */
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