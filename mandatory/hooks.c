/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:40:59 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 16:24:52 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

static inline bool	is_move_allowed(t_game *game, keys_t key,
						t_double_vector save);
static inline void	rotate(t_game *game, keys_t key);

/* ************************************************************************** */

void	key_hook(mlx_key_data_t keydata, void *param)
{
	static t_game	*game;
	t_double_vector	move;

	if (!game)
		game = (t_game *)param;
	if (keydata.action != MLX_RELEASE)
	{
		if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_A
				|| keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D)
			&& is_move_allowed(game, keydata.key, move))
		{
			game->player[POSITION][X] = move[X];
			game->player[POSITION][Y] = move[Y];
		}
		else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
			rotate(game, keydata.key);
		else if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->window);
	}
}

static inline bool	is_move_allowed(t_game *game, keys_t key,
						t_double_vector save)
{
	t_double_vector	move;

	move[X] = game->player[POSITION][X] + game->player[DIRECTION][X] * 0.15;
	move[Y] = game->player[POSITION][Y] + game->player[DIRECTION][Y] * 0.15;
	if (key == MLX_KEY_A)
	{
		move[X] = game->player[POSITION][X] - game->player[PLANE][X] * 0.15;
		move[Y] = game->player[POSITION][Y] - game->player[PLANE][Y] * 0.15;
	}
	else if (key == MLX_KEY_S)
	{
		move[X] = game->player[POSITION][X] - game->player[DIRECTION][X] * 0.15;
		move[Y] = game->player[POSITION][Y] - game->player[DIRECTION][Y] * 0.15;
	}
	else if (key == MLX_KEY_D)
	{
		move[X] = game->player[POSITION][X] + game->player[PLANE][X] * 0.15;
		move[Y] = game->player[POSITION][Y] + game->player[PLANE][Y] * 0.15;
	}
	save[X] = move[X];
	save[Y] = move[Y];
	return (game->map[(int)move[Y]][(int)move[X]] != WALL);
}

static inline void	rotate(t_game *game, keys_t key)
{
	double			rotation;
	const double	previous_x_direction = game->player[DIRECTION][X];
	const double	previous_x_plane = game->player[PLANE][X];
	const double	previous_y_plane = game->player[PLANE][Y];

	rotation = CLOCKWISE;
	if (key == MLX_KEY_LEFT)
		rotation = -CLOCKWISE;
	rotation *= 3 * DEGREE;
	game->player[DIRECTION][X] = game->player[DIRECTION][X] * cos(rotation)
		- game->player[DIRECTION][Y] * sin(rotation);
	game->player[DIRECTION][Y] = previous_x_direction * sin(rotation)
		+ game->player[DIRECTION][Y] * cos(rotation);
	game->player[PLANE][X] = previous_x_plane * cos(rotation)
		- previous_y_plane * sin(rotation);
	game->player[PLANE][Y] = previous_x_plane * sin(rotation)
		+ previous_y_plane * cos(rotation);
}
