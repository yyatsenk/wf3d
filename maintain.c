/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:21:54 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/03/27 18:21:55 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	free_2d(t_mlx *mlx)
{
	int				i;
	
	i = -1;
	if (!mlx->char_map)
		return ;
	while (mlx->char_map[++i])
		free(mlx->char_map[i]);
	free(mlx->char_map[i]);
	free(mlx->char_map);
}

static void	free_2d_int(t_mlx *mlx)
{
	int				i;
	
	i = -1;
	if (!mlx->game_map)
		return ;
	while (++i < mlx->map_size)
		free(mlx->game_map[i]);
	free(mlx->game_map);
}

void				mlx_mem_free(t_mlx *mlx, int macro)
{
	free_2d(mlx);
	if (macro == 1)
		free_2d_int(mlx);
	if (mlx->str)
	{
		free(mlx->str);
		mlx->str = NULL;
	}
}

int				icon_close(t_mlx *mlx)
{
	mlx_mem_free(mlx, FREE_MAP_INT);
	exit(1);
	return (0);
}

void write_interface(void)
{
	write(1, "############################################\n", 46);
	write(1, "# w,s,a,d - forward, backward, left, right #\n", 46);
	write(1, "# f,v - go faster\\slower                   #\n", 46);
	write(1, "# p,o - psycho mode on\\off                 #\n", 46);
	write(1, "# c - sit down                             #\n", 46);
	write(1, "# r - drunken mode                         #\n", 46);
	write(1, "############################################\n", 46);
}