/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_x_pos_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:39:40 by adesille          #+#    #+#             */
/*   Updated: 2024/12/15 12:12:26 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

extern inline int	is_door(t_game *game, uint32_t x, uint32_t y)
{
	if (x > 0 && x < game->scene->width && y > 0 && y < game->scene->height
		&& game->scene->map[y][x] == 'D')
	{
		if (game->doors_cast.is_close[return_door_index(game,
					(t_vector){x, y})])
			return (1);
	}
	return (0);
}

extern inline int	set_closest_bad_guy_position(t_game *game, int i,
		t_double_vector *position)
{
	int	j;

	j = -1;
	(*position)[X] = 1000;
	(*position)[Y] = 1000;
	while (++j < game->sprite_count)
	{
		if (fabs(game->sprite[j].position[X]
				- game->sprite[i].position[X]) < fabs((*position)[X]
			- game->sprite[i].position[X])
			&& fabs(game->sprite[j].position[Y]
				- game->sprite[i].position[Y]) < fabs((*position)[Y]
			- game->sprite[i].position[Y])
			&& (game->sprite[j].type == BAD_GUY1
				|| game->sprite[j].type == BAD_GUY2))
		{
			(*position)[X] = game->sprite[j].position[X];
			(*position)[Y] = game->sprite[j].position[Y];
			return (j);
		}
	}
	return (-1);
}

extern inline int	set_closest_good_guy_position(t_game *game, int i,
		t_double_vector *position)
{
	int	j;

	j = -1;
	(*position)[X] = 1000;
	(*position)[Y] = 1000;
	while (++j < game->sprite_count)
	{
		if (fabs(game->sprite[j].position[X]
				- game->sprite[i].position[X]) < fabs((*position)[X]
			- game->sprite[i].position[X])
			&& fabs(game->sprite[j].position[Y]
				- game->sprite[i].position[Y]) < fabs((*position)[Y]
			- game->sprite[i].position[Y])
			&& game->sprite[j].type == GOOD_GUY)
		{
			(*position)[X] = game->sprite[j].position[X];
			(*position)[Y] = game->sprite[j].position[Y];
			return (j);
		}
	}
	return (-1);
}

extern inline char	*select_death_sound(int n)
{
	if (!n)
		return ("Death_0");
	if (n == 1)
		return ("Death_1");
	if (n == 2)
		return ("Death_2");
	if (n == 3)
		return ("Death_3");
	if (n == 4)
		return ("Death_4");
	if (n == 5)
		return ("Death_5");
	if (n == 6)
		return ("Death_6");
	if (n == 7)
		return ("Death_7");
	if (n == 8)
		return ("Death_8");
	return ("Death_9");
}
