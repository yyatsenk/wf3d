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
	if ((mlx->step.x == -1 && mlx->step.y == -1) ||
		(mlx->step.x == 1 && mlx->step.y == -1))
		return (mlx->color1);
	if ((mlx->step.x == -1 && mlx->step.y == 1) ||
		(mlx->step.x == 1 && mlx->step.y == 1))
		return (mlx->color2);
	return (0);
}

static void			put_it(t_mlx *mlx, int x, int y, unsigned int c)
{
	if (c != mlx->ceil_color && c != mlx->ground_color)
	{
		if (mlx->side == 1)
			c = if_wall(mlx);
		else if ((mlx->step.x == -1 && mlx->step.y == -1) ||
			(mlx->step.x == -1 && mlx->step.y == 1))
			c = mlx->color3;
		else
			c = mlx->color4;
	}
	if ((y * WIDTH + x) <= WIDTH * HEIGHT)
		mlx->data[y * WIDTH + x] = c;
}

void			draw_line(t_mlx *mlx, int x)
{
	int				y;
	unsigned int	color;

	mlx->line_height = (int)(HEIGHT / mlx->wall_dist);
  mlx->draw_srt_end.x = -(mlx->line_height) / 2 + HEIGHT / 2;
  if(mlx->draw_srt_end.x < 0)
    mlx->draw_srt_end.x = 0;
  mlx->draw_srt_end.y = mlx->line_height / 2 + HEIGHT / 2;
  if(mlx->draw_srt_end.y >= HEIGHT)
    mlx->draw_srt_end.y = HEIGHT - 1;
	color = 0x111111;
	y = -1;
	while (++y < mlx->draw_srt_end.x)
		put_it(mlx, x, y, mlx->ceil_color);
	y -= 1;
	while (y++ <= mlx->draw_srt_end.y && y < HEIGHT)
		put_it(mlx, x, y, color);
	y -= 1;
	while (y++ <= HEIGHT)
		put_it(mlx, x, y, mlx->ground_color);
}
