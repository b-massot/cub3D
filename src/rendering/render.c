/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <bmassot@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 00:00:00 by bmassot           #+#    #+#             */
/*   Updated: 2026/06/08 00:00:00 by bmassot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static void	render_column(t_game *game, int x)
{
	t_ray	ray;
	int		line_height;
	int		ceiling_height;

	init_ray(game, &ray, x);
	set_steps_and_sidedist(game, &ray);
	perform_dda(game, &ray);
	if (ray.side == 0)
		ray.perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
	else
		ray.perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;
	if (ray.perp_wall_dist <= 0.0001)
		ray.perp_wall_dist = 0.0001;
	
	line_height = (int)(WIN_H / ray.perp_wall_dist);
	ceiling_height = -line_height / 2 + WIN_H / 2;
	if (ceiling_height < 0)
		ceiling_height = 0;
	
	draw_column_ceiling_floor(game, x, ceiling_height);
	draw_wall_slice(game, &ray, x);
}

void	render_frame(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		render_column(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}
