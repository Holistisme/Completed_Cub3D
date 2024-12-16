/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:06:19 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/15 12:23:50 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	ingame_key(mlx_key_data_t keydata, t_game *game);

/* ************************************************************************** */

static inline void	manage_minimap(t_game *game, keys_t key)
{
	if (key == MLX_KEY_EQUAL || key == MLX_KEY_MINUS)
		return (manage_compass_zoom(game, key));
	else if (key == MLX_KEY_KP_SUBTRACT || key == MLX_KEY_KP_ADD)
		return (manage_zoom(game, key));
	else if (key == MLX_KEY_KP_2 || key == MLX_KEY_KP_3 || key == MLX_KEY_KP_5
		|| key == MLX_KEY_KP_6)
		return (change_corner(game, which_corner(key)));
	else if (key == MLX_KEY_U)
		game->set_uni_texture = !game->set_uni_texture;
	else if (key == MLX_KEY_O)
		game->set_disco_mode = !game->set_disco_mode;
}

static inline void	key_hook_utils(t_game *game, keys_t key)
{
	if (game->main_menu == &pause_game && key == MLX_KEY_TAB)
	{
		while (game->state != &pause_game)
			game->state(game);
		game->state(game);
	}
	else if (game->state == &edit_settings && !game->settings->animation)
	{
		if (key == MLX_KEY_DOWN)
			change_setting(game, 2);
		else if (key == MLX_KEY_RIGHT)
			change_setting(game, 1);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action != MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_SPACE
			&& (game->state == &introduce || game->state == &display_studio))
			skip_chapter(game, SET);
		else if (keydata.key == MLX_KEY_ESCAPE)
		{
			manage_mlx(NULL);
			stop_sound();
			set_memory(NULL, 0);
			exit(EXIT_SUCCESS);
		}
		else if (game->state == &raycast)
			ingame_key(keydata, game);
		else
			key_hook_utils(game, keydata.key);
	}
}

static inline void	ingame_key(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_TAB)
	{
		play_ambience(game, UNSET);
		pause_game(game);
	}
	else if (keydata.key == MLX_KEY_SPACE || keydata.key == MLX_KEY_G
		|| keydata.key == MLX_KEY_R || keydata.key == MLX_KEY_I)
		manage_animations(game, keydata.key);
	else if (keydata.key == MLX_KEY_KP_0 || keydata.key == MLX_KEY_KP_1
		|| keydata.key == MLX_KEY_KP_4 || keydata.key == MLX_KEY_KP_9
		|| keydata.key == MLX_KEY_KP_8 || keydata.key == MLX_KEY_KP_7)
		return (cheat_code_check(game, keydata.key));
	else
		manage_minimap(game, keydata.key);
}
