/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:32:21 by adesille          #+#    #+#             */
/*   Updated: 2024/12/12 16:03:00 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_brainless_texture(t_game *game, int i)
{
	static int	x = 0;
	static int	rollback = 0;

	if (!x)
		rollback = 0;
	if (!rollback)
	{
		game->sprite[i].texture = game->raycast->good_guy[++x];
		if (x == 3)
			rollback = 1;
	}
	else
		game->sprite[i].texture = game->raycast->good_guy[x--];
}

void	update_crusader1_texture(t_game *game, int i)
{
	static int	x = 0;
	static int	rollback = 0;

	if (!x)
		rollback = 0;
	if (!rollback)
	{
		game->sprite[i].texture = game->raycast->crusader1[++x];
		if (x == 3)
			rollback = 1;
	}
	else
		game->sprite[i].texture = game->raycast->crusader1[x--];
}

void	update_crusader2_texture(t_game *game, int i)
{
	static int	x = 0;
	static int	rollback = 0;

	if (!x)
		rollback = 0;
	if (!rollback)
	{
		game->sprite[i].texture = game->raycast->crusader2[++x];
		if (x == 3)
			rollback = 1;
	}
	else
		game->sprite[i].texture = game->raycast->crusader2[x--];
}

void	update_crusader3_texture(t_game *game, int i)
{
	static int	x = 0;
	static int	rollback = 0;

	if (!x)
		rollback = 0;
	if (!rollback)
	{
		game->sprite[i].texture = game->raycast->crusader3[++x];
		if (x == 3)
			rollback = 1;
	}
	else
		game->sprite[i].texture = game->raycast->crusader3[x--];
}

void	update_texture(t_game *game, int i, int type)
{
	if (game->brainless_mode && type == GOOD_GUY)
		update_brainless_texture(game, i);
	else if (game->crusader_mode && type == BAD_GUY1)
		update_crusader1_texture(game, i);
	else if (game->crusader_mode && type == BAD_GUY2)
		update_crusader2_texture(game, i);
	else if (game->crusader_mode && type == GOOD_GUY)
		update_crusader3_texture(game, i);
}
