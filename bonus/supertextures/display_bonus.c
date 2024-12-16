/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:39:49 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/14 18:24:09 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	draw_the_sky(t_game *game, const t_double_vector pixel,
						const t_vector position);
static inline void	draw_the_floor(t_game *game, const t_double_vector pixel,
						const t_vector position);

/* ************************************************************************** */

extern inline void	display_sky(t_game *game)
{
	t_vector		position;
	double			theta;
	t_double_vector	pixel;
	const double	angle = atan2(game->player->direction[Y],
			game->player->direction[X]);

	position[X] = 0;
	while (position[X] < game->resolution[WIDTH])
	{
		theta = (angle - game->fov / 2)
			+ ((double)position[X] / game->resolution[WIDTH]) * game->fov;
		pixel[X] = fmod((theta + PI) / (2 * PI), 1.0);
		if (pixel[X] < 0)
			pixel[X] += 1.0;
		position[Y] = 0;
		while (position[Y] < game->resolution[HEIGHT])
		{
			pixel[Y] = sin((double)position[Y]
					/ game->resolution[HEIGHT] * (PI / 2));
			draw_the_sky(game, pixel, position);
			++position[Y];
		}
		++position[X];
	}
}

static inline void	draw_the_sky(t_game *game,
						const t_double_vector pixel, const t_vector position)
{
	t_texture_pixel	texture;
	const float		percent = (game->player->life * 100) / 150;
	uint32_t		color;

	texture[X] = (int)(pixel[X] * game->sky->width) % game->sky->width;
	texture[Y] = (int)(pixel[Y] * game->sky->height) % game->sky->height;
	if (texture[X] < 0)
		texture[X] += game->sky->width;
	if (texture[Y] < 0)
		texture[Y] += game->sky->height;
	texture[OFFSET] = (texture[Y] * game->sky->width + texture[X]) * 4;
	color = get_rgba((t_rgba){
			game->sky->pixels[texture[OFFSET] + R],
			game->sky->pixels[texture[OFFSET] + G],
			game->sky->pixels[texture[OFFSET] + B],
			game->sky->pixels[texture[OFFSET] + A]});
	if (game->dark_mode)
		color = disco_mode_bro(color, game->raycast->temperature_shift);
	else
		color = damage_colorization(color, percent);
	mlx_put_pixel(game->frame, position[X], position[Y], color);
}

extern inline void	display_floor(t_game *game)
{
	t_vector		position;
	double			row_distance;
	t_double_vector	floor;
	double			camera_x;

	position[Y] = game->resolution[HEIGHT] / 2;
	while (position[Y] < game->resolution[HEIGHT])
	{
		row_distance = (game->resolution[HEIGHT] / 2.0)
			/ (position[Y] - game->resolution[HEIGHT] / 2);
		position[X] = 0;
		while (position[X] < game->resolution[WIDTH])
		{
			camera_x = 2.0 * position[X] / game->resolution[WIDTH] - 1.0;
			floor[X] = game->player->position[X] + row_distance
				* (game->player->direction[X]
					+ camera_x * game->player->plane[X]);
			floor[Y] = game->player->position[Y] + row_distance
				* (game->player->direction[Y]
					+ camera_x * game->player->plane[Y]);
			draw_the_floor(game, floor, position);
			++position[X];
		}
		++position[Y];
	}
}

static inline void	draw_the_floor(t_game *game, const t_double_vector pixel,
						const t_vector position)
{
	t_texture_pixel	texture;
	const double	tile_x = pixel[X] - floor(pixel[X]);
	const double	tile_y = pixel[Y] - floor(pixel[Y]);
	const float		percent = (game->player->life * 100) / 150;
	uint32_t		color;

	texture[X] = (int)(tile_x * game->floor->width);
	texture[Y] = (int)(tile_y * game->floor->height);
	texture[OFFSET] = (texture[Y] * game->floor->width + texture[X]) * 4;
	color = get_rgba((t_rgba){
			game->floor->pixels[texture[OFFSET] + R],
			game->floor->pixels[texture[OFFSET] + G],
			game->floor->pixels[texture[OFFSET] + B],
			game->floor->pixels[texture[OFFSET] + A]});
	if (game->dark_mode)
		color = disco_mode_bro(color, game->raycast->temperature_shift);
	else
		color = damage_colorization(color, percent);
	mlx_put_pixel(game->frame, position[X], position[Y], color);
}
