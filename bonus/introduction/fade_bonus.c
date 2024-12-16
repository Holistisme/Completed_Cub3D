/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fade_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:52:00 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:43 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline bool	update_image(t_game *game, mlx_image_t *reference_image,
						const t_vector pixel, int fade);
static inline bool	update_pixel(uint8_t *color, const uint8_t target,
						const bool fade, const int change);

#define FADING		1
#define UNFADING	-1

#define HOLY_PNG	"./textures/holy_order.png"
#define MLX_PNG		"./textures/mlx.png"

/* ************************************************************************** */

extern inline int	load_fade(t_game *game, t_index image)
{
	static t_index	sound;

	if (game->restart)
		sound = 0;
	if (skip_chapter(game, GET))
		return (UNFADING);
	else if (image == 1)
	{
		if (!sound)
		{
			play_sound("holy", UNDEFINED);
			++sound;
		}
		if (!fade_intro(game, HOLY_PNG))
			return (UNFADING);
	}
	else
	{
		if (sound++ == 1)
			play_sound("mlx", UNDEFINED);
		if (!fade_intro(game, MLX_PNG))
			return (UNFADING);
	}
	return (FADING);
}

extern inline bool	fade_intro(t_game *game, const t_path reference)
{
	static mlx_image_t	*reference_image = NULL;
	bool				fade;
	t_pixel				position;

	fade = false;
	if (reference && !reference_image)
		reference_image = set_image(game, reference, (t_vector){0}, false);
	position[X] = 0;
	while (position[X] < game->frame->width)
	{
		position[Y] = 0;
		while (position[Y] < game->frame->height)
			if (update_image(game, reference_image,
					(t_vector){position[X], position[Y]++}, reference != NULL))
				fade = true;
		++position[X];
	}
	if (!fade && reference_image)
	{
		mlx_delete_image(game->window, reference_image);
		reference_image = NULL;
	}
	return (fade);
}

static inline bool	update_image(t_game *game, mlx_image_t *reference_image,
						const t_vector pixel, int fade)
{
	const size_t	offset = ((pixel[X] * game->frame->height) + pixel[Y]) * 4;
	bool			edit;
	uint8_t			*color[3];
	uint8_t			*objective[3];
	t_index			index;

	edit = false;
	if (!fade)
		fade = -1;
	index = 0;
	while (index <= B)
	{
		color[index] = &game->frame->pixels[offset + index];
		if (fade)
			objective[index] = &reference_image->pixels[offset + index];
		if (update_pixel(color[index], *objective[index], fade == 1, fade))
			edit = true;
		++index;
	}
	return (edit);
}

static inline bool	update_pixel(uint8_t *color, const uint8_t target,
						const bool fade, const int change)
{
	uint8_t	update;

	if ((!fade && *color) || (fade && *color != target))
	{
		update = *color + change;
		*color = update;
		return (true);
	}
	return (false);
}
