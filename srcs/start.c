/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:04:19 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/09 17:20:39 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

t_mlx				*init(void)
{
	t_mlx				*m;

	m = (t_mlx *)malloc(sizeof(*m));
	m->mlx = mlx_init();
	m->size.x = 512;
	m->size.y = 384;
	return (m);
}

int				key_press_hook(int keycode, t_mlx *m)
{
	printf("keycode = %d\n", keycode);
	if (keycode == 53)
		exit(1);
	if (m->mlx)
		printf("-----------------\n");
	return (0);
}

void				set_hooks(t_mlx *m)
{
	mlx_hook(m->win, 2, 0, key_press_hook, m);
}

void			color_pixel(t_mlx *m, int x, int y, int color)
{
	m->img_int[y * m->size_line + x * m->bpp] = color;
	m->img_int[y * m->size_line + x * m->bpp + 1] = color >> 8;
	m->img_int[y * m->size_line + x * m->bpp + 2] = color >> 16;
}

void				draw_vert_line(t_mlx *m, int color, int start_y, int end_y, int x)
{
	m->color = mlx_get_color_value(m->mlx, color);
	printf("%s\n", __func__);
	printf("start_y = %d\nend_y = %d\n", start_y, end_y);
	for (int i = start_y; i < end_y ; i++)
	{
		color_pixel(m, x, i, m->color);
	}
}

void				init_battlefield(t_mlx *m, t_player *p1, t_map *map)
{
	t_point				ray;
	double				camera;
	int					i;

	t_point				side_dist;
	t_point				delta_dist;
	int					map_x;
	int					map_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit = 0;
	int					side;

	m->img_ptr = mlx_new_image(m->mlx, m->size.x, m->size.y);
	m->img_int = mlx_get_data_addr(m->img_ptr, &m->bpp, &m->size_line, &m->endian);
	m->bpp /= 8;

	i = 0;
int	o = 550;
while (i < m->size.x && o--)
{
		camera = 2 * i / (double)m->size.x - 1;
		ray.x = p1->direction.x + p1->plane.x * camera;
		ray.y = p1->direction.y + p1->plane.y * camera;
		map_x = (int)p1->position.x;
		map_y = (int)p1->position.y;
		delta_dist.x = ft_abs(1 / ray.x);
		delta_dist.y = ft_abs(1 / ray.y);
		if (ray.x < 0)
		{
			step_x = -1;
			side_dist.x = (p1->position.x - map_x) * delta_dist.x;
		}
		else
		{
			step_x = 1;
			side_dist.x = (map_x + 1.0 - p1->position.x) * delta_dist.x;
		}
		if (ray.y < 0)
		{
			step_y = -1;
			side_dist.y = (p1->position.y - map_y) * delta_dist.y;
		}
		else
		{
			step_y = 1;
			side_dist.y = (map_y + 1.0 - p1->position.y);
		}
//	}
//	dda
	while (hit == 0)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map_y += step_y;
			side = 1;
		}
		printf("map_y = %d\nmap_x = %d\n", map_y, map_x);
		if (map->map[(int)floor(map_y)][(int)floor(map_x)] == '1')
			hit = 1;
	}

	if (side == 0)
	{
		perp_wall_dist = (map_x - p1->position.x + (1 - step_x) / 2) / ray.x;
	}
	else
	{
		perp_wall_dist = (map_y - p1->position.y + (1 - step_y) / 2) / ray.y;
	}

	int line_height = (int)(m->size.y / perp_wall_dist);
	int	draw_start = -line_height / 2 + m->size.y / 2;
	if (draw_start < 0)
		draw_start = 0;
	int	draw_end = line_height / 2 + m->size.y / 2;
	if (draw_end >= m->size.y)
		draw_end = m->size.y - 1;
	
//	if (side)
//		color = color / 2;
	printf("i = %i\n", i);
	printf("draw_start = %d\ndraw_end = %d\n", draw_start, draw_end);
	draw_vert_line(m, GRAY, draw_start, draw_end, i);
	i += 1;
}
	mlx_put_image_to_window(m->mlx, m->win, m->img_ptr, 0, 0);


}

void				start(t_player *player, t_map *map)
{
	t_mlx				*m;

	while (player)
		break ;
	while (map)
		break  ;
	m = init();
	m->win = mlx_new_window(m->mlx, m->size.x, m->size.y, "wolf3d");
	set_hooks(m);
	ft_print_strings(map->map);
	init_battlefield(m, player, map);
	mlx_loop(m->mlx);
}
