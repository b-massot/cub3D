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

static void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
				put_pixel(&game->img, x, y, 0x87CEEB);
			else
				put_pixel(&game->img, x, y, 0x3C2F2F);
			x++;
		}
		y++;
	}
}

void	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;

	draw_background(game);
	x = 0;
	while (x < WIN_W)
	{
		init_ray(game, &ray, x);
		set_steps_and_sidedist(game, &ray);
		perform_dda(game, &ray);
		draw_wall_slice(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}
