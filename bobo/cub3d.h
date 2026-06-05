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
    double	dir_x;
    double	dir_y;
    double	plane_x;
    double	plane_y;
}	t_player;

typedef struct s_ray
{
    double	camera_x;
    double	ray_dir_x;
    double	ray_dir_y;
    int		map_x;
    int		map_y;
    double	side_dist_x;
    double	side_dist_y;
    double	delta_dist_x;
    double	delta_dist_y;
    double	perp_wall_dist;
    int		step_x;
    int		step_y;
    int		hit;
    int		side;
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