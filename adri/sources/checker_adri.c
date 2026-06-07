/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_adri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:58:13 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/07 13:02:05 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

int	check_extension(char *str)
{
	int len;
	
	len = ft_strlen(str);
	if (len < 5)
		return (0);
	if (ft_strncmp(&str[len-4], ".cub", 4) == 0)
		return (1);
	return (0);
}

int	check_path(char *str)
{
	int	fd;

	if (!str)
		return (0);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static int	check_all_identifiers_present(int *found)
{
	int	i;
 
	i = 0;
	while (i < 6)
	{
		if (found[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	get_id_index(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0)
		return (0);
	if (ft_strncmp(&line[i], "SO", 2) == 0)
		return (1);
	if (ft_strncmp(&line[i], "WE", 2) == 0)
		return (2);
	if (ft_strncmp(&line[i], "EA", 2) == 0)
		return (3);
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (4);
	if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (5);
	return (-1);
}

int	check_map_validity(t_map_info *map)
{
	int	i;
	int	found[6];
	int	in_map;
	int	map_start;
	int	idx;

	i = 0;
	in_map = 0;
	map_start = -1;
	ft_memset(found, 0, sizeof(found));
	while (map->file[i])
	{
		if (check_empty_line(map->file[i]))
		{
			i++;
			continue ;
		}
		idx = get_id_index(map->file[i]);
		if (!in_map && idx >= 0)
		{
			if (found[idx] == 1)
				return ((map->error_code = DOUBLE_IDENTIFIERS), 0);
			found[idx] = 1;
			i++;
			continue ;
		}
		if (!in_map)
		{
			in_map = 1;
			map_start = i;
		}
		i++;
	}
	if (!check_all_identifiers_present(found))
		return ((map->error_code = TEXTURE_INVALID), 0);
	if (map_start == -1)
		return ((map->error_code = MAP_EMPTY), 0);
	return (1);
}