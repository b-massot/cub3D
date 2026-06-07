/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map_adri.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:13:24 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/07 15:16:09 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

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

void    free_map_colors(t_map_color *colors)
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
    free_map_colors(&map->colors);
    if (map->fd > 0)
        close(map->fd);
    free(map);
}
