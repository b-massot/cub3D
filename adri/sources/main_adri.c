/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_adri.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:48:06 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/07 15:30:25 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_adri.h"

/* Extract map grid from file and store in structure. */
static int	extract_map_grid(t_map_info *map, int start_line)
{
	int		i;
	int		j;
	int		map_lines;
	char	**grid;

	i = start_line;
	map_lines = 0;
	while (map->file[i])
	{
		map_lines++;
		i++;
	}
	grid = malloc(sizeof(char *) * (map_lines + 1));
	if (!grid)
		return (0);
	i = 0;
	while (i < map_lines)
	{
		j = ft_strlen(map->file[start_line + i]);
		if (j > 0 && map->file[start_line + i][j - 1] == '\n')
			j--;
		grid[i] = malloc(sizeof(char) * (j + 1));
		if (!grid[i])
			return (free_file_array(grid), 0);
		ft_strlcpy(grid[i], map->file[start_line + i], j + 1);
		i++;
	}
	grid[map_lines] = NULL;
	map->map_grid.grid = grid;
	return (1);
}

/* Display all parsed map information from structure. */
void	print_map_info(t_map_info *map)
{
	int	i;

	ft_putstr_fd("\n=== MAP INFORMATION ===\n", 1);
	ft_putstr_fd("Path: ", 1);
	ft_putstr_fd(map->path, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("Validity: ", 1);
	ft_putnbr_fd(map->validity, 1);
	ft_putstr_fd("\n\n", 1);
	ft_putstr_fd("--- TEXTURES ---\n", 1);
	ft_putstr_fd("North (NO): ", 1);
	if (map->colors.north)
		ft_putstr_fd(map->colors.north, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("South (SO): ", 1);
	if (map->colors.south)
		ft_putstr_fd(map->colors.south, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("West (WE): ", 1);
	if (map->colors.west)
		ft_putstr_fd(map->colors.west, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("East (EA): ", 1);
	if (map->colors.east)
		ft_putstr_fd(map->colors.east, 1);
	ft_putstr_fd("\n\n", 1);
	ft_putstr_fd("--- COLORS ---\n", 1);
	ft_putstr_fd("Floor (F): ", 1);
	if (map->colors.floor)
	{
		ft_putnbr_fd(map->colors.floor[0], 1);
		ft_putstr_fd(",", 1);
		ft_putnbr_fd(map->colors.floor[1], 1);
		ft_putstr_fd(",", 1);
		ft_putnbr_fd(map->colors.floor[2], 1);
	}
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("Ceiling (C): ", 1);
	if (map->colors.ceiling)
	{
		ft_putnbr_fd(map->colors.ceiling[0], 1);
		ft_putstr_fd(",", 1);
		ft_putnbr_fd(map->colors.ceiling[1], 1);
		ft_putstr_fd(",", 1);
		ft_putnbr_fd(map->colors.ceiling[2], 1);
	}
	ft_putstr_fd("\n\n", 1);
	ft_putstr_fd("--- PLAYER ---\n", 1);
	ft_putstr_fd("Direction: ", 1);
	ft_putchar_fd(map->player.direction, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("Position X: ", 1);
	ft_putnbr_fd((int)map->player.x, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("Position Y: ", 1);
	ft_putnbr_fd((int)map->player.y, 1);
	ft_putstr_fd("\n\n", 1);
	ft_putstr_fd("--- MAP GRID ---\n", 1);
	ft_putstr_fd("Width: ", 1);
	ft_putnbr_fd(map->map_grid.width, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("Height: ", 1);
	ft_putnbr_fd(map->map_grid.height, 1);
	ft_putstr_fd("\n\n", 1);
	ft_putstr_fd("--- MAP ---\n", 1);
	i = 0;
	while (i < map->map_grid.height && map->map_grid.grid
		&& map->map_grid.grid[i])
	{
		ft_putstr_fd(map->map_grid.grid[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	ft_putstr_fd("\n=== END MAP INFORMATION ===\n\n", 1);
}

int	main(int argc, char **argv)
{
	t_map_info	*map;
	int			i;

	if (argc != 2 || !argv[1][0] || !check_extension(argv[1])
		|| !check_path(argv[1]))
		return (print_error("Invalid arguments, extension (.cub) or path", 1));
	map = malloc(sizeof(t_map_info));
	if (!map)
		return (print_error("Invalid memory allocation", 1));
	ft_memset(map, 0, sizeof(t_map_info));
	if (!init_map(map, argv[1]))
	{
		print_error("Invalid map : ", map->error_code);
		free_map(map);
		return (1);
	}
	i = 0;
	while (map->file[i])
	{
		if (!check_empty_line(map->file[i])
			&& check_identifier_type(map->file[i]) == 0)
			break ;
		i++;
	}
	if (!extract_map_grid(map, i))
	{
		print_error("Failed to extract map grid", -1);
		free_map(map);
		return (1);
	}
	print_map_info(map);
	free_map(map);
	return (0);
}
