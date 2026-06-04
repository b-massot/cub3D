/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adri.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:48:06 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 16:13:42 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

int main(int argc, char **argv)
{
	t_map_info	*map;

	if (argc != 2 || !argv[1][0] || !check_extension(argv[1]) || !check_path(argv[1]))
		return (print_error("Invalid arguments, extension (.cub) or path", -1));
		
	map = malloc(sizeof(t_map_info));
	if (!map)
		return (print_error("Invalid memory allocation", -1));
	ft_memset(map, 0, sizeof(t_map_info));

	if (!init_map(map, argv[1]))
	{
		print_error("Invalid map : ", map->error_code);
		free_map(map);
		return (1);
	}
	
	free_map(map);
	return (0);
}
