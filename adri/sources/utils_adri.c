/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_adri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 12:48:44 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 14:51:56 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

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
	int		total_lines;
	int		fd;

	total_lines = count_lines(map->path);
	if (total_lines <= 0)
		return ((map->error_code = MAP_EMPTY), 0);
	map->file = malloc(sizeof(char *) * (total_lines + 1));
	if (!map->file)
		return ((map->error_code = FAILED_MEMORY_ALLOCATION), 0);
	fd = open(map->path, O_RDONLY);
	if (fd == -1)
		return (free(map->file), (map->error_code = FAILED_MEMORY_ALLOCATION), 0);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->file[i++] = line;
		line = get_next_line(fd);
	}
	map->file[i] = NULL;
	close(fd);
	return (1);
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_identifier_type(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	if (ft_strncmp(&line[i], "NO", 2) == 0
		|| ft_strncmp(&line[i], "SO", 2) == 0
		|| ft_strncmp(&line[i], "WE", 2) == 0
		|| ft_strncmp(&line[i], "EA", 2) == 0)
		return (2);
	if (ft_strncmp(&line[i], "F ", 2) == 0
		|| ft_strncmp(&line[i], "C ", 2) == 0)
		return (1);
	return (0);
}

/* int	check_texture(char *line, int pos)
{
	int	end;
	int	len;

	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	if (line[pos] == '\0' || line[pos] == '\n')
		return (0);
	end = (int)ft_strlen(line) - 1;
	while (end >= pos
		&& (line[end] == ' ' || line[end] == '\t' || line[end] == '\n'))
	{
		line[end] = '\0';
		end--;
	}
	if (end < pos)
		return (0);
	len = (int)ft_strlen(&line[pos]);
	if (len < 5)
		return (0);
	if (ft_strncmp(&line[pos + len - 4], ".xpm", 4) != 0)
		return (0);
	return (check_path(&line[pos]));
}

int	check_color(char *line, int pos)
{
	int	value;
	int	count;

	count = 0;
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	while (count < 3)
	{
		if (line[pos] < '0' || line[pos] > '9')
			return (0);
		value = 0;
		while (line[pos] >= '0' && line[pos] <= '9')
		{
			value = value * 10 + (line[pos] - '0');
			pos++;
		}
		if (value < 0 || value > 255)
			return (0);
		while (line[pos] == ' ' || line[pos] == '\t')
			pos++;
		if (count < 2 && line[pos] != ',')
			return (0);
		if (count < 2)
			pos++;
		while (line[pos] == ' ' || line[pos] == '\t')
			pos++;
		count++;
	}
	if (line[pos] != '\0' && line[pos] != '\n')
		return (0);
	return (1);
}
 */