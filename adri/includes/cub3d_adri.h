/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_adri.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:25:05 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/08 14:51:11 by ajeanren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ADRI_H
# define CUB3D_ADRI_H

# include "../../libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef enum e_error_parsing
{
	FAILED_MEMORY_ALLOCATION,
	MAP_EMPTY,
	COLOR_INVALID,
	TEXTURE_INVALID,
	DOUBLE_IDENTIFIERS,
	INVALID_MAP,
}	t_error;

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

char	*get_error_text(int code);
int		print_error(char *message, int error_code);
void	free_file_array(char **file);
void	free_map_colors(t_map_color *colors);
void	free_map(t_map_info *map);
int		check_extension(char *str);
int		check_path(char *str);
int		check_map_validity(t_map_info *map);
int		parsing_map(t_map_info *map);
int		read_map(t_map_info *map);
int		init_map(t_map_info *map, char *str);
int		count_lines(char *path);
int		fill_file_array(t_map_info *map);
int		check_color(char *line, int pos);
int		check_texture(char *line, int pos);
int		check_identifier_type(char *line);
int		check_empty_line(char *line);
int		extract_color_values(t_map_info *map, char *line, int i, char id);
//int		extract_map_grid(t_map_info *map, int start_line);
int		validate_map_content(t_map_info *map, int start_line);

#endif
