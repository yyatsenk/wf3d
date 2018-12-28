/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 13:15:51 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/12/10 13:15:52 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		dist1(t_mlx *mlx)
{
	if (mlx->hit == 0)
		mlx->perpWallDist = (mlx->mapX - mlx->pos_x + (1 - mlx->stepX)
			/ 2) / mlx->rayDirX;
	else
		mlx->perpWallDist = (mlx->mapY - mlx->pos_y + (1 - mlx->stepY)
			/ 2) / mlx->rayDirY;
}

void		dist(t_mlx *mlx)
{
	while (mlx->hit == 0)
	{
		if (mlx->wall_side.x < mlx->wall_side.y)
		{
			mlx->wall_side.x += mlx->r_delta.x;
			mlx->r_map.x += mlx->step.x;
			mlx->hit_side = 0;
		}
		else
		{
			mlx->wall_side.y += mlx->r_delta.y;
			mlx->r_map.y += mlx->step.y;
			mlx->hit_side = 1;
		}
		if (mlx->map[mlx->r_map.x][mlx->r_map.y] > 0)
		{
			mlx->hit = 1;
			dist1(mlx);
		}
	}
}
void		steps(t_mlx *mlx)
{
	if (mlx->r_dir.x < 0)
	{
		mlx->step.x = -1;
		mlx->wall_side.x = (mlx->pl_pos.x - (int)mlx->pl_pos.x)
			* mlx->r_delta.x;
	}
	else
	{
		mlx->step.x = 1;
		mlx->wall_side.x = ((int)mlx->pl_pos.x + 1 - mlx->pl_pos.x)
			* mlx->r_delta.x;
	}
	if (mlx->r_dir.y < 0)
	{
		mlx->step.y = -1;
		mlx->wall_side.y = (mlx->pl_pos.y - (int)mlx->pl_pos.y)
			* mlx->r_delta.y;
	}
	else
	{
		mlx->step.y = 1;
		mlx->wall_side.y = ((int)mlx->pl_pos.y + 1 - mlx->pl_pos.y)
			* mlx->r_delta.y;
	}
}