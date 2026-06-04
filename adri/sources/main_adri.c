/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adri.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:48:06 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 13:49:18 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

int main(int argc, char **argv)
{
    t_map_info  *map;

    if(argc != 2 || !argv[1][0] || (!check_extension(argv[1]) && !check_path(argv[1])))
        return (print_error("Invalid arguments (only 2), map extension (.cub) or path to map"));

    map = malloc(sizeof(t_map_info));
    if(!map)
        return (print_error("Invalid memory allocation"));
    if(!init_map(map, argv[1]))
        return (free_map(&map), print_error("Invalid map"));
    
    free_map()//free_all();
    return(0);
}
