/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 09:34:38 by adesille          #+#    #+#             */
/*   Updated: 2024/12/16 10:05:14 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline void	init_door_cast(t_game *game, t_data_cast *d, int i)
{
	if (game->doors_cast.is_close[return_door_index(game,
				(t_vector){(*d).grid[X], (*d).grid[Y]})])
		game->raycast->door_cast[i].closed_door = TRUE;
	else
		game->raycast->door_cast[i].closed_door = FALSE;
	game->raycast->door_cast[i].grid[X] = (*d).grid[X];
	game->raycast->door_cast[i].grid[Y] = (*d).grid[Y];
	game->raycast->door_cast[i].step[X] = (*d).step[X];
	game->raycast->door_cast[i].step[Y] = (*d).step[Y];
	game->raycast->door_cast[i].x_side = game->raycast->x_side;
}

/**
 * Implements the Digital Differential Analyzer (DDA) algorithm for raycasting.
 * - Determines the next grid line the ray will cross.
 * - Updates side distances and grid positions based on the ray's direction.
 * - Checks for walls ('1') and doors ('D') in the map.
 * - Handles door encounters and updates the number of doors to draw.
*/
extern inline void	do_dda(t_game *game, t_data_cast *d)
{
	int	i;

	i = 0;
	while (42)
	{
		if ((*d).side[X] < (*d).side[Y])
			(*d).axis = 0;
		else
			(*d).axis = 1;
		(*d).side[(*d).axis] += (*d).delta[(*d).axis];
		(*d).grid[(*d).axis] += (*d).step[(*d).axis];
		game->raycast->x_side = (*d).axis;
		if (game->scene->map[(*d).grid[Y]])
		{
			if (game->scene->map[(*d).grid[Y]][(*d).grid[X]] == '1')
				break ;
			if (game->scene->map[(*d).grid[Y]][(*d).grid[X]] == 'D')
			{
				game->raycast->door = TRUE;
				init_door_cast(game, d, i++);
			}
		}
	}
	game->raycast->doors_to_draw = i;
}

/**
 * Determines the step direction and initial side distances for raycasting.
 * - Sets the step direction in the X and Y coordinates based
 * 	 on the ray direction.
 * - Calculates the initial side distances to the next grid line
 * 	 in the X and Y directions.
*/
extern inline void	determine_step_n_side_dist(t_game *game, t_data_cast *d)
{
	if (game->raycast->ray[X] < 0)
	{
		(*d).step[X] = -1;
		(*d).side[X] = (game->player->position[X] - (*d).grid[X])
			* (*d).delta[X];
	}
	else
	{
		(*d).step[X] = 1;
		(*d).side[X] = ((*d).grid[X] + 1. - game->player->position[X])
			* (*d).delta[X];
	}
	if (game->raycast->ray[Y] < 0)
	{
		(*d).step[Y] = -1;
		(*d).side[Y] = (game->player->position[Y] - (*d).grid[Y])
			* (*d).delta[Y];
	}
	else
	{
		(*d).step[Y] = 1;
		(*d).side[Y] = ((*d).grid[Y] + 1. - game->player->position[Y])
			* (*d).delta[Y];
	}
}

/**
 * Calculates the height of walls for raycasting.
 * - Determines the perpendicular distance from the player to the wall.
 * - Calculates the wall height based on the perpendicular distance.
 * - Updates the z-buffer for depth calculations.
*/
extern inline void	calculate_wall_height(t_game *game, t_data_cast *d,
		t_raycast *raycast)
{
	if (!raycast->x_side)
		raycast->perpendicular_distance = ((*d).grid[X]
				- game->player->position[X] + (1 - (*d).step[X]) / 2)
			/ raycast->ray[X];
	else
		raycast->perpendicular_distance = ((*d).grid[Y]
				- game->player->position[Y] + (1 - (*d).step[Y]) / 2)
			/ raycast->ray[Y];
	if (!raycast->perpendicular_distance)
		raycast->height = (int)game->resolution[HEIGHT];
	else
		raycast->height = (int)(game->resolution[HEIGHT]
				/ raycast->perpendicular_distance);
	if (!game->raycast->door)
		game->zbuffer[raycast->pixel[X]] = raycast->perpendicular_distance;
	else
		game->zbuffer[raycast->pixel[X]] = 0;
}

/**
 * Calculates the ray direction and delta distances for raycasting.
 * - Computes the camera position for the current pixel.
 * - Determines the ray direction based on the player's direction
 * 	 and camera plane.
 * - Maps the player's position to the corresponding grid cell.
 * - Calculates the delta distances for the ray in the X and Y directions.
*/
extern inline void	calculate_ray_n_delta_dist(t_game *game, t_data_cast *d)
{
	game->raycast->camera = 2 * game->raycast->pixel[X]
		/ (double)game->resolution[WIDTH] - 1;
	game->raycast->ray[X] = game->player->direction[X] + game->player->plane[X]
		* game->raycast->camera;
	game->raycast->ray[Y] = game->player->direction[Y] + game->player->plane[Y]
		* game->raycast->camera;
	(*d).grid[X] = (int)game->player->position[X];
	(*d).grid[Y] = (int)game->player->position[Y];
	(*d).delta[X] = fabs(1 / game->raycast->ray[X]);
	(*d).delta[Y] = fabs(1 / game->raycast->ray[Y]);
}
