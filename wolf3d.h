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
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

# define ERROR_MSG			"Usage:./wolf3d [filename]\n"
# define BAD_FILE_MSG		"Map should be 24x24\n"
# define BAD_BORDERS_MSG	"Bad borders\n"
# define EMPTY_FILE_MSG		"Empty file\n"
# define HEIGHT				720
# define WIDTH				1080
# define MOVE_FORWARD		126
# define MOVE_BACK			125
# define MOVE_LEFT			123
# define MOVE_RIGHT			124
# define EXIT				53
# define GO_FASTER			3
# define GO_SLOWER			9
# define PSYCHO_ON			35
# define PSYCHO_OFF			31
# define SIT_SOWN			8
# define DRUNKEN			15
# define W					13
# define A					0
# define S					1
# define D					2
# define Q					12
# define FREE_MAP_INT		1
# define LEAVE_MAP_INT		0

typedef struct		s_texture
{
	void		*image;
	void		*m;
	void		*tex_mlx;
	int			*ptr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}					t_texture;

typedef struct		s_float_c
{
	float			x;
	float			y;
}					t_float_c;

typedef struct		s_int_c
{
	int				x;
	int				y;
}					t_int_c;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*image_ptr;
	int				*data;
	int				bpp;
	int				size_line;
	int				end;
	t_float_c		pos;
	t_float_c		dir;
	t_float_c		plain;
	char			*str;
	int				**game_map;
	char			*filename;
	int				color_change;
	unsigned int	ceil_color;
	unsigned int	ground_color;
	t_float_c		ray_dir;
	t_int_c			map;
	t_int_c			txtr;
	t_float_c		side_dist;
	t_float_c		delta_dist;
	t_int_c			draw_srt_end;
	t_int_c			step;
	float			wall_dist;
	int				wall_is_here;
	int				side;
	int				line_height;
	float			move_speed;
	float			rot_speed;
	float			cam;
	int				map_size;
	double			old_dir;
	double			old_plain;
	char			**char_map;
	t_texture		texture[4];
	double			wall_x;
	int				sit_down;
	int				drunken;
	int				sit_flag;
	int				stat_x;
}					t_mlx;

void				check_map_pasring(char *filename, t_mlx *mlx);
int					icon_close(void);
void				per(void);
void				color_intlz(t_mlx *mlx);
int					key_hook(int keycode, t_mlx *mlx);
int					draw_it_for_me(t_mlx *mlx);
void				draw_line(t_mlx *mlx, int x);
void				mlx_mem_free(t_mlx *mlx, int macro);
void				end(const char *msg);
int					mouse_hook(int x, int y, t_mlx *mlx);
void				move_side(t_mlx *mlx, float rot);
void				write_interface(void);
#endif
