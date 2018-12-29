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


void free_2d(char **str)
{
  int i;
  
  i = -1;
  while (str[++i])
    free(str[i]);
  free(str[i]);
  free(str);
}

void free_2d_int(int **arr, int size)
{
  int i;
  
  i = -1;
  while (++i < size)
    free(arr[i]);
  free(arr);
}

int				icon_close(void)
{
	exit(1);
	return (0);
}

void		per(void)
{
	perror("\033[31mFile opening error");
	exit(1);
}