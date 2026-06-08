/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_extractor_adri.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:00:00 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 14:48:24 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

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

int	process_texture_id(t_map_info *map, char *line, int i, char id)
{
	if (!check_texture(line, i + 2))
		return ((map->error_code = TEXTURE_INVALID), 0);
	if (!extract_texture_path(map, line, i + 2, id))
		return (0);
	return (1);
}
