/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_animations_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 09:56:21 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 09:14:55 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	ultimate_transformation(t_game *game, int i)
{
	static int	j = -1;

	if (++j < game->resolution[HEIGHT] / 37.5)
	{
		game->sprite[i].texture = game->raycast->bad_guy[j % 2];
		if (j % 2)
			game->sprite[i].transform_deformation = 300 - j * 10;
		else
			game->sprite[i].transform_deformation = 0;
	}
	else
	{
		game->sprite[i].texture = game->raycast->bad_guy[1];
		game->sprite[i].transformed = TRUE;
		game->sprite[i].life = 0;
		game->sprite[i].speed = 0.05;
		game->sprite[i].transform_deformation = 0;
		game->transformation = FALSE;
		j = -1;
	}
}

static inline void	animate_items(t_game *game, int i)
{
	static int	j = -1;

	if (++j < 20)
	{
		game->sprite[i].position[X] += game->sprite[i].eject_direction[X] * 0.1;
		game->sprite[i].position[Y] += game->sprite[i].eject_direction[Y] * 0.1;
	}
	else
	{
		game->sprite[i].collectible_collected = FALSE;
		game->sprite[i].items_given = TRUE;
		game->give_collectible_animation = FALSE;
		j = -1;
	}
}

static inline void	bury_corpse(t_game *game, int i)
{
	game->sprite[i].position[X] = -1000;
	game->sprite[i].position[Y] = -1000;
}

extern inline void	animate_sprites(t_game *game, int i, int *vertical_offset)
{
	static int	j = 0;

	if (game->sprite[i].dead && get_time() - game->sprite[i].death_time > 5000)
		bury_corpse(game, i);
	if (!game->sprite[i].dead)
		make_dat_heresy_move(game, i);
	if (game->sprite[i].hit && !game->sprite[i].dead)
	{
		if (++j % 3)
			game->sprite[i].hit_deformation = 50;
		else
			game->sprite[i].hit_deformation = 0;
	}
	if (game->sprite[i].transformation && !game->sprite[i].transformed
		&& game->brainless_mode)
		ultimate_transformation(game, i);
	if (game->sprite[i].type == ITEMS)
	{
		*vertical_offset = game->i_vertical_offset - game->vertical_offset;
		if (game->sprite[i].collectible_collected
			&& game->give_collectible_animation)
			animate_items(game, i);
	}
	else
		*vertical_offset = game->e_vertical_offset - game->vertical_offset;
}

extern inline void	update_jump(t_game *game)
{
	double	progress;

	if (game->is_jumping)
	{
		progress = (double)game->jump_frame / game->jump_duration;
		game->vertical_offset = (int)(game->jump_height * sin(progress * PI));
		game->jump_frame++;
		if (game->jump_frame >= game->jump_duration)
		{
			game->is_jumping = false;
			game->jump_frame = 0;
			game->vertical_offset = 0;
		}
	}
}
