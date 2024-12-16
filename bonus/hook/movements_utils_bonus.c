/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:04:06 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 11:11:24 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	valid_player_collision(t_game *game, int j)
{
	return ((game->player->position[Y] <= game->sprite[j].position[Y] + 0.25
			&& game->player->position[Y] >= game->sprite[j].position[Y]
			- 0.25)
		&& (game->player->position[X] <= game->sprite[j].position[X] + 0.25
			&& game->player->position[X] >= game->sprite[j].position[X]
			- 0.25) && game->sprite[j].type == ITEMS);
}

int	no_enemy_block(t_game *game, double x, double y)
{
	int	i;

	i = -1;
	while (++i < game->sprite_count)
	{
		if (game->sprite[i].type != ITEMS && !game->sprite[i].dead)
		{
			if (fabs(x - game->sprite[i].position[X]) < 0.3 && fabs(y
					- game->sprite[i].position[Y]) < 0.3)
				return (0);
		}
	}
	return (1);
}

int	check_move(t_game *game, double move_x, double move_y)
{
	double		player_x;
	double		player_y;

	player_x = game->player->position[X] + move_x * 0.15;
	player_y = game->player->position[Y] + move_y * 0.15;
	if (game->scene->map[(int)player_y][(int)player_x] == '1')
		return (0);
	if (game->scene->map[(int)player_y][(int)player_x] == 'D'
		&& game->doors_cast.is_close[return_door_index(game,
				(t_vector){player_x, player_y})])
		return (0);
	return (no_enemy_block(game, player_x, player_y));
}

int	is_move_ok(t_game *game, keys_t key)
{
	double	move_x;
	double	move_y;

	move_x = 0.0;
	move_y = 0.0;
	if (key == MLX_KEY_W || key == MLX_KEY_S)
	{
		move_x = game->player->direction[X];
		move_y = game->player->direction[Y];
	}
	else if (key == MLX_KEY_D || key == MLX_KEY_A)
	{
		move_x = game->player->plane[X];
		move_y = game->player->plane[Y];
	}
	if (key == MLX_KEY_S || key == MLX_KEY_A)
		return (check_move(game, -move_x, -move_y));
	else
		return (check_move(game, move_x, move_y));
}
