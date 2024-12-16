/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:44:27 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 09:57:26 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline int	is_wall(t_game *game, uint32_t x, uint32_t y)
{
	if (x >= game->scene->width || y >= game->scene->height)
		return (1);
	return (game->scene->map[y][x] == '1');
}

void	y_move1(t_game *game, int i, int *y_wall, t_double_vector position)
{
	if (!is_wall(game, game->sprite[i].position[X], game->sprite[i].position[Y]
			+ 0.3) && !(game->sprite[i].position[Y] <= position[Y] + 0.25
			&& game->sprite[i].position[Y] >= position[Y] - 0.25) && !*y_wall)
	{
		if (is_door(game, game->sprite[i].position[X],
				game->sprite[i].position[Y] + 0.05))
			return ;
		game->sprite[i].position[Y] += game->sp_speed + game->sprite[i].speed;
	}
	else if (!(game->sprite[i].position[Y] <= position[Y] + 0.25
			&& game->sprite[i].position[Y] >= position[Y] - 0.25))
	{
		if (is_door(game, game->sprite[i].position[X],
				game->sprite[i].position[Y] - 0.05))
			return ;
		game->sprite[i].position[Y] -= game->sp_speed + game->sprite[i].speed;
		if (is_wall(game, game->sprite[i].position[X],
				game->sprite[i].position[Y] + 0.3))
			*y_wall = 1;
		if (!is_wall(game, game->sprite[i].position[X],
				game->sprite[i].position[Y] + 0.3))
			*y_wall = 0;
	}
}

void	y_move2(t_game *game, int i, int *y_wall, t_double_vector position)
{
	if (!is_wall(game, game->sprite[i].position[X], game->sprite[i].position[Y]
			- 0.3) && (!(game->sprite[i].position[Y] <= position[Y] + 0.25
				&& game->sprite[i].position[Y] >= position[Y] - 0.25))
		&& !*y_wall)
	{
		if (is_door(game, game->sprite[i].position[X],
				game->sprite[i].position[Y] - 0.05))
			return ;
		game->sprite[i].position[Y] -= game->sp_speed + game->sprite[i].speed;
	}
	else if (!(game->sprite[i].position[Y] <= position[Y] + 0.25
			&& game->sprite[i].position[Y] >= position[Y] - 0.25))
	{
		if (is_door(game, game->sprite[i].position[X],
				game->sprite[i].position[Y] + 0.05))
			return ;
		game->sprite[i].position[Y] += game->sp_speed + game->sprite[i].speed;
		if (is_wall(game, game->sprite[i].position[X],
				game->sprite[i].position[Y] - 0.3))
			*y_wall = 1;
		if (!is_wall(game, game->sprite[i].position[X],
				game->sprite[i].position[Y] - 0.3))
			*y_wall = 0;
	}
}

void	x_move1(t_game *game, int i, int *x_wall, t_double_vector position)
{
	if (!is_wall(game, game->sprite[i].position[X] + 0.3,
			game->sprite[i].position[Y])
		&& (!(game->sprite[i].position[X] <= position[X] + 0.25
				&& game->sprite[i].position[X] >= position[X] - 0.25))
		&& !*x_wall)
	{
		if (is_door(game, game->sprite[i].position[X] + 0.05,
				game->sprite[i].position[Y]))
			return ;
		game->sprite[i].position[X] += game->sp_speed + game->sprite[i].speed;
	}
	else if (!(game->sprite[i].position[X] <= position[X] + 0.25
			&& game->sprite[i].position[X] >= position[X] - 0.25))
	{
		if (is_door(game, game->sprite[i].position[X] - 0.05,
				game->sprite[i].position[Y]))
			return ;
		game->sprite[i].position[X] -= game->sp_speed + game->sprite[i].speed;
		if (is_wall(game, game->sprite[i].position[X] + 0.3,
				game->sprite[i].position[Y]))
			*x_wall = 1;
		if (!is_wall(game, game->sprite[i].position[X] + 0.3,
				game->sprite[i].position[Y]))
			*x_wall = 0;
	}
}

void	x_move2(t_game *game, int i, int *x_wall, t_double_vector position)
{
	if (!is_wall(game, game->sprite[i].position[X] - 0.3,
			game->sprite[i].position[Y])
		&& (!(game->sprite[i].position[X] <= position[X] + 0.25
				&& game->sprite[i].position[X] >= position[X] - 0.25))
		&& !*x_wall)
	{
		if (is_door(game, game->sprite[i].position[X] - 0.05,
				game->sprite[i].position[Y]))
			return ;
		game->sprite[i].position[X] -= game->sp_speed + game->sprite[i].speed;
	}
	else if (!(game->sprite[i].position[X] <= position[X] + 0.25
			&& game->sprite[i].position[X] >= position[X] - 0.25))
	{
		if (is_door(game, game->sprite[i].position[X] + 0.05,
				game->sprite[i].position[Y]))
			return ;
		game->sprite[i].position[X] += game->sp_speed + game->sprite[i].speed;
		if (is_wall(game, game->sprite[i].position[X] - 0.3,
				game->sprite[i].position[Y]))
			*x_wall = 1;
		if (!is_wall(game, game->sprite[i].position[X] - 0.3,
				game->sprite[i].position[Y]))
			*x_wall = 0;
	}
}
