/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:57:29 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:23 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

extern inline void	handle_resolution(t_game *game, const int action)
{
	if (action == +1)
	{
		if (game->settings->resolution < 2560)
			game->settings->resolution += 640;
		else if (game->settings->resolution == 2560)
			game->settings->resolution = 3840;
		else
			game->settings->resolution = 1280;
	}
	else if (action == -1)
	{
		if (game->settings->resolution == 3840)
			game->settings->resolution = 2560;
		else if (game->settings->resolution > 1280)
			game->settings->resolution -= 640;
		else
			game->settings->resolution = 3840;
	}
	else
	{
		game->resolution[WIDTH] = game->settings->resolution;
		game->resolution[HEIGHT] = 2160;
		if (game->settings->resolution <= 2560)
			game->resolution[HEIGHT] = 360 * (game->resolution[WIDTH] / 640);
	}
}

extern inline void	handle_sensitivity(t_game *game, const int action)
{
	game->settings->sensitivity += action;
	if (game->settings->sensitivity < 1.0)
		game->settings->sensitivity = 5.0;
	else if (game->settings->sensitivity > 5.0)
		game->settings->sensitivity = 1.0;
	game->sensitivity = game->settings->sensitivity;
}

extern inline void	handle_difficulty(t_game *game, const int action)
{
	game->settings->difficulty += action;
	if (game->settings->difficulty < 1)
		game->settings->difficulty = 3;
	else if (game->settings->difficulty > 3)
		game->settings->difficulty = 1;
}

extern inline void	handle_supertextures(t_game *game)
{
	static bool	active;

	if (active)
		unset_supertextures(game);
	else
		set_supertextures(game);
	active = !active;
}
