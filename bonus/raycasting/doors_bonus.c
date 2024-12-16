/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 09:31:31 by adesille          #+#    #+#             */
/*   Updated: 2024/12/14 18:40:33 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

extern inline void	calculate_door_height(t_game *game, t_door_cast *door_cast)
{
	game->raycast->draw_door = TRUE;
	if (!(*door_cast).x_side)
		(*door_cast).perpendicular_distance = ((*door_cast).grid[X]
				- game->player->position[X] + (1 - (*door_cast).step[X]) / 2)
			/ game->raycast->ray[X];
	else
		(*door_cast).perpendicular_distance = ((*door_cast).grid[Y]
				- game->player->position[Y] + (1 - (*door_cast).step[Y]) / 2)
			/ game->raycast->ray[Y];
	if (!(*door_cast).perpendicular_distance)
		game->raycast->height = (int)game->resolution[HEIGHT];
	else
		game->raycast->height = (int)(game->resolution[HEIGHT]
				/ (*door_cast).perpendicular_distance);
	if ((*door_cast).closed_door)
		game->zbuffer[game->raycast->pixel[X]]
			= (*door_cast).perpendicular_distance;
	else if (!game->zbuffer[game->raycast->pixel[X]])
		game->zbuffer[game->raycast->pixel[X]]
			= game->raycast->perpendicular_distance;
	(*door_cast).closed_door = FALSE;
}

extern inline void	draw_door(t_game *game, t_raycast *raycast, t_draw draw,
		t_vector pixel)
{
	float		wall_pixel_y;
	const int	wall_height = game->raycast->height;

	pixel[Y] = draw[START] + game->vertical_offset;
	wall_pixel_y = (draw[START] - (game->resolution[HEIGHT] / 2
				- wall_height / 2))
		* (float)raycast->texture->height / wall_height;
	while (pixel[Y] < draw[END] + game->vertical_offset)
	{
		safe_put_pixel(game, (int32_t[2]){pixel[X], pixel[Y]++},
			get_pixel_color(raycast, wall_pixel_y, game->player->position,
				raycast->texture), TRUE);
		wall_pixel_y += (float)raycast->texture->height / wall_height;
	}
	pixel[Y] = 0;
}
