/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:50:48 by adesille          #+#    #+#             */
/*   Updated: 2024/12/14 11:49:26 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	load_gun(t_game *game)
{
	if (!game->gun_cheat_code)
	{
		delete_crossbow_textures(game);
		load_gun_textures(game);
		game->raycast->gun[0]->enabled = TRUE;
		game->gun_cheat_code = TRUE;
		if (game->settings->difficulty == 3)
			game->max_bullets = 1;
		else
			game->max_bullets = 15;
	}
	else
	{
		delete_gun_textures(game);
		load_crossbow_textures(game);
		game->raycast->crossbow[0]->enabled = TRUE;
		game->gun_cheat_code = FALSE;
		if (game->settings->difficulty == 3)
			game->max_bullets = 1;
		else
			game->max_bullets = 5;
	}
}

static inline bool	previous_keys_are_true(bool key_code[6], int target)
{
	int	i;

	i = -1;
	while (++i <= target)
		if (key_code[i] == FALSE)
			return (FALSE);
	return (TRUE);
}

extern inline void	cheat_code_check(t_game *game, keys_t key)
{
	static bool	key_code[6] = {FALSE};
	int			i;

	i = -1;
	if (key == MLX_KEY_KP_0)
		key_code[0] = TRUE;
	else if (key == MLX_KEY_KP_4 && previous_keys_are_true(key_code, 0))
		key_code[1] = TRUE;
	else if (key == MLX_KEY_KP_1 && previous_keys_are_true(key_code, 1))
		key_code[2] = TRUE;
	else if (key == MLX_KEY_KP_8 && previous_keys_are_true(key_code, 2))
		key_code[3] = TRUE;
	else if (key == MLX_KEY_KP_9 && previous_keys_are_true(key_code, 3))
		key_code[4] = TRUE;
	else if (key == MLX_KEY_KP_7 && previous_keys_are_true(key_code, 4))
	{
		key_code[5] = TRUE;
		load_gun(game);
	}
	else
	{
		while (++i < 6)
			key_code[i] = FALSE;
	}
}
