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

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


    
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int			key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		exit(1);
    
    if (keycode == 65362)
    {
      printf("hahahahahha\n");
      if(worldMap[(int)(mlx->pos_x + mlx->dir_x * mlx->moveSpeed)][(int)(mlx->pos_y)] == 0) mlx->pos_x += mlx->dir_x * mlx->moveSpeed;
      if(worldMap[(int)(mlx->pos_x)][(int)(mlx->pos_y + mlx->dir_y * mlx->moveSpeed)] == 0) mlx->pos_y += mlx->dir_y * mlx->moveSpeed;
    }
    //move backwards if no wall behind you
    if (keycode == 65364)
    {
      if(worldMap[(int)(mlx->pos_x - mlx->dir_x * mlx->moveSpeed)][(int)(mlx->pos_y)] == 0) mlx->pos_x -= mlx->dir_x * mlx->moveSpeed;
      if(worldMap[(int)(mlx->pos_x)][(int)(mlx->pos_y - mlx->dir_y * mlx->moveSpeed)] == 0) mlx->pos_y -= mlx->dir_y * mlx->moveSpeed;
    }
    //rotate to the right
    if (keycode == 65363)
    {
      //both camera direction and camera plane must be rotated
      double olddir_x = mlx->dir_x;
      mlx->dir_x = mlx->dir_x * cos(-mlx->rotSpeed) - mlx->dir_y * sin(-mlx->rotSpeed);
      mlx->dir_y = olddir_x * sin(-mlx->rotSpeed) + mlx->dir_y * cos(-mlx->rotSpeed);
      double oldplain_x = mlx->plain_x;
      mlx->plain_x = mlx->plain_x * cos(-mlx->rotSpeed) - mlx->plain_y * sin(-mlx->rotSpeed);
      mlx->plain_y = oldplain_x * sin(-mlx->rotSpeed) + mlx->plain_y * cos(-mlx->rotSpeed);
    }
    //rotate to the left
    if (keycode == 65361)
    {
      //both camera direction and camera plane must be rotated
      double olddir_x = mlx->dir_x;
      mlx->dir_x = mlx->dir_x * cos(mlx->rotSpeed) - mlx->dir_y * sin(mlx->rotSpeed);
      mlx->dir_y = olddir_x * sin(mlx->rotSpeed) + mlx->dir_y * cos(mlx->rotSpeed);
      double oldplain_x = mlx->plain_x;
      mlx->plain_x = mlx->plain_x * cos(mlx->rotSpeed) - mlx->plain_y * sin(mlx->rotSpeed);
      mlx->plain_y = oldplain_x * sin(mlx->rotSpeed) + mlx->plain_y * cos(mlx->rotSpeed);
    }
	return (0);
}

void		mlx_struct_init(t_mlx *mlx, char *name)
{
	mlx->name = name;
	
//	mlx->iter = 100;
	
    mlx->pos_x = 22;
    mlx->pos_y = 12; 
    mlx->dir_x = -1;
    mlx->dir_y = 0; 
    mlx->plain_x = 0;
    mlx->plain_y = 1;
    mlx->time = 0; 
    mlx->oldtime = 0; 
    mlx->c1 = 0x002570;
	mlx->c2 = 0x00704a;
	mlx->c3 = 0x6a6d03;
	mlx->c4 = 0x6d026b;
	mlx->c_s = 0x0090ff;
  mlx->c_g = 0x664848;
}
/*
void draw_line(t_mlx *mlx, int x)
{

    int y = 0;
  if (mlx->side == 0) mlx->perpWallDist = (mlx->mapX - mlx->pos_x + (1 - mlx->stepX) / 2) / mlx->rayDirX;
      else           mlx->perpWallDist = (mlx->mapY - mlx->pos_x + (1 - mlx->stepY) / 2) / mlx->rayDirY;

      //Calculate height of line to draw on screen
      mlx->lineHeight = (int)(HEIGHT / mlx->perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      mlx->drawStart = -(mlx->lineHeight) / 2 + HEIGHT / 2;
      if(mlx->drawStart < 0)mlx->drawStart = 0;
      mlx->drawEnd = mlx->lineHeight / 2 + HEIGHT / 2;
      if(mlx->drawEnd >= HEIGHT)mlx->drawEnd = HEIGHT - 1;

      //choose wall color
      switch(worldMap[mlx->mapX][mlx->mapY])
      {
        case 1:  mlx->color = 0x4286f4;  break; //red
        case 2:  mlx->color = 0x41f447;  break; //green
        case 3:  mlx->color = 0x40bced;   break; //blue
        case 4:  mlx->color = 0xf7f9f9;  break; //white
        default: mlx->color = 0xf2f91b; break; //yellow
      }
      mlx->cord.x0 = x;
      mlx->cord.x1 = x;
      mlx->cord.y0 = mlx->drawStart;
      mlx->cord.y1 = mlx->drawEnd;


      //give x and y sides different brightness
      if (mlx->side == 1) {mlx->color = mlx->color / 2;}

  while (y < mlx->drawStart)
  {
    mlx->data[WIDTH * y + x] = mlx->color;
    y++;
  }
  y = 0;
  while (y < mlx->drawEnd && y < HEIGHT)
  {
    mlx->data[WIDTH * y + x] = mlx->color;
    y++;
  }
  y = 0;
  while (y < HEIGHT)
  {
    mlx->data[WIDTH * y + x] = mlx->color;
    y++;
  }
}*/


//vkazbodi draw


unsigned int	wall(t_mlx *mlx)
{
	if ((mlx->step.x == -1 && mlx->step.y == -1) ||
		(mlx->step.x == 1 && mlx->step.y == -1))
		return (mlx->c1);
	if ((mlx->step.x == -1 && mlx->step.y == 1) ||
		(mlx->step.x == 1 && mlx->step.y == 1))
		return (mlx->c2);
	return (0);
}

void			put_pxl(t_mlx *mlx, int x, int y, unsigned int c)
{
	int		i;

	if (c != mlx->c_s && c != mlx->c_g)
	{
		if (mlx->side == 1)
			c = wall(mlx);
		else if ((mlx->step.x == -1 && mlx->step.y == -1) ||
			(mlx->step.x == -1 && mlx->step.y == 1))
			c = mlx->c3;
		else
			c = mlx->c4;
	}
	i = (y * WIDTH + x);
	if (i <= WIDTH * HEIGHT)
		mlx->data[i] = c;
}

void			draw_line(t_mlx *mlx, int x)
{
	int				y;
	unsigned int	c;

	   mlx->lineHeight = (int)(HEIGHT / mlx->perpWallDist);
      mlx->drawStart = -(mlx->lineHeight) / 2 + HEIGHT / 2;
      if(mlx->drawStart < 0)mlx->drawStart = 0;
      mlx->drawEnd = mlx->lineHeight / 2 + HEIGHT / 2;
      if(mlx->drawEnd >= HEIGHT)mlx->drawEnd = HEIGHT - 1;
	c = 0x111111;
	y = -1;
	while (++y < mlx->drawStart)
		put_pxl(mlx, x, y, mlx->c_s);
	y -= 1;
	while (y++ <= mlx->drawEnd && y < HEIGHT)
		put_pxl(mlx, x, y, c);
	y -= 1;
	while (y++ <= HEIGHT)
		put_pxl(mlx, x, y, mlx->c_g);
}


void draw_it_for_me(t_mlx *mlx)
{
  for(int x = 0; x < WIDTH; x++)
    {
      //printf ("helooooooooo!!   %d\n", keycode);
      //calculate ray position and direction
     mlx->cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
      mlx->rayDirX = mlx->dir_x + mlx->plain_x * mlx->cameraX;
      mlx->rayDirY = mlx->dir_y + mlx->plain_y * mlx->cameraX;
      //which box of the map we're in
      mlx->mapX = (int)mlx->pos_x;
      mlx->mapY = (int)mlx->pos_y;

      //length of ray from current position to next x or y-side
       //length of ray from one x or y-side to next x or y-side
      mlx->deltaDistX = sqrt(1 + pow(mlx->rayDirY, 2) / pow(mlx->rayDirX, 2));
      mlx->deltaDistY = sqrt(1 + pow(mlx->rayDirX, 2) / pow(mlx->rayDirY, 2));

      //what direction to step in x or y-direction (either +1 or -1)
      

      mlx->hit = 0; //was there a wall hit?
       //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      
      if (mlx->rayDirX < 0)
      {
        mlx->stepX = -1;
        mlx->sideDistX = (mlx->pos_x - mlx->mapX) * mlx->deltaDistX;
      }
      else
      {
        mlx->stepX = 1;
        mlx->sideDistX = (mlx->mapX + 1 - mlx->pos_x) * mlx->deltaDistX;
      }
      if (mlx->rayDirY < 0)
      {
        mlx->stepY = -1;
        mlx->sideDistY = (mlx->pos_y - mlx->mapY) * mlx->deltaDistY;
      }
      else
      {
        mlx->stepY = 1;
        mlx->sideDistY = (mlx->mapY + 1 - mlx->pos_y) * mlx->deltaDistY;
      }
      //perform DDA
      while (mlx->hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (mlx->sideDistX < mlx->sideDistY)
        {
          mlx->sideDistX += mlx->deltaDistX;
          mlx->mapX += mlx->stepX;
          mlx->side = 0;
        }
        else
        {
          mlx->sideDistY += mlx->deltaDistY;
          mlx->mapY += mlx->stepY;
          mlx->side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[mlx->mapX][mlx->mapY] > 0)
        {
          mlx->hit = 1;
          if (mlx->side == 0) 
            mlx->perpWallDist = (mlx->mapX - mlx->pos_x + (1 - mlx->stepX) / 2) / mlx->rayDirX;
          else          
            mlx->perpWallDist = (mlx->mapY - mlx->pos_y + (1 - mlx->stepY) / 2) / mlx->rayDirY;

        }
      }
      mlx->step.x =  mlx->stepX;
      mlx->step.y =  mlx->stepY;
      draw_line(mlx, x);
    
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image_ptr, 0,0);
}
int do_all_stuff(t_mlx *mlx)
{

    //draw_it_for_me(mlx);
    mlx->oldtime = mlx->time;
    printf("%f",(1.0 / mlx->frameTime)); //FPS counter
    draw_it_for_me(mlx);
    printf("time: %f  oldtime: %f  frametime: %f\n", mlx->time, mlx->oldtime, mlx->frameTime);
    //speed modifiers
    mlx->moveSpeed = 0.4;//mlx->frameTime * 2.0; //the constant value is in squares/second
    mlx->rotSpeed = 0.4;//mlx->frameTime * 1.5; //the constant value is in radians/second
}

int main(int argv, char **argc)
{
  t_mlx	mlx;

	if (argv == 2)
	{
		mlx_struct_init(&mlx, argc[1]);
		mlx.mlx_ptr = mlx_init();
		mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Wolf3d");
		mlx.image_ptr = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
		mlx.data = (int*)mlx_get_data_addr(mlx.image_ptr, &(mlx.bpp),\
		&(mlx.size_line), &(mlx.end));
        //do_all_stuff(&mlx);
		  //mlx_hook(mlx.win_ptr, 4, 0, zoom, mlx);
	    //mlx_hook(mlx.win_ptr, 6, 0, mouse, mlx);
      mlx_hook(mlx.win_ptr, 2, 5, key_hook, &mlx);
      mlx_loop_hook(mlx.mlx_ptr, do_all_stuff, &mlx);
	    //mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	    mlx_loop(mlx.mlx_ptr);
	}
	else
		write(1, ERROR_MSG, ft_strlen(ERROR_MSG));
	return (0);
}
