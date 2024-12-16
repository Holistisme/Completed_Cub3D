/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_animations_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:01:14 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 10:54:31 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	give_collectibles(t_game *game)
{
	int	i;

	if (game->player->blue_cord_collected && !game->give_collectible_animation)
	{
		game->player->blue_cord_collected = FALSE;
		i = game->sprite_count + 1;
		while (i >= 0)
		{
			if (game->sprite[i].collectible_collected)
			{
				game->sprite[i].position[X] = game->player->position[X];
				game->sprite[i].position[Y] = game->player->position[Y];
				game->sprite[i].eject_direction[X] = game->player->direction[X];
				game->sprite[i].eject_direction[Y] = game->player->direction[Y];
				game->give_collectible_animation = TRUE;
				return ;
			}
			i--;
		}
	}
}

static inline void	handle_jump(t_game *game)
{
	if (!game->jump_frame)
	{
		game->is_jumping = true;
		game->jump_frame = 0;
	}
}

static inline void	reload(t_game *game)
{
	if (!game->reload_animation && !game->shoot_animation)
	{
		if (game->gun_cheat_code)
			play_sound("gun-reload", 0);
		else
			play_sound("crossbow-reload", 0);
		game->reload_animation = TRUE;
		game->bullets = 0;
	}
}

static inline void	change_mode(t_game *game)
{
	static int	once = FALSE;

	if (!once)
	{
		game->crusader_mode = FALSE;
		game->brainless_mode = TRUE;
		game->intro = TRUE;
		load_brainless_textures(game);
		load_brainless_intro(game);
		game->raycast->start_time = get_time();
		game->start_screen[0]->enabled = TRUE;
		game->start_screen[1]->enabled = TRUE;
		once = TRUE;
	}
}

extern inline void	manage_animations(t_game *game, keys_t key)
{
	if (key == MLX_KEY_SPACE)
		handle_jump(game);
	else if (key == MLX_KEY_G && game->brainless_mode)
		give_collectibles(game);
	else if (key == MLX_KEY_R)
		reload(game);
	else if (key == MLX_KEY_I)
		change_mode(game);
}
