/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:23:52 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:20 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	animate_slides(t_game *game, const int side);
static inline void	split_image(t_game *game, mlx_image_t *image,
						const int split, const int direction);
static inline void	create_splits(t_game *game, mlx_image_t *image,
						const t_vector size[2], const int direction);
static inline void	copy_pixels(mlx_image_t *source, mlx_image_t *destination,
						const t_vector start, const t_vector size);

#define HORIZONTALLY	1
#define VERTICALLY		2

/* ************************************************************************** */

void	animate_setting(t_game *game, mlx_image_t *image, const int direction)
{
	static int	side;
	int			split;

	if (direction)
	{
		play_sound("slide", UNDEFINED);
		side = direction;
		split = image->width / 2.5;
		if (direction == VERTICALLY)
			split = image->height / 2;
		split_image(game, image, split, direction);
		display_image(game->window, game->settings->slide[0],
			(t_vector){image->instances->x, image->instances->y});
		if (direction == HORIZONTALLY)
			display_image(game->window, game->settings->slide[1],
				(t_vector){image->instances->x + split, image->instances->y});
		else
			display_image(game->window, game->settings->slide[1],
				(t_vector){image->instances->x, image->instances->y + split});
		game->settings->frame->instances->z
			= game->settings->slide[1]->instances->z + 1;
	}
	else
		animate_slides(game, side);
}

static inline void	animate_slides(t_game *game, const int side)
{
	if (side == HORIZONTALLY)
	{
		game->settings->slide[0]->instances->x -= game->speed;
		game->settings->slide[1]->instances->x += game->speed;
	}
	else if (side == VERTICALLY)
	{
		game->settings->slide[0]->instances->y -= game->speed;
		game->settings->slide[1]->instances->y += game->speed;
	}
	if (game->settings->slide[0]->instances->x
		+ (int32_t)game->settings->slide[0]->width
		< game->settings->image[0]->instances->x
		|| game->settings->slide[0]->instances->y
		+ (int32_t)game->settings->slide[0]->height
		< game->settings->image[0]->instances->y)
	{
		mlx_delete_image(game->window, game->settings->slide[0]);
		mlx_delete_image(game->window, game->settings->slide[1]);
		game->settings->slide[0] = NULL;
		game->settings->slide[1] = NULL;
		game->settings->animation = false;
	}
}

static inline void	split_image(t_game *game, mlx_image_t *image,
						const int split, const int direction)
{
	t_vector	size[2];

	size[0][X] = split;
	size[0][Y] = image->height;
	size[1][X] = image->width - split;
	size[1][Y] = image->height;
	if (direction == VERTICALLY)
	{
		size[0][X] = image->width;
		size[0][Y] = split;
		size[1][X] = image->width;
		size[1][Y] = image->height - split;
	}
	create_splits(game, image, size, direction);
}

static inline void	create_splits(t_game *game, mlx_image_t *image,
						const t_vector size[2], const int direction)
{
	t_vector	start[2];

	start[0][X] = 0;
	start[0][Y] = 0;
	start[1][X] = 0;
	start[1][Y] = 0;
	if (direction == HORIZONTALLY)
		start[1][X] = size[0][X];
	else
		start[1][Y] = size[0][Y];
	game->settings->slide[0]
		= mlx_new_image(game->window, size[0][X], size[0][Y]);
	game->settings->slide[1]
		= mlx_new_image(game->window, size[1][X], size[1][Y]);
	copy_pixels(image, game->settings->slide[0], start[0], size[0]);
	copy_pixels(image, game->settings->slide[1], start[1], size[1]);
}

static inline void	copy_pixels(mlx_image_t *source, mlx_image_t *destination,
				const t_vector start, const t_vector size)
{
	t_vector	position;
	t_index		offset_source;
	t_index		offset_destination;

	position[Y] = 0;
	while (position[Y] < size[Y])
	{
		position[X] = 0;
		while (position[X] < size[X])
		{
			offset_source = ((start[Y] + position[Y])
					* source->width + (start[X] + position[X])) * 4;
			offset_destination = (position[Y]
					* destination->width + position[X]++) * 4;
			destination->pixels[offset_destination + R]
				= source->pixels[offset_source + R];
			destination->pixels[offset_destination + G]
				= source->pixels[offset_source + G];
			destination->pixels[offset_destination + B]
				= source->pixels[offset_source + B];
			destination->pixels[offset_destination + A]
				= source->pixels[offset_source + A];
		}
		position[Y]++;
	}
}
