/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_check_adri.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:00:00 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 15:16:58 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

static int	flood_fill(char **grid, int y, int x, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (0);
	if (grid[y][x] == '.' || grid[y][x] == '\0' || grid[y][x] == '\n')
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);
	grid[y][x] = 'V';
	if (!flood_fill(grid, y + 1, x, height, width))
		return (0);
	if (!flood_fill(grid, y - 1, x, height, width))
		return (0);
	if (!flood_fill(grid, y, x + 1, height, width))
		return (0);
	if (!flood_fill(grid, y, x - 1, height, width))
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

static int	find_player(t_map_info *map, char **temp_grid, int height, int max_w)
{
	int	i;
	int	j;
	int	p_x;
	int	p_y;

	p_y = -1;
	i = -1;
	while (++i < height)
	{
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
	if (p_y == -1 || !flood_fill(temp_grid, p_y, p_x, height, max_w))
		return (0);
	return (1);
}

int	check_walls_and_player(t_map_info *map, int start, int height)
{
	char	**temp_grid;
	int		max_w;
	int		i;
	int		len;

	max_w = get_max_width(map->file, start, height);
	temp_grid = malloc(sizeof(char *) * (height + 1));
	if (!temp_grid)
		return (0);
	i = 0;
	while (i < height)
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
		i++;
	}
	temp_grid[height] = NULL;
	if (!find_player(map, temp_grid, height, max_w))
		return (free_file_array(temp_grid),
			(map->error_code = INVALID_MAP), 0);
	map->map_grid.width = max_w;
	map->map_grid.height = height;
	return (free_file_array(temp_grid), 1);
}
