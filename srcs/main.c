/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:26:23 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/09 17:23:59 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


//mlx
/*
** creates a string with alocated space for all pixels on screen
*/

void	pixel_str(t_mlx *m)
{
	m->img_ptr = mlx_new_image(m->mlx, m->width, m->height);
	m->img_int = (int*)mlx_get_data_addr(
		m->img_ptr, &m->bpp, &m->size_line, &m->endian);
}

/*
** puts all pixles to screen, and then destroys the image
*/

void	create_image(t_mlx *m)
{
	mlx_put_image_to_window(m->mlx, m->win, m->img_ptr, 0, 0);
	// mlx_destroy_image(m->mlx, m->img_ptr);///maybe
	// mlx_clear_window(m->mlx, m->win);//////better?
}





void init(t_mlx *mast){
	mast->height = 1000;
	mast->width = 1000;
	mast->space = 0;
	mast->im_buff_size = mast->height * mast->width;
	mast->mouse_x = mast->width/2;
	mast->mouse_y = mast->height/2;
	mast->theme = 0;
}

void pixel_put(t_mlx *mlx, int x, int y, int color){
	if (x < mlx->wsize && y < mlx->wsize)
		// if (y >= 0 && x >= 0) /////Maybe add back
		{
			int i = (x) + (y * mlx->size_line / 4);
			// mlx->img_int[((y * mlx->size_line/4) + x)] = color;
			mlx->img_int[i] = color;
			mlx->img_int[++i] = color >> 8;
			mlx->img_int[++i] = color >> 16;
		}
}

int verLine(int x, int y1, int y2, int color, t_mlx *m){
	// m->img_int;//pixels

	// if(y2 < y1) {y1 += y2; y2 = y1 - y2; y1 -= y2;} //swap y1 and y2
	// if(y2 < 0 || y1 >= m->height  || x < 0 || x >= m->width) return 0; //no single point of the line is on screen
	// if(y1 < 0) y1 = 0; //clip
	// if(y2 >= m->width) y2 = m->height - 1; //clip

	// Uint32 colorSDL = SDL_MapRGB(scr->format, color.r, color.g, color.b);
	// Uint32* bufp;

	// m->img_int = scr->pixels + y1 * scr->pitch / 4 + x;
	for(int y = y1; y <= y2; y++)
	{
		pixel_put(m, x, y, color);
		// bufp += scr->pitch / 4;
	}
	return 1;
}



t_map			*wolf3d(char *mapname)
{
	t_map				*map;
//	t_player			*player;


	map = read_validate_map(mapname);
	if (!map)
	{
		write(2, MAP_ERROR, sizeof(MAP_ERROR));
		return NULL;
	}
	return map;
//	player = init_player(map);
}

void	start(t_mlx *m, t_map *map){
	double posX = map->start.x, posY = map->start.y;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame


	// screen(512, 384, 0, "Raycaster");
	// while(!done())// Find out when done is not true
	// {
		for(int x = 0; x < m->width; x++)
		{
			// printf("%d\n", x);
			//calculate ray position and direction
			double cameraX = 2 * x / (double)(m->width) - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			//which box of the map we're in
			int mapX = (int)(posX);
			int mapY = (int)(posY);

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = ft_abs(1 / rayDirX);
			double deltaDistY = ft_abs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?

			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}

			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY)
				{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
				}
				else
				{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
				}
				//Check if ray has hit a wall
				if (map->map[mapY][mapX] > '0') hit = 1;
			} 

			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(m->height / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + m->height / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + m->height / 2;
			if(drawEnd >= m->height)drawEnd = m->height - 1;


			//choose wall color
			int color;
			if (map->map[mapY][mapX] == '1')
			{
				color = RGB_Red;
			}

			//give x and y sides different brightness
			if (side == 1) {color = color / 2;}

			//draw the pixels of the stripe as a vertical line
			verLine(x, drawStart, drawEnd, color, m);
		}
}

int		main(int argc, char *argv[])
{
	t_mlx	mast;

	ft_bzero(&mast, sizeof(mast));
	mast.wsize = 1000;
	mast.mlx = mlx_init();
	mast.win = mlx_new_window(mast.mlx, mast.wsize, mast.wsize, "WOLF_3D");

	init(&mast);
	pixel_str(&mast);//new


	ft_printf("Project %s successfully created! \n", argv[0]);
	ft_putchar('\n');

	t_map *map;
	if (argc == 2)
	{
		map = wolf3d(argv[1]);
		printf("MAP GOOD\n");
		start(&mast, map);
	}
	else
	{
		write(2, USAGE, sizeof(USAGE));
	}
	create_image(&mast);//new

	// set_hooks(&mast);
	// // mlx_hook(mast.win, 2, 0, my_key_funct, &mast);

	// // mlx_do_sync(mast.mlx);
	set_hooks(&mast);
	// mlx_hook(mast.win, 2, 0, my_key_funct, &mast);

	// mlx_do_sync(mast.mlx);
	mlx_loop(mast.mlx);

	//Added after
	// mlx_destroy_image(mast.mlx, mast.img_ptr);
	// sleep(3);
	return (0);
}
