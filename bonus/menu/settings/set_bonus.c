/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:14:54 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 11:13:36 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline mlx_image_t	*select_image(t_game *game);
static inline t_index		select_index(t_game *game);

#define HD_PNG			"./textures/settings/1280.png"
#define FHD_PNG			"./textures/settings/1920.png"
#define QHD_PNG			"./textures/settings/2560.png"
#define UHD_PNG			"./textures/settings/3840.png"

#define VERY_LOW_PNG	"./textures/settings/1.png"
#define LOW_PNG			"./textures/settings/2.png"
#define MEDIUM_PNG		"./textures/settings/3.png"
#define HIGH_PNG		"./textures/settings/4.png"
#define VERY_HIGH_PNG	"./textures/settings/5.png"

#define EASY_PNG		"./textures/settings/easy.png"
#define NORMAL_PNG		"./textures/settings/normal.png"
#define HARD_PNG		"./textures/settings/hard.png"

#define NO_PNG			"./textures/settings/no.png"
#define YES_PNG			"./textures/settings/yes.png"

/* ************************************************************************** */

extern inline void	set_setting(t_game *game, const int change)
{
	if (game->settings->displayed_setting == RESOLUTION)
		handle_resolution(game, change);
	else if (game->settings->displayed_setting == SENSITIVITY)
		handle_sensitivity(game, change);
	else if (game->settings->displayed_setting == DIFFICULTY)
		handle_difficulty(game, change);
	else if (game->settings->displayed_setting == SUPERTEXTURE)
		handle_supertextures(game);
	save_settings(game);
	if (game->settings->resolution != (size_t)game->resolution[WIDTH])
	{
		game->state(game);
		mlx_terminate(game->window);
		*game->intro_vector = 0;
		*game->intro_prev = 0;
		game->restart = true;
		game->settings->working = false;
		game->music = false;
		play(game);
		stop_sound();
		set_memory(NULL, 0);
		exit(EXIT_SUCCESS);
	}
}

extern inline void	display_data(t_game *game)
{
	static mlx_image_t	*data = NULL;

	if (data)
	{
		mlx_delete_image(game->window, data);
		data = NULL;
	}
	if (game->state == &edit_settings)
	{
		data = select_image(game);
		data->instances->z = game->settings->frame->instances->z + 1;
	}
}

static inline mlx_image_t	*select_image(t_game *game)
{
	const t_path	paths[SETTINGS_COUNT][42] = {
	{HD_PNG, FHD_PNG, QHD_PNG, UHD_PNG},
	{VERY_LOW_PNG, LOW_PNG, MEDIUM_PNG, HIGH_PNG, VERY_HIGH_PNG},
	{EASY_PNG, NORMAL_PNG, HARD_PNG},
	{NO_PNG, YES_PNG}};
	const t_vector	position = {game->resolution[WIDTH] / 2.83,
		game->resolution[HEIGHT] / 1.85};
	t_index			path_index;

	path_index = game->settings->displayed_setting;
	return (set_image(game, paths[path_index][select_index(game)],
		(t_bipoints)position, true));
}

static inline t_index	select_index(t_game *game)
{
	t_index	index;

	index = game->settings->displayed_setting;
	if (index > 3)
		index = 0;
	if (index == RESOLUTION)
	{
		if (game->settings->resolution == FHD)
			return (1);
		if (game->settings->resolution == QHD)
			return (2);
		if (game->settings->resolution == UHD)
			return (3);
		return (0);
	}
	if (index == SENSITIVITY)
		return ((t_index)game->settings->sensitivity - 1);
	if (index == DIFFICULTY)
		return (game->settings->difficulty - 1);
	return (game->sky != NULL);
}
