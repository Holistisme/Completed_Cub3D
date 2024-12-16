/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_aiming_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:24:01 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:05:24 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline t_index	aim_a_choice(const t_game *game,
							const t_vector position);
static inline void	aim_nothing(const t_menu *menu);

/* ************************************************************************** */

extern inline void	aim_menu(t_game *game)
{
	static t_index	last_button = UNSET;
	t_index			current_button;
	t_vector		position;

	mlx_get_mouse_pos(game->window, &position[X], &position[Y]);
	if (game->state == &display_main_menu || game->state == &pause_game)
	{
		current_button = aim_a_choice(game, position);
		if (current_button == UNSET)
			aim_nothing(game->menu);
		else if (current_button != last_button)
			play_sound("choice", CHOICE);
		last_button = current_button;
	}
}

static inline t_index	aim_a_choice(const t_game *game,
							const t_vector position)
{
	t_index	button;

	button = 0;
	while (button <= EXIT_GAME)
	{
		if (selected_image((t_double_vector){position[X], position[Y]},
			game->menu->button, button) >= NEW_CAMPAIGN
			&& !(game->state == &display_main_menu
				&& button == CONTINUE_CAMPAIGN && game->menu->blocked_banner))
		{
			set_image_visibility(&game->menu->button->instances[button], false);
			set_image_visibility(&game->menu->selected_button
				->instances[button], true);
			return (button);
		}
		++button;
	}
	return (UNSET);
}

static inline void	aim_nothing(const t_menu *menu)
{
	t_index	button;

	button = 0;
	while (button <= EXIT_GAME)
	{
		set_image_visibility(&menu->button->instances[button], true);
		set_image_visibility(&menu->selected_button->instances[button], false);
		++button;
	}
}
