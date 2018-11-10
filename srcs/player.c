/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:56:50 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/09 15:10:51 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_point					east(void)
{
	t_point				e;

	e.y = 0;
	e.x = -1;
	return (e);
}

t_point					north(void)
{
	t_point				n;

	n.y = -1;
	n.x = 0;
	return (n);
}

t_player				*init_player(t_map *map)
{
	t_player			*p1;

	p1 = malloc(sizeof(*p1));
	p1->position = map->start;
	p1->direction = east();
	p1->plane.x = 0;
	p1->plane.y = 0.66;
	return (p1);
}


