/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:31:39 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 10:06:44 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * Transforms the sprite's position from world coordinates to camera coordinates.
 * - Calculates the relative position of the sprite to the player.
 * - Computes the inverse determinant for the transformation.
 * - Transforms the sprite's X and Y coordinates using 
 * 	 the player's direction and plane vectors.
*/
static inline void	transform_sprite_position(t_game *game, t_sprite *sprite,
		double *inv_det, t_double_vector *transform)
{
	double	sprite_x;
	double	sprite_y;

	sprite_x = sprite->position[X] - game->player->position[X];
	sprite_y = sprite->position[Y] - game->player->position[Y];
	*inv_det = 1.0 / (game->player->plane[X] * game->player->direction[Y]
			- game->player->direction[X] * game->player->plane[Y]);
	(*transform)[X] = *inv_det * (game->player->direction[Y] * sprite_x
			- game->player->direction[X] * sprite_y);
	(*transform)[Y] = *inv_det * (-game->player->plane[Y] * sprite_x
			+ game->player->plane[X] * sprite_y);
}

static void	sort_sprites(t_game *game)
{
	t_sprite	temp;
	int			i;
	int			j;

	i = -1;
	while (++i < game->sprite_count)
	{
		j = i;
		while (++j < game->sprite_count)
		{
			if ((pow(game->player->position[X] - game->sprite[i].position[X], 2)
					+ pow(game->player->position[Y]
						- game->sprite[i].position[Y],
						2)) < (pow(game->player->position[X]
						- game->sprite[j].position[X], 2)
					+ pow(game->player->position[Y]
						- game->sprite[j].position[Y], 2)))
			{
				temp = game->sprite[i];
				game->sprite[i] = game->sprite[j];
				game->sprite[j] = temp;
			}
		}
	}
}

/**
 * Calculates the screen position and dimensions of a sprite.
 * - Transforms the sprite's position from world coordinates
 * 	 to camera coordinates.
 * - Calculates the sprite's screen X-coordinate.
 * - Determines the sprite's height and width on the screen.
 * - Calculates the starting and ending X and Y coordinates
 * 	 for drawing the sprite.
*/
void	do_sprites_calculations(t_game *game, int i, t_sprite_cast *e,
		int vertical_offset)
{
	transform_sprite_position(game, &game->sprite[i], &(*e).inv_det,
		&(*e).transform);
	(*e).sprite_screen_x = (int)((game->resolution[WIDTH] / 2)
			* (1 + (*e).transform[X] / (*e).transform[Y]));
	(*e).sprite_height = abs((int)(game->resolution[HEIGHT]
				/ (*e).transform[Y]));
	(*e).sprite_width = (*e).sprite_height;
	(*e).draw_start_x = (*e).sprite_screen_x - (*e).sprite_width / 2;
	(*e).draw_end_x = (*e).sprite_screen_x + (*e).sprite_width / 2;
	(*e).draw_start_y = game->resolution[HEIGHT] / 2 - (*e).sprite_height / 2
		- vertical_offset;
	(*e).draw_end_y = game->resolution[HEIGHT] / 2 + (*e).sprite_height / 2
		- vertical_offset;
}

void	cast_sprites(t_game *game)
{
	t_sprite_cast	e;
	int				i;
	int				vertical_offset;

	i = -1;
	sort_sprites(game);
	if (game->brainless_mode)
		update_jump_enemy(game);
	update_floating_items(game);
	while (++i < game->sprite_count)
	{
		animate_sprites(game, i, &vertical_offset);
		do_sprites_calculations(game, i, &e, vertical_offset);
		if (game->sprite[i].collision_buffer && !game->sprite[i].dead)
			update_texture(game, i, game->sprite[i].type);
		e.x = e.draw_start_x - 1;
		draw_sprites(game, e, &game->sprite[i]);
	}
}
