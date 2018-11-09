/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:26:23 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/09 14:50:58 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			wolf3d(char *mapname)
{
	t_map				*map;
	t_player			*player;


	map = read_validate_map(mapname);
	if (!map)
	{
		write(2, MAP_ERROR, sizeof(MAP_ERROR));
		return ;
	}
//	player = init_player(map);
}

int		main(int argc, char *argv[])
{
	if (argc == 2)
	{
		wolf3d(argv[1]);
	}
	else
	{
		write(2, USAGE, sizeof(USAGE));
	}
	return (0);
}
