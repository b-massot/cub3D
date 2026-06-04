/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_adri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:58:16 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 16:11:02 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

char *get_error_text(int code)
{
    if (code == FAILED_MEMORY_ALLOCATION)
        return ("Memory allocation failed");
    if (code == MAP_EMPTY)
        return ("Map file is empty");
    if (code == COLOR_INVALID)
        return ("Invalid RGB color format");
    if (code == TEXTURE_INVALID)
        return ("Invalid or missing texture path");
    return ("Unknown error");
}
int print_error(char *message, int error_code)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	if (error_code != -1)
		ft_putstr_fd(get_error_text(error_code), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void    free_file_array(char **file)
{
    int i;

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

void    free_map(t_map_info *map)
{
    if (!map)
        return ;
    if (map->file)
    {
        free_file_array(map->file);
        map->file = NULL;
    }
    if (map->map_grid.grid)
    {
        free_file_array(map->map_grid.grid);
        map->map_grid.grid = NULL;
    }
    if (map->colors.north)
        free(map->colors.north);
    if (map->colors.south)
        free(map->colors.south);
    if (map->colors.west)
        free(map->colors.west);
    if (map->colors.east)
        free(map->colors.east);
    if (map->colors.floor)
        free(map->colors.floor);
    if (map->colors.ceiling)
        free(map->colors.ceiling);
    if (map->fd > 0)
        close(map->fd);
    free(map);
}
