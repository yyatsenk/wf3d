/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:22:54 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/03/27 18:22:55 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


static unsigned int	if_wall(t_mlx *mlx)
{
	if (mlx->side == 1)
	{
		if ((mlx->step.x == -1 && mlx->step.y == -1) ||
		(mlx->step.x == 1 && mlx->step.y == -1))
			return (0);
		if ((mlx->step.x == -1 && mlx->step.y == 1) ||
		(mlx->step.x == 1 && mlx->step.y == 1))
			return (1);
	}
	if ((mlx->step.x == -1 && mlx->step.y == -1) ||
		(mlx->step.x == -1 && mlx->step.y == 1))
		return (2);
	else
		return (3);
	return (0);
}

static void			put_it(t_mlx *mlx, int x, int y, unsigned int c)
{
	if ((y * WIDTH + x) <= WIDTH * HEIGHT)
		mlx->data[y * WIDTH + x] = c;
}

static void			maintain_texture(t_mlx *mlx, int c)
{
	if (mlx->side == 0)
		mlx->wall_x = mlx->pos.y + mlx->wall_dist * mlx->ray_dir.y;
	else
		mlx->wall_x = mlx->pos.x + mlx->wall_dist * mlx->ray_dir.x;
	mlx->wall_x -= floor((mlx->wall_x));
	mlx->txtr.x = (int)(mlx->wall_x * (double)mlx->texture[c].width);
	if(mlx->side == 0 && mlx->ray_dir.x > 0)
		mlx->txtr.x = mlx->texture[c].width - mlx->txtr.x - 1;
	if(mlx->side == 1 && mlx->ray_dir.y < 0)
		mlx->txtr.x = mlx->texture[c].width - mlx->txtr.x - 1;
}

static void			draw_walls(t_mlx *mlx, int c, int y_ax, int x)
{
	int				color;
	int				var;
	int				dd;
	
	dd = y_ax * 256 - HEIGHT * 128 + mlx->line_height * 128;
	mlx->txtr.y = ((dd * mlx->texture[c].width) /mlx->line_height) / 256;
	var = mlx->texture[c].width * mlx->txtr.y + mlx->txtr.x;
	if (var < 0)
		var = -var;
	if (var < mlx->texture[c].width * mlx->texture[c].height && var >= 0)
		color = mlx->texture[c].ptr[var];
	if(mlx->side == 1)
		color = (color >> 1) & 8355711;
	put_it(mlx, x, y_ax, color);
}

void				draw_line(t_mlx *mlx, int x)
{
	int				y_ax;
	int				c;
	
	mlx->line_height = (int)(HEIGHT / mlx->wall_dist);
	mlx->draw_srt_end.x = -(mlx->line_height) /\
	2 + HEIGHT / 2 - mlx->sit_down;
	if(mlx->draw_srt_end.x < 0)
		mlx->draw_srt_end.x = 0;
	mlx->draw_srt_end.y = mlx->line_height / 2 + HEIGHT /\
	2 - mlx->sit_down;
	if(mlx->draw_srt_end.y >= HEIGHT)
		mlx->draw_srt_end.y = HEIGHT - 1;
	c = if_wall(mlx);
	maintain_texture(mlx, c);
	y_ax = -1;
	while (++y_ax < mlx->draw_srt_end.x)
		put_it(mlx, x, y_ax, mlx->ceil_color);
	y_ax -= 1;
	while (y_ax++ <= mlx->draw_srt_end.y && y_ax < HEIGHT)
		draw_walls(mlx, c, y_ax, x);
	y_ax -= 1;
	while (y_ax++ <= HEIGHT)
		put_it(mlx, x, y_ax, mlx->ground_color);
}
