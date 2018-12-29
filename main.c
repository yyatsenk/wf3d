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

/*
void move_for_back(int keycode, t_mlx *mlx)
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
*/

/*
void bonus(int keycode, t_mlx *mlx)
{
  if (keycode == GO_FASTER)
    if (mlx->move_speed < 3)
      mlx->move_speed += 0.4;
  if (keycode == GO_SLOWER)
    if (mlx->move_speed > 0.4)
      mlx->move_speed -= 0.4;
  if (keycode == PSYCHO_ON)
    mlx->color_change = 1;
  if (keycode == PSYCHO_OFF)
  {
    mlx->color_change = 0;
    color_intlz(mlx);
  }
}

int			key_hook(int keycode, t_mlx *mlx)
{
  printf("%d\n", keycode);
	if (keycode == EXIT)
  {
    free_2d_int(mlx->game_map, mlx->map_size);
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
  bonus(keycode, mlx);
	return (0);
}

*/
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
    mlx->mlx_ptr = mlx_init();
		mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Wolf3d");
		mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
		mlx->data = (int*)mlx_get_data_addr(mlx->image_ptr, &(mlx->bpp),\
		&(mlx->size_line), &(mlx->end));
}
/*

unsigned int	if_wall(t_mlx *mlx)
{
	if ((mlx->step.x == -1 && mlx->step.y == -1) ||
		(mlx->step.x == 1 && mlx->step.y == -1))
		return (mlx->color1);
	if ((mlx->step.x == -1 && mlx->step.y == 1) ||
		(mlx->step.x == 1 && mlx->step.y == 1))
		return (mlx->color2);
	return (0);
}

void			put_it(t_mlx *mlx, int x, int y, unsigned int c)
{
	if (c != mlx->ceil_color && c != mlx->ground_color)
	{
		if (mlx->side == 1)
			c = if_wall(mlx);
		else if ((mlx->step.x == -1 && mlx->step.y == -1) ||
			(mlx->step.x == -1 && mlx->step.y == 1))
			c = mlx->color3;
		else
			c = mlx->color4;
	}
	if ((y * WIDTH + x) <= WIDTH * HEIGHT)
		mlx->data[y * WIDTH + x] = c;
}

void			draw_line(t_mlx *mlx, int x)
{
	int				y;
	unsigned int	color;

	mlx->line_height = (int)(HEIGHT / mlx->wall_dist);
  mlx->draw_srt_end.x = -(mlx->line_height) / 2 + HEIGHT / 2;
  if(mlx->draw_srt_end.x < 0)
    mlx->draw_srt_end.x = 0;
  mlx->draw_srt_end.y = mlx->line_height / 2 + HEIGHT / 2;
  if(mlx->draw_srt_end.y >= HEIGHT)
    mlx->draw_srt_end.y = HEIGHT - 1;
	color = 0x111111;
	y = -1;
	while (++y < mlx->draw_srt_end.x)
		put_it(mlx, x, y, mlx->ceil_color);
	y -= 1;
	while (y++ <= mlx->draw_srt_end.y && y < HEIGHT)
		put_it(mlx, x, y, color);
	y -= 1;
	while (y++ <= HEIGHT)
		put_it(mlx, x, y, mlx->ground_color);
}

void dda_find_algorithm(t_mlx *mlx)
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
void set_steps(t_mlx *mlx)
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

int draw_it_for_me(t_mlx *mlx)
{
  int x;

  x = -1;
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
  while (++x < WIDTH)
  {
      mlx->cam = 2 * x / (double)WIDTH - 1;
      mlx->ray_dir.x = mlx->dir.x + mlx->plain.x * mlx->cam;
      mlx->ray_dir.y = mlx->dir.y + mlx->plain.y * mlx->cam;
      mlx->map.x = (int)mlx->pos.x;
      mlx->map.y = (int)mlx->pos.y;
      mlx->delta_dist.x = sqrt(1 + pow(mlx->ray_dir.y, 2) / pow(mlx->ray_dir.x, 2));
      mlx->delta_dist.y = sqrt(1 + pow(mlx->ray_dir.x, 2) / pow(mlx->ray_dir.y, 2));
      mlx->wall_is_here = 0; 
      set_steps(mlx);
      dda_find_algorithm(mlx);
      draw_line(mlx, x);
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image_ptr, 0,0);
    return (0);
}
*/

/*
int check_line_size(char **char_map)
{
  int i;

  i = 0;
  while (char_map && char_map[i])
    i++;
  return (i);
}

void fill_line_int(t_mlx *mlx,char **char_map, int y)
{
  int i;
  int x;

  i = 0;
  x = 0;
  if (check_line_size(char_map) != mlx->map_size)
  {
    write(1, BAD_FILE_MSG, ft_strlen(BAD_FILE_MSG));
    free_2d(char_map);
    free_2d_int(mlx->game_map, mlx->map_size);
    exit(1);
  }
  mlx->game_map[y] = (int*)malloc(sizeof(int) * mlx->map_size);
  while (char_map && char_map[i])
  {
    mlx->game_map[y][x] = ft_atoi(char_map[i]);
    x++;
    i++;
  }
}

int check_border(t_mlx *mlx)
{
  int x;
  int y;

  x = -1;
  y = -1;
  while (++y < mlx->map_size)
  {
    while(++x < mlx->map_size)
    {
      if (y == 0 || y == mlx->map_size - 1)
      {
        if (mlx->game_map[y][x] != 1)
          return (0);
      }
      else if (mlx->game_map[y][0] != 1\
      || mlx->game_map[y][mlx->map_size - 1] != 1)
        return (0);
    }
    x = -1;
  }
  return (1);
}

int parse_file(char *filename, t_mlx *mlx, int fd)
{
  char **char_map;
  int   i;

  i = 0;
  if (fd < 0 || (get_next_line(fd, &mlx->str) < 1))
  {
    printf("loking for leaks_1\n");
		return (-1);
  }
  char_map = ft_strsplit(mlx->str, ' ');
  mlx->map_size = check_line_size(char_map);
  mlx->game_map = (int**)malloc(sizeof(int*) * mlx->map_size);
  fill_line_int(mlx, char_map, i);
  free_2d(char_map);
  free(mlx->str);
	while (get_next_line(fd, &mlx->str) == 1)
  {
    i++;
    if (i > mlx->map_size)
    {
      free_2d_int(mlx->game_map, mlx->map_size);
      free(mlx->str);
      printf("loking for leaks_1\n");
      return (0);
    }
    char_map = ft_strsplit(mlx->str, ' ');
    fill_line_int(mlx, char_map, i);
    free_2d(char_map);
    free(mlx->str);
  }
  if (!check_border(mlx))
  {
    write(1, BAD_BORDERS_MSG, ft_strlen(BAD_BORDERS_MSG));
    free_2d(char_map);
    exit(1);
  }
  return (1);
}
void check_map_pasring(char *filename, t_mlx *mlx)
{
  int fd;

  fd = open(filename, O_RDONLY);
	if ((read(fd, NULL, 0)) == -1)
  {
		per();
  }
	if (parse_file(filename, mlx, fd) == -1)
  {
    printf("saaadsadsadsa");
    close(fd);
    per();
  }
  close(fd);
}
*/
int main(int argv, char **argc)
{
  t_mlx	mlx;

	if (argv == 2)
	{
    srand(time(0)); 
    check_map_pasring(argc[1], &mlx);
		mlx_struct_init(&mlx, argc[1]);
    mlx_hook(mlx.win_ptr, 2, 5, key_hook, &mlx);
    mlx_hook(mlx.win_ptr, 17, 1L << 17, icon_close, 0);
    mlx_loop_hook(mlx.mlx_ptr, draw_it_for_me, &mlx);
    mlx_loop(mlx.mlx_ptr);
	}
	else
		write(1, ERROR_MSG, ft_strlen(ERROR_MSG));
	return (0);
}
