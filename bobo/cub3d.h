/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <bmassot@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:00:00 by bmassot           #+#    #+#             */
/*   Updated: 2026/01/21 00:00:00 by bmassot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define WIN_W 1024
# define WIN_H 768

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define MOVE_SPEED 0.08
# define ROT_SPEED 0.05

# define MINIMAP_SCALE 12

typedef struct s_img
{
    void	*ptr;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
}	t_img;

typedef struct s_map
{
    char	**grid;
    int		width;
    int		height;
}	t_map;

typedef struct s_player
{
    double	x;
    double	y;
    double	dir_x; // position of the player
    double	dir_y;
    double	plane_x; // direction vector of plane
    double	plane_y; // (perpendicular to the direction vector)
}	t_player;

typedef struct s_ray
{
    double	camera_x; // +1 0 or -1. for the FOV
    double	ray_dir_x; //position of a specific ray
    double	ray_dir_y;

	//which box of the map we're in
    int		map_x; //position of the current square the ray is in
    int		map_y;

	//length of ray from current position to next x or y-side
    double	side_dist_x; // distance from og position of the ray
    double	side_dist_y; // to first x-side or y-side (when touching a square)

	//length of ray from one x or y-side to next x or y-side
    double	delta_dist_x; // distance to go from 1 x-side to next x-side
    double	delta_dist_y;
    double	perp_wall_dist;

	//what direction to step in x or y-direction (either +1 or -1)
    int		step_x; // always +1 or -1
    int		step_y; // when we advance the ray, and so the squares
    int		hit; //was there a wall hit?
    int		side; //was a NS or a EW wall hit?
}	t_ray;

typedef struct s_game
{
    void		*mlx;
    void		*win;
    t_img		img;
    t_map		map;
    t_player	player;
    int			key_w;
    int			key_a;
    int			key_s;
    int			key_d;
    int			key_left;
    int			key_right;
}	t_game;

#endif