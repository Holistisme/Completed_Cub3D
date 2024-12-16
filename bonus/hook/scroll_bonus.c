/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:52:05 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:05:36 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	scroll_settings(t_game *game, double ydelta);

/* ************************************************************************** */

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_game			*game;
	static bool		working;

	(void)xdelta;
	game = (t_game *)param;
	if (game->state == &master_legacies && !working)
	{
		working = true;
		if (ydelta > 0)
			display_achievement(game->legacies, -1);
		else
			display_achievement(game->legacies, +1);
		working = false;
	}
	else if (game->state == &edit_settings
		&& !game->settings->animation)
		scroll_settings(game, ydelta);
}

static inline void	scroll_settings(t_game *game, double ydelta)
{
	if (!game->settings->working)
	{
		game->settings->working = true;
		if (ydelta > 0)
			set_setting(game, +1);
		else
			set_setting(game, -1);
		game->settings->working = false;
	}
}
