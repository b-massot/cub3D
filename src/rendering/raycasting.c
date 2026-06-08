/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <bmassot@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 00:00:00 by bmassot           #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by bmassot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width)
		return (1);
	return (game->map.grid[y][x] == '1');
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)WIN_W - 1.0;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	ray->hit = 0;
}

void	set_steps_and_sidedist(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(game, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(int *)pixel;
	return (color);
}

void	draw_wall_slice(t_game *game, t_ray *ray, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		tex_x;
	int		tex_y;
	t_img	*texture;
	double	wall_x;
	double	tex_pos;
	double	step;

	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist <= 0.0001)
		ray->perp_wall_dist = 0.0001;
	
	line_height = (int)(WIN_H / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_H / 2;
	draw_end = line_height / 2 + WIN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_H)
		draw_end = WIN_H - 1;
	
	/* Determine la texture et calcule wallX */
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			texture = &game->tex_east;
		else
			texture = &game->tex_west;
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			texture = &game->tex_south;
		else
			texture = &game->tex_north;
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	wall_x -= floor(wall_x);
	
	/* Calcule la coordonnee X sur la texture */
	tex_x = (int)(wall_x * 64);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= 64)
		tex_x = 63;
	
	/* Mirroring correction selon direction */
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = 64 - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = 64 - tex_x - 1;
	
	/* Boucle Y avec affine texture mapping */
	step = 1.0 * 64 / line_height;
	tex_pos = (double)(draw_start - WIN_H / 2 + line_height / 2) * step;
	
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos & 63;
		tex_pos += step;
		put_pixel(&game->img, x, y, get_pixel_color(texture, tex_x, tex_y));
		y++;
	}
}
