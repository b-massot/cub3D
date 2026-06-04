/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_adri.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanren <ajeanren@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 09:25:05 by ajeanren          #+#    #+#             */
/*   Updated: 2026/06/04 13:46:27 by ajeanren         ###   ########.fr       */
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

typedef	struct s_map{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef	struct s_map_player{
	char	direction;
	double	x;
	double	y;
}	t_map_player;

typedef	struct	s_map_info{
	int				fd;
	int				validity;
	char 			*path;
	int 			height;
	int 			width;
	t_map			map;
	t_map_color		colors;
	t_map_player	player;
}	t_map_info;


/* ---------------------
		FUNCTIONS
--------------------- */

/* MAIN */
int main(int argc, char **argv);

/* ERROR */
int print_error(char *message);

/* CHECKER */
int	check_extension(char *str);
int	check_path(char *str);

/* PARSING */

#endif