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
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

# define ERROR_MSG "Usage:./wolf3d [filename]\n"
# define BAD_FILE_MSG "Bad line size\n"
# define BAD_BORDERS_MSG "Bad borders\n"
# define HEIGHT 720
# define WIDTH 1080
# define MOVE_FORWARD	65363
# define MOVE_BACK  65361
# define MOVE_LEFT	65362
# define MOVE_RIGHT 65364
# define EXIT		65307
# define GO_FASTER  102
# define GO_SLOWER 	115
# define PSYCHO_ON		112
# define PSYCHO_OFF		111
# define COLORS			

typedef struct		s_float_c
{
	float			x;
	float			y;
}					t_float_c;

typedef struct		s_int_c
{
	int				x;
	int				y;
} 					t_int_c;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image_ptr;
	int			*data;
	int			bpp;
	int			size_line;
	int			end;
	t_float_c		pos;
	t_float_c		dir;
	t_float_c		plain;
	char 		*str;
	int			**game_map;
	char		*filename;
	int 		color_change;


	unsigned int	color1;
	unsigned int	color2;
	unsigned int	color3;
	unsigned int	color4;
	unsigned int	ceil_color;
	unsigned int	ground_color;
	t_float_c 			ray_dir;
	t_int_c 			map;
	t_float_c 			side_dist;
	t_float_c 			delta_dist;
	t_int_c 			draw_srt_end;
	t_int_c 			step;
	float 				wall_dist;
	int 				wall_is_here;
	int 				side;
	int 				line_height;
	float 				move_speed;
	float 				rot_speed;
	float 				cam;
	int					map_size;
	double old_dir;
    double old_plain;
}				t_mlx;
void 		check_map_pasring(char *filename, t_mlx *mlx);
int			icon_close(void);
void		per(void);
void 		color_intlz(t_mlx *mlx);
int			key_hook(int keycode, t_mlx *mlx);
void 		free_2d(char **str);
void 		free_2d_int(int **arr, int size);
int 		draw_it_for_me(t_mlx *mlx);
void		draw_line(t_mlx *mlx, int x);
#endif
