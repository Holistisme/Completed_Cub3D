/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_corner_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:55:27 by isb               #+#    #+#             */
/*   Updated: 2024/12/13 09:48:32 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

extern inline int	which_corner(keys_t key)
{
	if (key == MLX_KEY_KP_2 || key == DOWN_LEFT)
		return (DOWN_LEFT);
	else if (key == MLX_KEY_KP_3 || key == DOWN_RIGHT)
		return (DOWN_RIGHT);
	else if (key == MLX_KEY_KP_5 || key == UP_LEFT)
		return (UP_LEFT);
	return (UP_RIGHT);
}

static inline void	down_right(t_game *game)
{
	game->compass->instances[0].x = game->resolution[WIDTH]
		- game->compass->width;
	game->compass->instances[0].y = game->resolution[HEIGHT]
		- game->compass->height;
	game->helmet->instances[0].x = game->resolution[WIDTH]
		- game->compass->width / 2 - game->helmet->width / 2;
	game->helmet->instances[0].y = game->resolution[HEIGHT]
		- game->compass->height / 2 - game->helmet->height / 2;
	game->minimap->instances[0].x = game->resolution[WIDTH]
		- game->compass->width;
	game->minimap->instances[0].y = game->resolution[HEIGHT]
		- game->compass->height;
}

static inline void	upright_or_upleft(t_game *game, int corner)
{
	if (corner == UP_RIGHT)
	{
		game->compass->instances[0].x = game->resolution[WIDTH]
			- game->compass->width;
		game->compass->instances[0].y = 0;
		game->helmet->instances[0].x = game->resolution[WIDTH]
			- game->compass->width / 2 - game->helmet->width / 2;
		game->helmet->instances[0].y = game->compass->height / 2
			- game->helmet->height / 2;
		game->minimap->instances[0].x = game->resolution[WIDTH]
			- game->compass->width;
		game->minimap->instances[0].y = 0;
	}
	else if (corner == UP_LEFT)
	{
		game->compass->instances[0].x = 0;
		game->compass->instances[0].y = 0;
		game->helmet->instances[0].x = game->compass->width / 2
			- game->helmet->width / 2;
		game->helmet->instances[0].y = game->compass->height / 2
			- game->helmet->height / 2;
		game->minimap->instances[0].x = 0;
		game->minimap->instances[0].y = 0;
	}
}

extern inline void	change_corner(t_game *game, int corner)
{
	if (corner == DOWN_LEFT)
	{
		game->compass->instances[0].x = 0;
		game->compass->instances[0].y = game->resolution[HEIGHT]
			- game->compass->height;
		game->helmet->instances[0].x = game->compass->width / 2
			- game->helmet->width / 2;
		game->helmet->instances[0].y = game->resolution[HEIGHT]
			- game->compass->height / 2 - game->helmet->height / 2;
		game->minimap->instances[0].x = 0;
		game->minimap->instances[0].y = game->resolution[HEIGHT]
			- game->compass->height;
	}
	else if (corner == DOWN_RIGHT)
		down_right(game);
	else
		upright_or_upleft(game, corner);
	game->scale->corner = corner;
}
