/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:27:59 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:05:34 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

// 💬 Updates the player's direction and plane based on the new x position.
void	update_direction(t_game *game, const double xpos)
{
	double			rotation;
	static double	previous_xpos = 0;
	const double	previous_x_direction = game->player->direction[X];
	const double	previous_x_plane = game->player->plane[X];
	const double	previous_y_plane = game->player->plane[Y];

	rotation = CLOCKWISE;
	if (xpos != previous_xpos)
	{
		if (xpos > previous_xpos)
			rotation = -CLOCKWISE;
		previous_xpos = xpos;
		rotation *= game->sensitivity * DEGREE;
		game->player->direction[X] = game->player->direction[X] * cos(rotation)
			- game->player->direction[Y] * sin(rotation);
		game->player->direction[Y] = previous_x_direction * sin(rotation)
			+ game->player->direction[Y] * cos(rotation);
		game->player->plane[X] = previous_x_plane * cos(rotation)
			- previous_y_plane * sin(rotation);
		game->player->plane[Y] = previous_x_plane * sin(rotation)
			+ previous_y_plane * cos(rotation);
	}
	update_achievement(game->legacies->achievement, WATCH, +1);
}

// 💬 Rotates the player's view based on the x position of the mouse.
void	rotate(double xpos, double ypos, void *param)
{
	t_game	*game;

	(void)ypos;
	game = (t_game *)param;
	if (game->state == &raycast)
	{
		update_direction(game, -xpos);
		mlx_set_mouse_pos(game->window, game->resolution[WIDTH] / 2,
			game->resolution[HEIGHT] / 2);
	}
}
