/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:26:23 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/09 14:30:38 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "../minilibx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>

typedef struct		s_mlx
{
	int				*img_int;
	void			*mlx_ptr;
	void			*img_ptr;
	int				bpp;
	int				size_line;
	int				endian;
	void			*mlx;
	void			*win;

	int				space;
	int				wsize;
	int				height;
	int				width;
	int				mouse_x;
	int				mouse_y;

	int				theme;
}					t_mlx;

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_map
{
	t_point			size;
	char			**map;
	t_point			start;
}					t_map;

typedef struct		s_player
{
	t_point			position;
	t_point			direction;
	t_point			plane;
}					t_player;

typedef	struct		s_thread
{
	t_mlx	*m;
	int		count;
}					t_thread;


void	create_image(t_mlx *m);
void	draw(t_mlx *master, int y1, int x1, int color);
void	pixel_str(t_mlx *m);
void	set_hooks(t_mlx *m);
void	move_forward(t_mlx *v);
void	move_back(t_mlx *v);
void	move_right(t_mlx *v);
void	move_left(t_mlx *v);
int		key_press_hook(int keycode, t_mlx *mast);
int		mouse_motion_hook(int x, int y, t_mlx *m);
int		mouse_press_hook(int code, int x, int y, t_mlx *m);
void	pixel_put(t_mlx *mlx, int x, int y, int color);

#endif 
