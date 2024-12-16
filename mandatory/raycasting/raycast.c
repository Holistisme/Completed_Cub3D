/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:41:57 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/16 10:15:08 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */

static inline void	determine_step_n_side_dist(t_game *game);
static inline void	do_dda(t_game *game);
static inline void	calculate_wall_height(t_game *game);
static inline void	set_draw(t_raycast *raycast);

/* ************************************************************************** */

void	raycast(void *context)
{
	t_game		*game;

	game = (t_game *)context;
	game->raycast.i = 0;
	game->raycast.pixel[X] = 0;
	while (game->raycast.pixel[X] < WIDTH_SIZE)
	{
		game->raycast.camera
			= 2 * game->raycast.pixel[X] / (double)WIDTH_SIZE - 1;
		game->raycast.ray[X] = game->player[DIRECTION][X]
			+ game->player[PLANE][X] * game->raycast.camera;
		game->raycast.ray[Y] = game->player[DIRECTION][Y]
			+ game->player[PLANE][Y] * game->raycast.camera;
		game->raycast.grid[X] = (int)game->player[POSITION][X];
		game->raycast.grid[Y] = (int)game->player[POSITION][Y];
		game->raycast.delta[X] = fabs(1 / game->raycast.ray[X]);
		game->raycast.delta[Y] = fabs(1 / game->raycast.ray[Y]);
		determine_step_n_side_dist(game);
		do_dda(game);
		calculate_wall_height(game);
		set_draw(&game->raycast);
		draw(game);
		game->raycast.pixel[X]++;
	}
}

static inline void	determine_step_n_side_dist(t_game *game)
{
	if (game->raycast.ray[X] < 0.0)
	{
		game->raycast.step[X] = -1.0;
		game->raycast.side[X] = (game->player[POSITION][X]
				- game->raycast.grid[X]) * game->raycast.delta[X];
	}
	else
	{
		game->raycast.step[X] = 1.0;
		game->raycast.side[X] = (game->raycast.grid[X] + 1.
				- game->player[POSITION][X]) * game->raycast.delta[X];
	}
	if (game->raycast.ray[Y] < 0.0)
	{
		game->raycast.step[Y] = -1.0;
		game->raycast.side[Y] = (game->player[POSITION][Y]
				- game->raycast.grid[Y]) * game->raycast.delta[Y];
	}
	else
	{
		game->raycast.step[Y] = 1.0;
		game->raycast.side[Y] = (game->raycast.grid[Y] + 1.0
				- game->player[POSITION][Y]) * game->raycast.delta[Y];
	}
}

static inline void	do_dda(t_game *game)
{
	while (true)
	{
		if (game->raycast.side[X] < game->raycast.side[Y])
			game->raycast.axis = 0;
		else
			game->raycast.axis = 1;
		game->raycast.side[game->raycast.axis]
			+= game->raycast.delta[game->raycast.axis];
		game->raycast.grid[game->raycast.axis]
			+= game->raycast.step[game->raycast.axis];
		game->raycast.x_side = game->raycast.axis;
		if (game->map[game->raycast.grid[Y]]
			&& game->map[game->raycast.grid[Y]][game->raycast.grid[X]] == WALL)
			break ;
	}
}

static inline void	calculate_wall_height(t_game *game)
{
	if (!game->raycast.x_side)
		game->raycast.perpendicular_distance
			= (game->raycast.grid[X] - game->player[POSITION][X]
				+ (1 - game->raycast.step[X]) / 2.0) / game->raycast.ray[X];
	else
		game->raycast.perpendicular_distance
			= (game->raycast.grid[Y] - game->player[POSITION][Y]
				+ (1 - game->raycast.step[Y]) / 2.0) / game->raycast.ray[Y];
	if (!game->raycast.perpendicular_distance)
		game->raycast.height = (int)HEIGHT_SIZE;
	else
		game->raycast.height
			= (int)(HEIGHT_SIZE / game->raycast.perpendicular_distance);
}

static inline void	set_draw(t_raycast *raycast)
{
	(*raycast).draw[START] = HEIGHT_SIZE / 2 - (*raycast).height / 2;
	(*raycast).draw[END] = HEIGHT_SIZE / 2 + (*raycast).height / 2;
	if ((*raycast).draw[START] < 0)
		(*raycast).draw[START] = 0;
	if ((*raycast).draw[END] >= HEIGHT_SIZE)
		(*raycast).draw[END] = HEIGHT_SIZE - 1;
}
