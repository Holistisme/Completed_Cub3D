/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:38:48 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:03:45 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void			set_average_color(t_game *game,
								const t_vector pixel);
static inline int				get_average_color(t_game *game,
								const t_vector pixel, const t_index color);
static inline t_rgba_color	iterating_in_depth(t_game *game,
								t_rgba_color *side_color,
								const t_index color,
								const t_vector pixel);

#define AVERAGE	0
#define SEPIA	1
#define LEFT	0
#define RIGHT	1
#define UP		2
#define DOWN	3
#define TARGET	4
#define DEPTH	15

/* ************************************************************************** */

void	blur_frame(t_game *game)
{
	t_vector	position;

	position[X] = 0;
	while (position[X] < game->resolution[WIDTH])
	{
		position[Y] = 0;
		while (position[Y] < game->resolution[HEIGHT])
		{
			set_average_color(game, position);
			++position[Y];
		}
		++position[X];
	}
}

static inline void	set_average_color(t_game *game, const t_vector pixel)
{
	t_index			index;
	t_rgba_color	color[3][3];
	const double	adjustments[3][3] = {{0.393, 0.769, 0.189},
	{0.349, 0.686, 0.168}, {0.272, 0.534, 0.131}};

	index = 0;
	while (index < 3)
	{
		color[AVERAGE][index] = get_average_color(game, pixel, index);
		++index;
	}
	index = 0;
	while (index < 3)
	{
		color[SEPIA][index] = (int)(adjustments[index][R] * color[AVERAGE][R]
				+ adjustments[index][G] * color[AVERAGE][G]
				+ adjustments[index][B] * color[AVERAGE][B]);
		if (color[SEPIA][index++] > 255)
			color[SEPIA][index - 1] = 255;
	}
	mlx_put_pixel(game->menu->blur_frame, pixel[X], pixel[Y],
		get_rgba((t_rgba){color[SEPIA][R], color[SEPIA][G],
			color[SEPIA][B], OPAQUE}));
}

static inline t_rgba_color	get_average_color(t_game *game,
								const t_vector pixel, const t_index color)
{
	t_index			index;
	t_rgba_color	side_color[5];

	side_color[TARGET] = game->frame->pixels[((pixel[Y]
				* game->resolution[WIDTH] + pixel[X]) * 4) + color];
	index = 0;
	while (index <= DOWN)
		side_color[index++] = side_color[TARGET];
	return (iterating_in_depth(game, side_color, color, pixel));
}

static inline t_rgba_color	iterating_in_depth(t_game *game,
								t_rgba_color *side_color,
								const t_index color,
								const t_vector pixel)
{
	t_index	index;

	index = 1;
	while (index < DEPTH)
	{
		if (pixel[X] - index > 0)
			side_color[LEFT] += game->frame->pixels[((pixel[Y]
						* game->resolution[WIDTH] + (pixel[X] - index))
					* 4) + color];
		if (pixel[X] + index < game->resolution[WIDTH] - 1)
			side_color[RIGHT] += game->frame->pixels[((pixel[Y]
						* game->resolution[WIDTH] + (pixel[X] + index)) * 4)
				+ color];
		if (pixel[Y] - index > 0)
			side_color[UP] += game->frame->pixels[(((pixel[Y] - index)
						* game->resolution[WIDTH] + pixel[X]) * 4) + color];
		if (pixel[Y] + index++ < game->resolution[HEIGHT] - 1)
			side_color[DOWN] += game->frame->pixels[(((pixel[Y] + index - 1)
						* game->resolution[WIDTH] + pixel[X]) * 4) + color];
	}
	return ((side_color[LEFT] + side_color[RIGHT] + side_color[UP]
			+ side_color[DOWN] + side_color[TARGET]) / (5 + DEPTH * 4));
}
