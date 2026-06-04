/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_adri.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:25:05 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 16:09:11 by ajeanren         ###   ########.fr       */
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
	
} t_error;

/* ---------------------
		STRUCTURES
--------------------- */

typedef	struct s_map_color{
	int		*floor;
	int		*ceiling;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_map_color;

typedef	struct s_map_grid{
	char	**grid;
	int		width;
	int		height;
}	t_map_grid;

typedef	struct s_map_player{
	char	direction;
	double	x;
	double	y;
}	t_map_player;

typedef	struct	s_map_info{
	int				fd;
	char			**file;
	int				validity;
	char 			*path;
	int 			height;
	int 			width;
	int				error_code;
	t_map_grid		map_grid;
	t_map_color		colors;
	t_map_player	player;
}	t_map_info;


/* ---------------------
		FUNCTIONS
--------------------- */

/* MAIN */

/* ERROR */
int print_error(char *message, int erro_code);

/* CHECKER */
int	check_extension(char *str);
int	check_path(char *str);

/* PARSING */

#endif