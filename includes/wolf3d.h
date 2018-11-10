/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:26:23 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/09 16:24:21 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "../minilibx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>

# define USAGE "wolf3d -> Usage:\n./wolf3d [map]\n"
# define MAP_ERROR "Invalid Map!\n"

//# define BLUE 0x4169e1
//# define RED 0xcd5c5c
//# define YELLOW 0xadff2f
# define GRAY 0x696969
typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_mlx
{
	char			*img_int;
	void			*mlx_ptr;
	void			*img_ptr;
	int				bpp;
	int				size_line;
	int				endian;
	void			*mlx;
	void			*win;
	int				color;
	t_point			size;
	int				space;
//	int				wsize;
	int				mouse_x;
	int				mouse_y;

	int				theme;
}					t_mlx;

typedef struct		s_map
{
	int				height;
	int				width;
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

t_map			*read_validate_map(char *filename);

void			ft_print_strings(char **strings);
char			**strsplit(char *str);
char			*replace_char(char *s, int old, int new_);
int				ptr_count(char **s);
void			start(t_player *player, t_map *map);
t_player		*init_player(t_map *map);
#endif 
