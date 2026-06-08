/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren & bmassot                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:13:24 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by bmassot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_error_text(int code)
{
	if (code == FAILED_MEMORY_ALLOCATION)
		return ("Memory allocation failed");
	if (code == MAP_EMPTY)
		return ("Map file is empty");
	if (code == COLOR_INVALID)
		return ("Invalid RGB color format");
	if (code == TEXTURE_INVALID)
		return ("Invalid or missing texture path");
	if (code == DOUBLE_IDENTIFIERS)
		return ("Textures or colors are not unique identifiers");
	if (code == INVALID_MAP)
		return ("Invalid map configuration");
	return ("Unknown error");
}

int	print_error(char *message, int error_code)
{
	ft_putstr_fd("Error\n", 2);
	if (error_code != -1)
	{
		ft_putstr_fd(get_error_text(error_code), 2);
	}
	else
	{
		ft_putstr_fd(message, 2);
	}
	ft_putstr_fd("\n", 2);
	return (1);
}

void	free_file_array(char **file)
{
	int	i;

	if (!file)
		return ;
	i = 0;
	while (file[i] != NULL)
	{
		free(file[i]);
		i++;
	}
	free(file);
}

void	free_map_colors(t_map_color *colors)
{
	if (colors->north)
		free(colors->north);
	if (colors->south)
		free(colors->south);
	if (colors->west)
		free(colors->west);
	if (colors->east)
		free(colors->east);
	if (colors->floor)
		free(colors->floor);
	if (colors->ceiling)
		free(colors->ceiling);
}

void	free_map_grid(t_map_grid *grid)
{
	if (!grid)
		return ;
	if (grid->grid)
	{
		free_file_array(grid->grid);
		grid->grid = NULL;
	}
}

void	free_map_info(t_map_info *map)
{
	if (!map)
		return ;
	if (map->file)
	{
		free_file_array(map->file);
		map->file = NULL;
	}
	free_map_grid(&map->map_grid);
	free_map_colors(&map->colors);
	if (map->fd > 0)
		close(map->fd);
	free(map);
}
