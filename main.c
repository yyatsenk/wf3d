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

void			end(const char *msg)
{
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
	mlx->ceil_color = 0x0090f1;
	mlx->ground_color = 0x664842;
	mlx->char_map = NULL;
	mlx->game_map = NULL;
	mlx->str = NULL;
	mlx->sit_down = 0;
	mlx->drunken = 0;
	mlx->stat_x = 0;
}

static void		get_textures_2(t_mlx *mlx)
{
	if (!(mlx->texture[2].image = (void*)mlx_xpm_file_to_image(mlx->mlx_ptr,\
	"textures_hi/brick.xpm", &(mlx->texture[2].width),
	&(mlx->texture[2].height))))
		end("Bad texture is used\n");
	mlx->texture[2].ptr = (int*)mlx_get_data_addr(mlx->texture[2].image,\
	&(mlx->texture[2].bpp), &(mlx->texture[2].size_line),
	&(mlx->texture[2].endian));
	if (!(mlx->texture[3].image = (void*)mlx_xpm_file_to_image(mlx->mlx_ptr,\
	"textures_hi/metal.xpm", &(mlx->texture[3].width),
	&(mlx->texture[3].height))))
		end("Bad texture is used\n");
	mlx->texture[3].ptr = (int*)mlx_get_data_addr(mlx->texture[3].image,\
	&(mlx->texture[3].bpp), &(mlx->texture[3].size_line),
	&(mlx->texture[3].endian));
}

static void		get_textures(t_mlx *mlx)
{
	if (!(mlx->texture[0].image = (void*)mlx_xpm_file_to_image(mlx->mlx_ptr,\
	"textures_hi/wood.xpm", &(mlx->texture[0].width),
	&(mlx->texture[0].height))))
		end("Bad texture is used\n");
	mlx->texture[0].ptr = (int*)mlx_get_data_addr(mlx->texture[0].image,\
	&(mlx->texture[0].bpp), &(mlx->texture[0].size_line),
	&(mlx->texture[0].endian));
	if (!(mlx->texture[1].image = (void*)mlx_xpm_file_to_image(mlx->mlx_ptr,\
	"textures_hi/stone.xpm", &(mlx->texture[1].width),
	&(mlx->texture[1].height))))
		end("Bad texture is used\n");
	mlx->texture[1].ptr = (int*)mlx_get_data_addr(mlx->texture[1].image,\
	&(mlx->texture[1].bpp), &(mlx->texture[1].size_line),
	&(mlx->texture[1].endian));
	get_textures_2(mlx);
}

int				main(int argv, char **argc)
{
	t_mlx	mlx;

	if (argv == 2)
	{
		mlx_struct_init(&mlx, argc[1]);
		check_map_pasring(argc[1], &mlx);
		mlx.mlx_ptr = mlx_init();
		get_textures(&mlx);
		mlx.win_ptr = mlx_new_window(mlx.mlx_ptr,\
		WIDTH, HEIGHT, "Wolf3d");
		mlx.image_ptr = mlx_new_image(mlx.mlx_ptr,\
		WIDTH, HEIGHT);
		mlx.data = (int*)mlx_get_data_addr(mlx.image_ptr, &(mlx.bpp),\
		&(mlx.size_line), &(mlx.end));
		write_interface();
		mlx_hook(mlx.win_ptr, 2, 5, key_hook, &mlx);
		mlx_hook(mlx.win_ptr, 6, 1L << 6, mouse_hook, &mlx);
		mlx_hook(mlx.win_ptr, 17, 1L << 17, icon_close, 0);
		mlx_loop_hook(mlx.mlx_ptr, draw_it_for_me, &mlx);
		mlx_loop(mlx.mlx_ptr);
	}
	else
		write(1, ERROR_MSG, ft_strlen(ERROR_MSG));
	return (0);
}
