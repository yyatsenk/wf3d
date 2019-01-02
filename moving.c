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

void move_side(t_mlx *mlx, float rot)
{
	mlx->old_dir = mlx->dir.x;
	mlx->dir.x = mlx->dir.x * cos(rot) -\
	mlx->dir.y * sin(rot);
	mlx->dir.y = mlx->old_dir * sin(rot) + mlx->dir.y *\
	cos(rot);
	mlx->old_plain = mlx->plain.x;
	mlx->plain.x = mlx->plain.x * cos(rot) -\
	mlx->plain.y * sin(rot);
	mlx->plain.y = mlx->old_plain * sin(rot) +\
	mlx->plain.y * cos(rot);
}


int	mouse_hook(int x, int y, t_mlx *mlx)
{
	float rot;
	
	y = y;
	if (!mlx->stat_x)
		mlx->stat_x = x;
	if (mlx->stat_x > x)
	{
		rot = ((mlx->stat_x - x) * 0.01);
		move_side(mlx, rot);
	}
	if (mlx->stat_x < x)
	{
		rot = -((x - mlx->stat_x) * 0.01);
		move_side(mlx, rot);
	}
	mlx->stat_x = x;
	return (0);
}

static void	bonus(int keycode, t_mlx *mlx)
{
	if (keycode == SIT_SOWN)
	{
		if (mlx->sit_flag == 0)
		{
			mlx->sit_down = 20;
			mlx->move_speed = 0.1;
			mlx->sit_flag = 1;
		}
		else
		{
			mlx->sit_down = 0;
			mlx->move_speed = 0.3;
			mlx->sit_flag = 0;
		}
	}
	if (keycode == DRUNKEN)
		mlx->drunken = mlx->drunken ? 0 : 1;
}

static void move_left_right(int keycode, t_mlx *mlx)
{
	if (keycode == MOVE_RIGHT || keycode == D)
	{
		move_side(mlx, -mlx->rot_speed);
	}
	if (keycode == MOVE_LEFT || keycode == A)
	{
		move_side(mlx, mlx->rot_speed);
	}
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
		mlx->ceil_color = 0x0090f1;
		mlx->ground_color = 0x664842;
	}
	bonus(keycode, mlx);
}

int			key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == EXIT)
	{
		mlx_mem_free(mlx, FREE_MAP_INT);
		exit(1);
	}
	if (keycode == MOVE_FORWARD || keycode == W)
	{
		if(mlx->game_map[(int)(mlx->pos.x + mlx->dir.x *\
		mlx->move_speed)][(int)(mlx->pos.y)] == 0)
	 		mlx->pos.x += mlx->dir.x * mlx->move_speed;
		if(mlx->game_map[(int)(mlx->pos.x)][(int)(mlx->pos.y +\
		mlx->dir.y * mlx->move_speed)] == 0)
	  		mlx->pos.y += mlx->dir.y * mlx->move_speed;
	}
	if (keycode == MOVE_BACK || keycode == S)
	{
		if(mlx->game_map[(int)(mlx->pos.x - mlx->dir.x *\
		mlx->move_speed)][(int)(mlx->pos.y)] == 0)
			mlx->pos.x -= mlx->dir.x * mlx->move_speed;
		if(mlx->game_map[(int)(mlx->pos.x)][(int)(mlx->pos.y -\
		mlx->dir.y * mlx->move_speed)] == 0)
			mlx->pos.y -= mlx->dir.y * mlx->move_speed;
	}
	move_left_right(keycode, mlx);
	return (0);
}
