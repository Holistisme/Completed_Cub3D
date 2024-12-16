/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:39:12 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 11:13:31 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	press_play_button(t_game *game);
static inline void	press_reload_button(t_game *game);
static inline void	press_return_button(t_game *game);

#define BLOCKED_BUTTON_PNG		"./textures/menu/blocked_button.png"

/* ************************************************************************** */

void	click_button(t_game *game, const t_index button)
{
	t_index	index;

	index = 0;
	while (index < 5)
	{
		set_image_visibility(&game->menu->button->instances[index], true);
		set_image_visibility(&game->menu->selected_button->instances[index++],
			false);
	}
	if (button == 0)
		press_play_button(game);
	else if (button == 1)
		press_reload_button(game);
	else if (button == 2)
		master_legacies(game);
	else if (button == 3)
		edit_settings(game);
	else if (button == 4)
		press_return_button(game);
}

static inline void	press_play_button(t_game *game)
{
	game->music = false;
	if (game->state == &display_main_menu)
	{
		change_textures(game, false);
		display_main_menu(game);
		skip_chapter(game, GET);
		game->state = &introduce;
		introduce(game);
		init_sprites(game, -1);
		draw_doors(game);
	}
	else
		game->state(game);
}

static inline void	press_reload_button(t_game *game)
{
	const t_vector	position = {game->menu->button->instances[1].x,
		game->menu->button->instances[1].y};

	if (game->state == &pause_game)
		save_game(game);
	else
	{
		if (!load_game(game))
		{
			game->menu->blocked_banner = set_image(game, BLOCKED_BUTTON_PNG,
					(t_bipoints)position, true);
			game->menu->blocked_banner->instances->z
				= game->menu->texts[1]->instances->z - 1;
			game->menu->button->instances[1].enabled = false;
			game->menu->selected_button->instances[1].enabled = false;
		}
		else
			game->state(game);
	}
}

static inline void	press_return_button(t_game *game)
{
	game->music = false;
	if (game->state == &pause_game)
	{
		game->state(game);
		display_main_menu(game);
	}
	else
		mlx_close_window(game->window);
}
