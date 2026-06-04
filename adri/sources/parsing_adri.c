/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_adri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 11:04:24 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 16:08:19 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

int	parsing_map(t_map_info *map)
{
	int	i;
	int line_number;

	i = 0;
	line_number = 0;
	while (map->file[i])
	{
		//check lignes vide -> avancer 
		//check identifiant avec sensible aux espaces
			//remplir la strucutre s_map_color
		// check lignes vides -> avancer
		// check map 
			// remplir la strucutre s_map et s_map_player
		// check lignes vides -> avancer
		
	}
}
void	read_map(t_map_info *map)
{
	// checks: info in the map, 1 and 0 in the map, floodfill, empty lines, space in the map
	//checks : texutres (valid, begin with identifier, etc), floor and ceiling, player, colors
    if (!fill_file_array(map) || !check_map_validity(map) ||!parsing_map(map))
        return ;
	//info_map(&map);

}

int	init_map(t_map_info	*map, char	*str)
{
	map->fd = open(str, O_RDONLY);
	map->validity = 1;
	map->error_code = -1;
	map->path = str;
	read_map(map);
	if (map->validity == -1)
		return (1);
	return (0);
}