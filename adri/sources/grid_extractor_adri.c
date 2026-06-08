/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_extractor_adri.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:00:00 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 14:49:31 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

static int	copy_line_to_grid(char **grid, char *source, int i, int len)
{
	grid[i] = malloc(sizeof(char) * (len + 1));
	if (!grid[i])
		return (0);
	ft_strlcpy(grid[i], source, len + 1);
	return (1);
}

static int	count_map_lines(t_map_info *map, int start_line)
{
	int	i;

	i = start_line;
	while (map->file[i])
		i++;
	return (i - start_line);
}

static int	prepare_grid_lines(char **grid, t_map_info *map, int start, int lines)
{
	int	i;
	int	j;

	i = 0;
	while (i < lines)
	{
		j = ft_strlen(map->file[start + i]);
		if (j > 0 && map->file[start + i][j - 1] == '\n')
			j--;
		if (!copy_line_to_grid(grid, map->file[start + i], i, j))
			return (free_file_array(grid), 0);
		i++;
	}
	return (1);
}

int	extract_map_grid(t_map_info *map, int start_line)
{
	char	**grid;
	int		map_lines;

	map_lines = count_map_lines(map, start_line);
	grid = malloc(sizeof(char *) * (map_lines + 1));
	if (!grid)
		return (0);
	if (!prepare_grid_lines(grid, map, start_line, map_lines))
		return (0);
	grid[map_lines] = NULL;
	map->map_grid.grid = grid;
	return (1);
}
