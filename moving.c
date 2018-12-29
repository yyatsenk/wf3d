/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:12:04 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/12/10 10:12:05 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		color_intlz(t_mlx *mlx)
{
	mlx->color1 = 0x002570;
	mlx->color2 = 0x00704a;
	mlx->color3 = 0x6a6d03;
	mlx->color4 = 0x6d026b;
	mlx->ceil_color = 0x0090ff;
	mlx->ground_color = 0x664848;
}

static void	bonus(int keycode, t_mlx *mlx)
{
	if (keycode == GO_FASTER)
		if (mlx->move_speed < 1)
			mlx->move_speed += 0.1;
	if (keycode == GO_SLOWER)
		if (mlx->move_speed > 0.5)
			mlx->move_speed -= 0.1;
	if (keycode == PSYCHO_ON)
		mlx->color_change = 1;
	if (keycode == PSYCHO_OFF)
	{
		mlx->color_change = 0;
		color_intlz(mlx);
	}
}

static void move_back(int keycode, t_mlx *mlx)
{
	if (keycode == MOVE_BACK)
	{
		mlx->old_dir = mlx->dir.x;
		mlx->dir.x = mlx->dir.x * cos(mlx->rot_speed) -\
		mlx->dir.y * sin(mlx->rot_speed);
		mlx->dir.y = mlx->old_dir * sin(mlx->rot_speed) + mlx->dir.y *\
		cos(mlx->rot_speed);
		mlx->old_plain = mlx->plain.x;
		mlx->plain.x = mlx->plain.x * cos(mlx->rot_speed) -\
		mlx->plain.y * sin(mlx->rot_speed);
		mlx->plain.y = mlx->old_plain * sin(mlx->rot_speed) +\
		mlx->plain.y * cos(mlx->rot_speed);
	}
}

static void move_for_back(int keycode, t_mlx *mlx)
{
	if (keycode == MOVE_FORWARD)
	{
		mlx->old_dir = mlx->dir.x;
		mlx->dir.x = mlx->dir.x * cos(-mlx->rot_speed) -\
		mlx->dir.y * sin(-mlx->rot_speed);
		mlx->dir.y = mlx->old_dir * sin(-mlx->rot_speed) +\
		mlx->dir.y * cos(-mlx->rot_speed);
		mlx->old_plain = mlx->plain.x;
		mlx->plain.x = mlx->plain.x * cos(-mlx->rot_speed) -\
		mlx->plain.y * sin(-mlx->rot_speed);
		mlx->plain.y = mlx->old_plain * sin(-mlx->rot_speed) +\
		mlx->plain.y * cos(-mlx->rot_speed);
	}
	move_back(keycode, mlx);
	bonus(keycode, mlx);
}

int			key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == EXIT)
	{
		mlx_mem_free(mlx, FREE_MAP_INT);
		exit(1);
	}
	if (keycode == MOVE_LEFT)
	{
		if(mlx->game_map[(int)(mlx->pos.x + mlx->dir.x *\
		mlx->move_speed)][(int)(mlx->pos.y)] == 0)
	 		mlx->pos.x += mlx->dir.x * mlx->move_speed;
		if(mlx->game_map[(int)(mlx->pos.x)][(int)(mlx->pos.y +\
		mlx->dir.y * mlx->move_speed)] == 0)
	  		mlx->pos.y += mlx->dir.y * mlx->move_speed;
	}
	if (keycode == MOVE_RIGHT)
	{
		if(mlx->game_map[(int)(mlx->pos.x - mlx->dir.x *\
		mlx->move_speed)][(int)(mlx->pos.y)] == 0)
			mlx->pos.x -= mlx->dir.x * mlx->move_speed;
		if(mlx->game_map[(int)(mlx->pos.x)][(int)(mlx->pos.y -\
		mlx->dir.y * mlx->move_speed)] == 0)
			mlx->pos.y -= mlx->dir.y * mlx->move_speed;
	}
	move_for_back(keycode, mlx);
	return (0);
}
