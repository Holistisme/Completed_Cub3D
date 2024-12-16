/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:35:12 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:28 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	set_default(t_game *game);

/* ************************************************************************** */

extern inline void	save_settings(t_game *game)
{
	FILE		*save;
	const bool	has_sky = game->sky != NULL;

	save = open_file(SETTINGS_BINARY, WRITE_BINARIES);
	if (!save)
		return ;
	if (write_key(save)
		&& write_file(&game->settings->resolution, sizeof(size_t), 1, save)
		&& write_file(&game->settings->sensitivity,
			sizeof(t_sensitivity), 1, save)
		&& write_file(&game->settings->difficulty, sizeof(size_t), 1, save))
		write_file(&has_sky, sizeof(bool), 1, save);
	close_file(save, SETTINGS_BINARY);
}

extern inline void	load_settings(t_game *game)
{
	FILE	*save;

	set_default(game);
	if (binary_file_available(SETTINGS_BINARY))
	{
		save = open_file(SETTINGS_BINARY, READ_BINARIES);
		if (save)
		{
			if (check_key(save, SETTINGS_BINARY))
			{
				if (read_file(&game->settings->resolution,
						sizeof(size_t), 1, save)
					&& read_file(&game->settings->sensitivity,
						sizeof(t_sensitivity), 1, save)
					&& read_file(&game->settings->difficulty,
						sizeof(size_t), 1, save))
					read_file(&game->requested_sky, sizeof(bool), 1, save);
				close_file(save, SETTINGS_BINARY);
			}
		}
	}
}

static inline void	set_default(t_game *game)
{
	game->settings->resolution = HD;
	game->settings->sensitivity = 1;
	game->settings->difficulty = 2;
	game->sky = NULL;
}
