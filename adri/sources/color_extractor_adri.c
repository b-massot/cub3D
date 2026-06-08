/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_extractor_adri.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:00:00 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 14:48:36 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

static int	read_color_value(char *line, int *pos)
{
	int	value;

	value = 0;
	while (line[*pos] >= '0' && line[*pos] <= '9')
	{
		value = value * 10 + (line[*pos] - '0');
		(*pos)++;
	}
	return (value);
}

static void	store_color(int *color, int *pos, char *line, int index)
{
	color[index] = read_color_value(line, pos);
	while (line[*pos] == ' ' || line[*pos] == '\t')
		(*pos)++;
	if (index < 2 && line[*pos] == ',')
		(*pos)++;
	while (line[*pos] == ' ' || line[*pos] == '\t')
		(*pos)++;
}

int	extract_color_values(t_map_info *map, char *line, int i, char id)
{
	int	*color;
	int	j;

	color = malloc(sizeof(int) * 3);
	if (!color)
		return ((map->error_code = FAILED_MEMORY_ALLOCATION), 0);
	j = 0;
	while (j < 3)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		store_color(color, &i, line, j++);
	}
	if (id == 'F')
		map->colors.floor = color;
	else
		map->colors.ceiling = color;
	return (1);
}
