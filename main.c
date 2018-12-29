/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:12:54 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/12/10 10:12:55 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void            end(t_mlx *mlx, int macro, const char *msg)
{
  mlx_mem_free(mlx, macro);
  write(1, msg, ft_strlen(msg));
  exit(1);
}


static void		mlx_struct_init(t_mlx *mlx, char *name)
{
	mlx->filename = name;
	mlx->pos.x = 22;
	mlx->pos.y = 12; 
	mlx->dir.x = -1;
	mlx->dir.y = 0; 
	mlx->plain.x = 0;
	mlx->plain.y = 1;
	mlx->move_speed = 0.3;
	mlx->rot_speed = 0.3;
	color_intlz(mlx);
	mlx->char_map = NULL;
	mlx->game_map = NULL;
	mlx->str = NULL;
}

int 		main(int argv, char **argc)
{
	t_mlx	mlx;

	if (argv == 2)
	{
		srand(time(0));
		mlx_struct_init(&mlx, argc[1]);
		check_map_pasring(argc[1], &mlx);
		mlx.mlx_ptr = mlx_init();
		mlx.win_ptr = mlx_new_window(mlx.mlx_ptr,\
		WIDTH, HEIGHT, "Wolf3d");
		mlx.image_ptr = mlx_new_image(mlx.mlx_ptr,\
		WIDTH, HEIGHT);
		mlx.data = (int*)mlx_get_data_addr(mlx.image_ptr, &(mlx.bpp),\
		&(mlx.size_line), &(mlx.end));
		mlx_hook(mlx.win_ptr, 2, 5, key_hook, &mlx);
		mlx_hook(mlx.win_ptr, 17, 1L << 17, icon_close, &mlx);
		mlx_loop_hook(mlx.mlx_ptr, draw_it_for_me, &mlx);
		mlx_loop(mlx.mlx_ptr);
	}
	else
		write(1, ERROR_MSG, ft_strlen(ERROR_MSG));
	return (0);
}
