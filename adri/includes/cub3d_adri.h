/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_adri.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:25:05 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/07 15:23:31 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ADRI_H
# define CUB3D_ADRI_H

/* ---------------------
		LIBRAIRIES
--------------------- */

#include "../../libft/libft.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/* ---------------------
		MACROS
--------------------- */
typedef enum e_error_parsing
{
	FAILED_MEMORY_ALLOCATION,
	MAP_EMPTY,
	COLOR_INVALID,
	TEXTURE_INVALID,
	DOUBLE_IDENTIFIERS,
	INVALID_MAP,
}	t_error;

/* ---------------------
		STRUCTURES
--------------------- */

typedef struct s_map_color
{
	int		*floor;
	int		*ceiling;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_map_color;

typedef struct s_map_grid
{
	char	**grid;
	int		width;
	int		height;
}	t_map_grid;

typedef struct s_map_player
{
	char	direction;
	double	x;
	double	y;
}	t_map_player;

typedef struct s_map_info
{
	int			fd;
	char		**file;
	int			validity;
	char		*path;
	int			height;
	int			width;
	int			error_code;
	t_map_grid	map_grid;
	t_map_color	colors;
	t_map_player	player;
}	t_map_info;

/* ---------------------
		FUNCTIONS
--------------------- */

/* MAIN */

/* ERROR */
char	*get_error_text(int code);
int		print_error(char *message, int error_code);

/* FREE */
void	free_file_array(char **file);
void	free_map_colors(t_map_color *colors);
void	free_map(t_map_info *map);

/* CHECKER */
int		check_extension(char *str);
int		check_path(char *str);
int		check_map_validity(t_map_info *map);

/* PARSING */
int		parsing_map(t_map_info *map);
int		read_map(t_map_info *map);
int		init_map(t_map_info *map, char *str);

/* UTILS */
int		count_lines(char *path);
int		fill_file_array(t_map_info *map);
int		check_color(char *line, int pos);
int		check_texture(char *line, int pos);
int		check_identifier_type(char *line);
int		check_empty_line(char *line);
int		get_value_start(char *line);

#endif