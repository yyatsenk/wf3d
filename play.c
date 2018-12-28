/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:12:11 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/12/10 10:12:12 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void dda_find_algorithm(t_mlx *mlx)
{
  while (mlx->wall_is_here == 0)
  {
    if (mlx->side_dist.x < mlx->side_dist.y)
    {
      mlx->side_dist.x += mlx->delta_dist.x;
      mlx->map.x += mlx->step.x;
      mlx->side = 0;
    }
    else
    {
      mlx->side_dist.y += mlx->delta_dist.y;
      mlx->map.y += mlx->step.y;
      mlx->side = 1;
    }
    if (mlx->game_map[mlx->map.x][mlx->map.y] > 0)
    {
      mlx->wall_is_here = 1;
      if (mlx->side == 0) 
        mlx->wall_dist = (mlx->map.x - mlx->pos.x\
        + (1 - mlx->step.x) / 2) / mlx->ray_dir.x;
      else          
        mlx->wall_dist = (mlx->map.y - mlx->pos.y\
        + (1 - mlx->step.y) / 2) / mlx->ray_dir.y;
    }
  }
}
static void set_steps(t_mlx *mlx)
{
  if (mlx->ray_dir.x < 0 && (mlx->step.x = -1))
    mlx->side_dist.x = (mlx->pos.x - mlx->map.x) *\
    mlx->delta_dist.x;
  else
  {
    mlx->step.x = 1;
    mlx->side_dist.x = (mlx->map.x + 1 - mlx->pos.x) *\
    mlx->delta_dist.x;
  }
  if (mlx->ray_dir.y < 0 && (mlx->step.y = -1))
    mlx->side_dist.y = (mlx->pos.y - mlx->map.y) *\
    mlx->delta_dist.y;
  else
  {
    mlx->step.y = 1;
    mlx->side_dist.y = (mlx->map.y + 1 - mlx->pos.y) *\
    mlx->delta_dist.y;
  }
}

static void bonus_color_change(t_mlx *mlx)
{
  if (mlx->color_change == 1)
  {
    if (mlx->color1 == 0 || mlx->color2 == 0\
    || mlx->color3 == 0 || mlx->color4 == 0)
      color_intlz(mlx);
    else
    {
      mlx->color1 *= rand();
	    mlx->color2 += rand();
	    mlx->color3 += rand();
	    mlx->color4 -= rand();
      mlx->ceil_color -= rand();
    }
  }
}
int draw_it_for_me(t_mlx *mlx)
{
  int x;

  x = -1;
  bonus_color_change(mlx);
  while (++x < WIDTH)
  {
      mlx->cam = 2 * x / (double)WIDTH - 1;
      mlx->ray_dir.x = mlx->dir.x + mlx->plain.x * mlx->cam;
      mlx->ray_dir.y = mlx->dir.y + mlx->plain.y * mlx->cam;
      mlx->map.x = (int)mlx->pos.x;
      mlx->map.y = (int)mlx->pos.y;
      mlx->delta_dist.x = sqrt(1 + pow(mlx->ray_dir.y, 2)\
      / pow(mlx->ray_dir.x, 2));
      mlx->delta_dist.y = sqrt(1 + pow(mlx->ray_dir.x, 2)\
       / pow(mlx->ray_dir.y, 2));
      mlx->wall_is_here = 0; 
      set_steps(mlx);
      dda_find_algorithm(mlx);
      draw_line(mlx, x);
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image_ptr, 0,0);
    return (0);
}