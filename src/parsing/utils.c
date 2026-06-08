/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 12:48:44 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by bmassot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_lines(char *path)
{
	int		count;
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	fill_file_array(t_map_info *map)
{
	int		i;
	char	*line;

	map->fd = open(map->path, O_RDONLY);
	if (map->fd == -1)
		return ((map->error_code = FAILED_MEMORY_ALLOCATION), 0);
	i = 0;
	line = get_next_line(map->fd);
	while (line != NULL && i < map->height)
	{
		map->file[i++] = line;
		line = get_next_line(map->fd);
	}
	map->file[i] = NULL;
	close(map->fd);
	return (1);
}
