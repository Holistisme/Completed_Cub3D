/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:21:24 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:25 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

#define FRAME				"./textures/settings/frame.png"
#define OPENING_PNG			"./textures/settings/opening.png"
#define RESOLUTION_PNG		"./textures/settings/resolution.png"
#define SENSITIVITY_PNG		"./textures/settings/sensitivity.png"
#define DIFFICULTIES_PNG	"./textures/settings/difficulties.png"
#define SUPERTEXTURES_PNG	"./textures/settings/supertextures.png"
#define BUTTON				"./textures/settings/button.png"

static void	open_settings(t_game *game);
static void	close_settings(t_game *game);

/* ************************************************************************** */

void	edit_settings(t_game *game)
{
	if (game->state == &edit_settings)
		close_settings(game);
	else
		open_settings(game);
}

static void	open_settings(t_game *game)
{
	const t_path	image[SETTINGS_COUNT]
		= {RESOLUTION_PNG, SENSITIVITY_PNG, DIFFICULTIES_PNG,
		SUPERTEXTURES_PNG};
	const t_vector	position
		= {game->resolution[WIDTH] / 4, game->resolution[HEIGHT] / 12};
	t_index			index;

	index = SETTINGS_COUNT;
	while (--index >= 0)
		game->settings->image[index]
			= set_image(game, image[index], (t_bipoints)position, true);
	game->settings->frame = set_image(game, FRAME, (t_vector){0}, true);
	game->settings->slide[0] = NULL;
	game->settings->slide[1] = NULL;
	game->state = &edit_settings;
}

static void	close_settings(t_game *game)
{
	t_index	index;

	index = 0;
	while (index < SETTINGS_COUNT)
		mlx_delete_image(game->window, game->settings->image[index++]);
	mlx_delete_image(game->window, game->settings->frame);
	if (game->settings->slide[0])
		mlx_delete_image(game->window, game->settings->slide[0]);
	if (game->settings->slide[1])
		mlx_delete_image(game->window, game->settings->slide[1]);
	game->settings->animation = false;
	game->state = game->main_menu;
	display_data(game);
	game->settings->displayed_setting = 0;
}

#define CURRENT	0
#define UNDER	1
#define ON		2

static void	turn_z(t_game *game)
{
	t_index		index;
	const int	base = game->settings->image[SETTINGS_COUNT - 1]->instances->z;

	index = SETTINGS_COUNT - 1;
	while (index >= 1)
	{
		game->settings->image[index]->instances->z
			= game->settings->image[index - 1]->instances->z;
		--index;
	}
	game->settings->image[index]->instances->z = base;
}

void	change_setting(t_game *game, t_index direction)
{
	game->settings->animation = true;
	animate_setting(game,
		game->settings->image[game->settings->displayed_setting], direction);
	if (direction)
	{
		game->state = NULL;
		display_data(game);
		game->state = &edit_settings;
		turn_z(game);
		++game->settings->displayed_setting;
		if (game->settings->displayed_setting < 0)
			game->settings->displayed_setting = SETTINGS_COUNT - 1;
		else if (game->settings->displayed_setting > SETTINGS_COUNT - 1)
			game->settings->displayed_setting = 0;
	}
}
