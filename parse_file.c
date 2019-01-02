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

static int	check_line_size(t_mlx *mlx)
{
	int		i;

	i = 0;
	while (mlx->char_map && mlx->char_map[i])
		i++;
	return (i);
}


static void	fill_line_int(t_mlx *mlx , int y)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (check_line_size(mlx) != mlx->map_size)
	{
		write(1, BAD_FILE_MSG, ft_strlen(BAD_FILE_MSG));
		mlx_mem_free(mlx, FREE_MAP_INT);
		exit(1);
	}
	mlx->game_map[y] = (int*)malloc(sizeof(int) * mlx->map_size);
	while (mlx->char_map && mlx->char_map[i])
	{
		mlx->game_map[y][x] = ft_atoi(mlx->char_map[i]);
		x++;
		i++;
	}
}

static int	check_border(t_mlx *mlx)
{
	int		x;
	int		y;

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

static void	parse_file(t_mlx *mlx, int fd)
{
	int		i;

	i = 0;
	mlx->char_map = ft_strsplit(mlx->str, ' ');
	mlx->map_size = check_line_size(mlx);
	if (mlx->map_size != 24)
		end(mlx, LEAVE_MAP_INT, BAD_FILE_MSG);
	mlx->game_map = (int**)malloc(sizeof(int*) * mlx->map_size);
	fill_line_int(mlx, i);
	mlx_mem_free(mlx, LEAVE_MAP_INT);
	while (get_next_line(fd, &mlx->str) == 1)
	{
		i++;
		if (i > mlx->map_size)
			end(mlx, FREE_MAP_INT, BAD_FILE_MSG);
		mlx->char_map = ft_strsplit(mlx->str, ' ');
		fill_line_int(mlx, i);
		mlx_mem_free(mlx, LEAVE_MAP_INT);
	}
	if (!check_border(mlx))
		end(mlx, FREE_MAP_INT, BAD_BORDERS_MSG);
}

void		check_map_pasring(char *filename, t_mlx *mlx)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if ((read(fd, NULL, 0)) == -1)
		per();
	if (fd < 0 || (get_next_line(fd, &mlx->str) < 1))
	{
		if (fd < 0)
			per();
		end(mlx, LEAVE_MAP_INT, EMPTY_FILE_MSG);
	}
	parse_file(mlx, fd);
	close(fd);
}
