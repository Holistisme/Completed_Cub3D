/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_texture_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:53:57 by adesille          #+#    #+#             */
/*   Updated: 2024/12/12 16:02:46 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	set_crusader_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->sprite_count)
	{
		if (game->sprite[i].dead)
			continue ;
		if (game->sprite[i].type == BAD_GUY1)
			game->sprite[i].texture = game->raycast->crusader1[0];
		else if (game->sprite[i].type == BAD_GUY2)
			game->sprite[i].texture = game->raycast->crusader2[0];
		else if (game->sprite[i].type == GOOD_GUY)
			game->sprite[i].texture = game->raycast->crusader3[0];
		else if (game->sprite[i].type == ITEMS)
			game->sprite[i].texture = game->raycast->holy_item;
	}
}

static inline void	set_brainless_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->sprite_count)
	{
		if ((game->sprite[i].type == BAD_GUY1
				|| game->sprite[i].type == BAD_GUY2)
			&& !game->sprite[i].transformed)
			game->sprite[i].texture = game->raycast->bad_guy[0];
		else if ((game->sprite[i].type == BAD_GUY1
				|| game->sprite[i].type == BAD_GUY2)
			&& game->sprite[i].transformed)
			game->sprite[i].texture = game->raycast->bad_guy[1];
		else if (game->sprite[i].type == GOOD_GUY)
			game->sprite[i].texture = game->raycast->good_guy[0];
		else if (game->sprite[i].type == ITEMS)
			game->sprite[i].texture = game->raycast->gaspar_item;
	}
}

extern inline void	set_game_textures(t_game *game)
{
	if (game->brainless_mode)
		set_brainless_textures(game);
	else if (game->crusader_mode)
		set_crusader_textures(game);
}
