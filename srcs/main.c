/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:26:23 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/07 11:23:46 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	mast->mouse_x = mast->width/2;
	mast->mouse_y = mast->height/2;
	mast->theme = 0;
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

	set_hooks(&mast);
//	 mlx_hook(mast.win, 2, 0, my_key_funct, &mast);

	// mlx_do_sync(mast.mlx);
	mlx_loop(mast.mlx);

	//Added after
	// mlx_destroy_image(mast.mlx, mast.img_ptr);
	sleep(3);
	return (argc);
}
