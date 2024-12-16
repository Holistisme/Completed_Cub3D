/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   studio_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:52:14 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:04:49 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* ************************************************************************** */

static inline void	set_alpha_opaque(mlx_image_t *image);

#define FADING		1
#define UNFADING	-1

/* ************************************************************************** */

void	display_studio(t_game *game)
{
	static t_index	image;
	static int		fade;

	if (game->restart && image == 3)
	{
		image = 0;
		fade = 0;
	}
	if (fade == FADING)
		fade = load_fade(game, image);
	else if (fade == UNFADING)
		fade = -fade_intro(game, NULL);
	else
	{
		set_alpha_opaque(game->frame);
		fade = FADING;
		if (++image == 3)
			display_main_menu(game);
	}
}

static inline void	set_alpha_opaque(mlx_image_t *image)
{
	size_t			index;
	const size_t	size = image->width * image->height;

	index = 0;
	while (index < size)
		image->pixels[(index++) * 4 + A] = OPAQUE;
}
