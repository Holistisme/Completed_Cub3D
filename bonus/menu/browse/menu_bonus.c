/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:08:06 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:40:40 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	set_buttons(t_game *game);
static inline void	set_first_button(t_game *game, const double menu);
static inline void	set_next_buttons(t_game *game, t_index button, double menu);
static inline void	set_texts(t_game *game, t_index index);

#define PAUSE					1.7
#define MAIN					2

#define NEW_CAMPAIGN_PNG		"./textures/menu/new_campaign.png"
#define RESUME_BATTLE_PNG		"./textures/menu/resume_battle.png"
#define CONTINUE_CAMPAIGN_PNG	"./textures/menu/continue_campaign.png"
#define SAVE_PROGRESS_PNG		"./textures/menu/save_progress.png"
#define MASTER_LEGACIES_PNG		"./textures/menu/master_legacies.png"
#define EDIT_SETTINGS_PNG		"./textures/menu/edit_settings.png"
#define EXIT_GAME_PNG			"./textures/menu/exit_game.png"
#define ABANDON_BATTLE_PNG		"./textures/menu/abandon_battle.png"

#define BUTTON_PNG				"./textures/menu/button.png"
#define SELECTED_BUTTON_PNG		"./textures/menu/selected_button.png"
#define BLOCKED_BUTTON_PNG		"./textures/menu/blocked_button.png"

/* ************************************************************************** */

void	open_menu(t_game *game)
{
	stop_sound();
	set_buttons(game);
	mlx_set_cursor_mode(game->window, MLX_MOUSE_NORMAL);
	game->legacies->ingame_start = 0;
}

static inline void	set_buttons(t_game *game)
{
	double	index;
	double	menu;

	menu = MAIN;
	if (game->state == &raycast)
		menu = PAUSE;
	index = 0.6;
	while (index < 5)
	{
		if (index == 0.6)
			set_first_button(game, menu);
		else
			set_next_buttons(game, index, menu);
		set_texts(game, index++);
	}
}

static inline void	set_first_button(t_game *game, const double menu)
{
	const int32_t	button_offset = (game->resolution[WIDTH] / 6) * 0.6;

	game->menu->button = set_image(game, BUTTON_PNG,
			(t_vector){button_offset, game->resolution[HEIGHT] / menu}, true);
	game->menu->selected_button = set_image(game, SELECTED_BUTTON_PNG,
			(t_vector){button_offset, game->resolution[HEIGHT] / menu}, true);
}

static inline void	set_next_buttons(t_game *game,
						const t_index button, const double menu)
{
	const t_vector	position = {(game->resolution[WIDTH] / 6)
		* ((double)button + 0.6), game->resolution[HEIGHT] / menu};

	display_image(game->window, game->menu->button, (t_bipoints)position);
	display_image(game->window,
		game->menu->selected_button, (t_bipoints)position);
	if (menu == MAIN && button == 1 && (game->menu->blocked_banner
			|| !binary_file_available(CAMPAIGN_BINARY)))
	{
		game->menu->blocked_banner
			= set_image(game, BLOCKED_BUTTON_PNG, (t_bipoints)position, true);
		game->menu->button->instances[button].enabled = false;
		game->menu->selected_button->instances[button].enabled = false;
	}
}

static inline void	set_texts(t_game *game, const t_index index)
{
	t_path			texts[5];
	const t_vector	position = {game->menu->button->instances[index].x
		+ (game->menu->button->width / 2),
		game->menu->button->instances[index].y
		+ (game->menu->button->height / 3.25)};

	texts[0] = NEW_CAMPAIGN_PNG;
	texts[1] = CONTINUE_CAMPAIGN_PNG;
	texts[2] = MASTER_LEGACIES_PNG;
	texts[3] = EDIT_SETTINGS_PNG;
	texts[4] = EXIT_GAME_PNG;
	if (game->state == &raycast)
	{
		texts[0] = CONTINUE_CAMPAIGN_PNG;
		texts[1] = SAVE_PROGRESS_PNG;
		texts[4] = ABANDON_BATTLE_PNG;
	}
	game->menu->selected_button->instances[index].enabled = false;
	game->menu->texts[index]
		= set_image(game, texts[index], (t_bipoints)position, true);
	game->menu->texts[index]->instances->x
		-= game->menu->texts[index]->width / 2;
}
