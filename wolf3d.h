/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wold3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:13:06 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/12/10 10:13:07 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define BLUE 0x375587
# define WHITE 0xe3e9f4
# define ERROR_MSG "Usage:./fractol [mandelbrot, julia, burningship]\n"
# define HEIGHT 720
# define WIDTH 1080

typedef struct	s_coo
{
	int			x0;
	int			x1;
	int			y0;
	int			y1;
	double		deltax;
	double		deltay;
}				t_cc;

typedef struct		s_vec
{
	float			x;
	float			y;
}					t_vec;

typedef struct		s_ivec
{
	int				x;
	int				y;
} t_ivec;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image_ptr;
	unsigned	color;
	unsigned	color_1;
	unsigned	color_2;
	int			*data;
	int			bpp;
	int			size_line;
	int			end;
	float		pos_x;
	float		pos_y;
	float		dir_x;
	float		dir_y;
	float		plain_x;
	float		plain_y;
	float		time;
	float		oldtime;
	float		camera_x;
	int 		map_x;
    int 		map_y;
	int			**map;
	char		*name;
	int			iter;
	int			inf_zoom;


	unsigned int	c1;
	unsigned int	c2;
	unsigned int	c3;
	unsigned int	c4;
	unsigned int	c_s;
	unsigned int	c_g;
	t_vec step;
	float cameraX;
	float rayDirX;
	float rayDirY;
	int mapX;
	int mapY;
	float sideDistX;
	float sideDistY;
	float deltaDistX;
	float deltaDistY;
	float perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	float frameTime;
	float moveSpeed;
	float rotSpeed;
	t_cc	cord;
}				t_mlx;


#endif
