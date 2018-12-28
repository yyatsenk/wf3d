/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:22:54 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/03/27 18:22:55 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int check_line_size(char **char_map)
{
  int i;

  i = 0;
  while (char_map && char_map[i])
    i++;
  return (i);
}

static void fill_line_int(t_mlx *mlx,char **char_map, int y)
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

static int check_border(t_mlx *mlx)
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

static int parse_file(char *filename, t_mlx *mlx, int fd)
{
  char **char_map;
  int   i;

  i = 0;
  if (fd < 0 || (get_next_line(fd, &mlx->str) < 1))
  {
    printf("loking for leaks_1\n");
    free(mlx->str);
    close(fd);
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
      printf("loking for leaks_2\n");
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
