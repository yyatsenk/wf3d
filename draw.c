/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:22:54 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/03/27 18:22:55 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			window_start(t_map_info *map_info)
{
	map_info->mlx_ptr = mlx_init();
	map_info->win_ptr = mlx_new_window(map_info->mlx_ptr, HEIGHT, WIDTH, "FDF");
}

static void		draw_horizont(t_map_info *m_i, t_dot *dot)
{
	t_cc		c;
	t_dot		*dot_copy;

	dot_copy = dot;
	while (dot)
	{
		c.x0 = dot->x_min;
		c.y0 = dot->y_min;
		if (dot->next && dot->y == dot->next->y)
		{
			c.x1 = dot->next->x_min;
			c.y1 = dot->next->y_min;
		}
		else
		{
			dot = dot->next;
			continue;
		}
		if (dot->altitude)
			make_line(m_i, c, 0, dot);
		else
			make_line(m_i, c, 0, dot->next);
		dot = dot->next;
	}
	dot = dot_copy;
}

static void		draw_vertical(t_map_info *m_i, t_dot *dot)
{
	t_cc		c;
	t_dot		*dot_copy;

	while (dot)
	{
		c.x0 = dot->x_min;
		c.y0 = dot->y_min;
		dot_copy = dot->next;
		while (dot_copy && dot_copy->x != dot->x)
			dot_copy = dot_copy->next;
		if (!dot_copy)
			break ;
		c.x1 = dot_copy->x_min;
		c.y1 = dot_copy->y_min;
		if (dot->altitude)
			make_line(m_i, c, 0, dot);
		else
			make_line(m_i, c, 0, dot_copy);
		dot = dot->next;
	}
}

void			draw_map(t_map_info *map_info, t_dot *dot)
{
	draw_horizont(map_info, dot);
	draw_vertical(map_info, dot);
}
