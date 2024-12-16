/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:32:46 by isb               #+#    #+#             */
/*   Updated: 2024/12/16 10:19:56 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	delete_items(t_game *game, int i, int j)
{
	game->sprite[j].position[X] = -1;
	game->sprite[j].position[Y] = -1;
	game->sprite[i].items_collected++;
	game->sprite[i].collectible_collected = TRUE;
	if (game->crusader_mode)
	{
		game->sprite[i].life = 0;
		game->dark_mode = FALSE;
	}
	if (game->brainless_mode)
	{
		if (game->sprite[j].items_given)
			game->sprite[i].items_given = TRUE;
		if (game->sprite[i].items_collected == 2)
			game->dark_mode = TRUE;
		else
		{
			game->sprite[i].transformation = TRUE;
			game->transformation = TRUE;
		}
	}
}

void	items_management(t_game *game, int i)
{
	int	j;

	j = game->sprite_count - 1;
	while (j > game->sprite_count - game->items_count - 1)
	{
		if (fabs(game->sprite[i].position[Y]
				- game->sprite[j].position[Y]) < 0.25
			&& fabs(game->sprite[i].position[X]
				- game->sprite[j].position[X]) < 0.25
			&& game->sprite[j].type == ITEMS)
			delete_items(game, i, j);
		j--;
	}
}

void	make_it_move(t_game *game, int i, t_vector wall[2],
		t_double_vector position)
{
	if (game->settings->difficulty == 1)
		game->sp_speed = 0.02;
	else
		game->sp_speed = 0.05;
	if (game->sprite[i].is_alive && game->sprite[i].type != ITEMS
		&& game->sprite[i].type != SWORD)
	{
		if (game->sprite[i].position[X] < position[X])
			x_move1(game, i, wall[X], position);
		else
			x_move2(game, i, wall[X], position);
		if (game->sprite[i].position[Y] < position[Y])
			y_move1(game, i, wall[Y], position);
		else
			y_move2(game, i, wall[Y], position);
		if (game->sprite[i].position[X] < position[X])
			x_move1(game, i, wall[X], position);
		else
			x_move2(game, i, wall[X], position);
		collision_buffer_management(game, i, position);
		items_management(game, i);
	}
}

void	make_dat_heresy_move(t_game *game, int i)
{
	static t_vector	wall[2] = {0};
	t_double_vector	position;

	if (game->transformation)
		return ;
	if ((game->sprite[i].type == BAD_GUY1 || game->sprite[i].type == BAD_GUY2)
		&& !game->sprite[i].hit)
	{
		position[X] = game->player->position[X];
		position[Y] = game->player->position[Y];
	}
	else if ((game->sprite[i].type == BAD_GUY1
			|| game->sprite[i].type == BAD_GUY2) && game->sprite[i].hit)
	{
		if (set_closest_good_guy_position(game, i, &position) == -1)
			return ;
	}
	else if (game->sprite[i].type == GOOD_GUY)
	{
		if (set_closest_bad_guy_position(game, i, &position) == -1)
			return ;
	}
	make_it_move(game, i, wall, position);
}
