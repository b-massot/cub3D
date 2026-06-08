/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot & ajeanren                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 00:00:00 by bmassot          #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by bmassot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include "../../libft/libft.h"
# include "../../minilibx-linux/mlx.h"

/* ============= WINDOW & RENDERING ============= */
# define WIN_W 1024
# define WIN_H 768

/* ============= KEYBOARD ============= */
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

/* ============= GAME CONSTANTS ============= */
# define MOVE_SPEED 0.03
# define ROT_SPEED 0.03

/* ============= ERROR CODES ============= */
typedef enum e_error_parsing
{
	FAILED_MEMORY_ALLOCATION,
	MAP_EMPTY,
	COLOR_INVALID,
	TEXTURE_INVALID,
	DOUBLE_IDENTIFIERS,
	INVALID_MAP,
}	t_error;

/* ============= IMAGE STRUCTURE ============= */
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

/* ============= COLORS (TEXTURES & FLOOR/CEILING) ============= */
typedef struct s_map_color
{
	int		*floor;
	int		*ceiling;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_map_color;

/* ============= MAP GRID ============= */
typedef struct s_map_grid
{
	char	**grid;
	int		width;
	int		height;
}	t_map_grid;

/* ============= PLAYER (FROM PARSING) ============= */
typedef struct s_map_player
{
	char	direction;
	double	x;
	double	y;
}	t_map_player;

/* ============= PLAYER (GAME STATE) ============= */
typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	direction;
}	t_player;

/* ============= RAY (FOR RAYCASTING) ============= */
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

/* ============= MAP INFO (FROM PARSING) ============= */
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

/* ============= MAIN GAME STRUCTURE ============= */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	/* Textures XPM chargees depuis les chemins du fichier .cub */
	t_img		tex_north;
	t_img		tex_south;
	t_img		tex_west;
	t_img		tex_east;
	t_map_grid	map;
	t_player	player;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
}	t_game;

/* ============= FUNCTION DECLARATIONS ============= */

/* --- PARSING --- */
int		parsing_map(t_map_info *map);
int		read_map(t_map_info *map);
int		init_map(t_map_info *map, char *str);
int		check_extension(char *str);
int		check_path(char *str);
int		check_map_validity(t_map_info *map);
int		count_lines(char *path);
int		fill_file_array(t_map_info *map);
int		check_color(char *line, int pos);
int		check_texture(char *line, int pos);
int		check_identifier_type(char *line);
int		check_empty_line(char *line);
int		get_value_start(char *line);

/* --- ERROR HANDLING --- */
char	*get_error_text(int code);
int		print_error(char *message, int error_code);

/* --- MEMORY MANAGEMENT --- */
void	free_file_array(char **file);
void	free_map_colors(t_map_color *colors);
void	free_map_info(t_map_info *map);
void	free_map_grid(t_map_grid *grid);

/* --- RENDERING --- */
void	render_frame(t_game *game);
int		is_wall(t_game *game, int x, int y);
void	put_pixel(t_img *img, int x, int y, int color);

/* --- TEXTURES --- */
int		load_textures(t_game *game, t_map_info *map_info);

/* --- RAYCASTING --- */
void	init_ray(t_game *game, t_ray *ray, int x);
void	set_steps_and_sidedist(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	draw_wall_slice(t_game *game, t_ray *ray, int x);

/* --- GAME LOGIC --- */
void	rotate_player(t_game *game, double angle);
void	try_move(t_game *game, double move_x, double move_y);
void	update_player(t_game *game);
void	init_player(t_game *game, t_map_info *map_info);

/* --- INPUT HOOKS --- */
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		close_window(void *param);
int		loop_hook(void *param);

/* --- GAME INIT --- */
int		init_game(t_game *game, t_map_info *map_info);

#endif
