/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_adri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 11:08:59 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 16:08:38 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

int	count_lines(char *path)
{
    int		count;
    char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
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
	int 	total_lines;

	total_lines = count_lines(map->path);
    if (total_lines <= 0)
		return ((map->error_code = 0), 0);
    map->file = malloc(sizeof(char *) * (total_lines + 1));
    if (!map->file)
        return ((map->error_code = 0), 0);
    i = 0;
    line = get_next_line(map->fd);
    while (line != NULL)
    {
        map->file[i] = line; 
        i++;
        line = get_next_line(map->fd);
    }
    map->file[i] = NULL;
    return (1);
}
